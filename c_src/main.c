#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


#include <stdint.h>
#include "utils.h"

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

  uint8_t* newData = (uint8_t*)malloc(sizeof(uint8_t) * width * height * channels);

  cv_squish_rgba_to_grayscale(data, newData, width, height, channels);

  if (stbi_write_jpg(output_file, width , height, channels, newData, 0) != 0) {
    fprintf(stderr, "Error: unable to write %s", output_file);
  }

  free(newData);
  free(data);
}
