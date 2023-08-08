#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "utils.h"
#include "sobel.h"
#include "crop.h"
#include "threshold.h"

#include <stdint.h>

void usage(const char * program) {
  printf("\nUsage:\t%s input.jpg output.jpg\n\n", program);
  printf("Applies the processing of quickdoc to input file and writes to output\n\n");
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

  cv_apply_sobel_filter_grayscale(grayscaleData, width, height, 1);

  size_t leftEdge = cv_get_left_edge(grayscaleData, width, height, channels);
  size_t rightEdge = cv_get_right_edge(grayscaleData, width, height, channels);
  width = cv_crop_x_edge_grayscale_and_get_width(data, width, height, channels, leftEdge, rightEdge);

  /*
  size_t topEdge = cv_get_top_edge(grayscaleData, width, height, channels);
  height = cv_crop_y_edge_grayscale_and_get_height(data, width, height, channels, topEdge, height);
  */

  cv_apply_threshold(data, width, height, 1, THRESHOLD);

  if (stbi_write_jpg(output_file, width , height, channels, data, 0) == 0) {
    fprintf(stderr, "Error: unable to write %s", output_file);
    exit(1);
  }

  free(grayscaleData);
  free(data);
}
