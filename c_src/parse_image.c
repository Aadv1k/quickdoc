#include "utils.h"
#include "sobel.h"
#include "crop.h"

#include <stdint.h>
#include <assert.h>
#include <stdlib.h>

#include <emscripten/emscripten.h>

#define RGBA 4

EMSCRIPTEN_KEEPALIVE
void cv_parse_image_rgba(uint8_t* data, size_t width, size_t height, uint8_t channels) {
  assert(channels == 4 && "cv_parse_image_rgba only accepts RGBA");
  
  size_t grayscaleSize = sizeof(uint8_t) * width * height;
  
  uint8_t* grayscaleData = (uint8_t*)malloc(grayscaleSize);
  
  cv_squish_rgba_to_grayscale(data, grayscaleData, width, height, channels);


  cv_apply_sobel_filter_grayscale(grayscaleData, width, height, 1);

  size_t rgba = 4;
  size_t originalSize = sizeof(uint8_t) * width * height * rgba;
  uint8_t* newData = (uint8_t*)malloc(originalSize);

  cv_expand_grayscale_to_rgba(grayscaleData, newData, width, height, 1);


  memcpy(data, newData, originalSize);

  // Free the allocated memory
  free(grayscaleData);
  free(newData);
}
