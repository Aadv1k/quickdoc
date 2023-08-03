#include "utils.h"

#include <emscripten/emscripten.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

EMSCRIPTEN_KEEPALIVE void cv_squish_rgba_to_grayscale(uint8_t* data, size_t width, size_t height, uint8_t channels) {
  assert(channels == 4 && "cv_squish_rgba_to_grayscale assumes RGBA");

  uint8_t* grayImage = (uint8_t*)malloc(sizeof(uint8_t) * width * height);

  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {

      size_t currentIndex = (i * width * channels) + j;

      uint8_t R = data[currentIndex + 0],
              G = data[currentIndex + 1],
              B = data[currentIndex + 2];

      uint8_t grayscale = (0.299 * R) + (0.587 * G) + (0.144 * B);
      grayImage[i * width + j] = grayscale;
    }
  }

  memcpy(data, grayImage, width * height * sizeof(uint8_t));
  free(grayImage);
}


EMSCRIPTEN_KEEPALIVE void cv_expand_grayscale_to_rgba(uint8_t* data, size_t width, size_t height, uint8_t channels) {
  assert(channels == 1 && "cv_expand_grayscale_to_rgba assumes GRAYSCALE");

  const uint8_t rgba = 4;

  uint8_t* newImage = (uint8_t*)malloc(sizeof(uint8_t) * width * height * rgba);

  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {

      size_t currentIndex = (i * width * rgba) + j;

      newImage[currentIndex + 0] = data[(i * width) + j];
      newImage[currentIndex + 1] = data[(i * width) + j];
      newImage[currentIndex + 2] = data[(i * width) + j];
      newImage[currentIndex + 3] = 255; // A
    }
  }

  memcpy(data, newImage, sizeof(uint8_t) * width * height * rgba);
  free(newImage);
}

