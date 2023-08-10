#define STB_IMAGE_IMPLEMENTATION
#include "thirdparty/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "thirdparty/stb_image_write.h"

#include "utils.h"
#include "sobel.h"
#include "crop.h"
#include "threshold.h"

#include <stdint.h>

#define MAX_FLOOD_F_VISITED 50

void usage(const char * program) {
  printf("\nUsage:\t%s input.jpg output.jpg\n\n", program);
  printf("Applies the processing of quickdoc to input file and writes to output\n\n");
}

static int dr[4] = {-1, 1, 0, 0};
static int dc[4] = {0, 0, -1, 1};

void floodFill(uint8_t * data, size_t width, size_t height, size_t channels, int startRow, int startCol, int fillValue) {
    bool visited[MAX_FLOOD_F_VISITED][MAX_FLOOD_F_VISITED] = {false};

    Point queue[MAX_FLOOD_F_VISITED * MAX_FLOOD_F_VISITED];
    int front = 0, rear = 0;

    queue[rear++] = (Point){startRow, startCol};
    visited[startRow][startCol] = true;

    while (front != rear) {
        Point current = queue[front++];
        int row = current.row;
        int col = current.col;

        labelArray[row * width + col] = fillValue;

        for (int k = 0; k < 4; k++) {
            int newRow = row + dr[k];
            int newCol = col + dc[k];

            if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width &&
                !visited[newRow][newCol] &&
                data[(newRow * width + newCol) * channels] == 255) {
                queue[rear++] = (Point){newRow, newCol};
                visited[newRow][newCol] = true;
            }
        }
    }
}

void cv_create_cca_labels_from_image(uint8_t * data, size_t width, size_t height, uint8_t channels, size_t * labelArray) {
    assert(channels == 1 && "cv_create_cca_labels_from_image expects a GRAYSCALE image");
    for (int i = 0; i < height; i++) {
        int visited[MAX_FLOOD_F_VISITED];
        for (int j = 0; j < width; j++) {
            if (visited[i][j] || data[(i * width + j) * channels] == 0) {
                continue;
            }
            floodFill(data, width, height, channels, i, j, i);
        }
    }
}

int main(int argc, char **argv) {
  const char *program = argv[0];

  if (argc != 3) {
    usage(program);
    exit(1);
  }

  const char *input_file = argv[1];
  const char *output_file = argv[2];

  int width, height, channels;
  uint8_t * data = stbi_load(input_file, &width, &height, &channels, 0);

  if (data == NULL) {
    fprintf(stderr, "Error: failed to load %s\n", input_file);
    exit(1);
  }

  cv_squish_rgba_to_grayscale(data, width, height, channels);
  channels = 1;

  uint8_t * grayscaleData = (uint8_t *)malloc(sizeof(uint8_t) * width * height);
  memcpy(grayscaleData, data, width * height * sizeof(uint8_t));

  cv_apply_sobel_filter_grayscale(grayscaleData, width, height, 1);

  size_t leftEdge = cv_get_left_edge(grayscaleData, width, height, channels, 0);
  size_t rightEdge = cv_get_left_edge(grayscaleData, width, height, channels, leftEdge + 10);
  width = cv_crop_x_edge_grayscale_and_get_width(data, width, height, channels, leftEdge, rightEdge);

  size_t topEdge = cv_get_top_edge(grayscaleData, width, height, channels, 0);
  height = cv_crop_y_edge_grayscale_and_get_height(data, width, height, channels, topEdge, height);

  cv_apply_threshold(data, width, height, 1, 128);

  if (stbi_write_jpg(output_file, width , height, channels, data, 0) == 0) {
    fprintf(stderr, "Error: unable to write %s", output_file);
    exit(1);
  }

  free(grayscaleData);
  free(data);
}
