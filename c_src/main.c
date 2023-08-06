#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "utils.h"

void usage(const char * program) {
  printf("Usage:\n");
  printf("  %s input.(png|jpg) output.(png|jpg)\n", program);
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

  free(data);
}
