/*
#include "utils.h"
#include "sobel.h"
#include "crop.h"

#include <stdint.h>
#include <assert.h>
#include <stdlib.h>

#include <emscripten/emscripten.h>

#include <stdio.h>

#define RGBA 4
#define GRAYSCALE 1


EMSCRIPTEN_KEEPALIVE void cv_parse_image_rgba(uint8_t* data, size_t width, size_t height, uint8_t channels) {
  assert(channels == 4 && "cv_parse_image_rgba only accepts RGBA");
  
  size_t grayscaleSize = sizeof(uint8_t) * width * height;
  uint8_t* grayscaleData = (uint8_t*)malloc(grayscaleSize);

  cv_squish_rgba_to_grayscale(data, grayscaleData, width, height, RGBA);
  cv_apply_sobel_filter_grayscale(grayscaleData, width, height, GRAYSCALE);

  const size_t leftEdge = cv_get_left_edge(grayscaleData, width, height, GRAYSCALE);

  printf("DEBUG %lu\n", leftEdge);
  printf("DEBUG %lu\n", grayscaleSize);

  printf("DEBUG %lu\n", width);

  cv_crop_x_edge_grayscale(grayscaleData, width, height, GRAYSCALE, leftEdge);
  width -= leftEdge;

  printf("DEBUG %lu\n", width);

  size_t originalSize = sizeof(uint8_t) * width * height * RGBA;

  printf("DEBUG %lu\n", originalSize);

  // Convert grayscale data back to RGBA and copy to newData
  uint8_t* newData = (uint8_t*)malloc(originalSize);
  cv_expand_grayscale_to_rgba(grayscaleData, newData, width, height, GRAYSCALE);

  memcpy(data, newData, originalSize);

  free(grayscaleData);
  free(newData);
//  return {width, height, RGBA};
}
*/
