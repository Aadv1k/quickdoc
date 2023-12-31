#include "utils.h"

#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

EXPORT_FN void cv_squish_rgba_to_grayscale(uint8_t* data, size_t width, size_t height, uint8_t channels) {
    for (size_t i = 0, j = 0; i < width * height * channels; i += channels, j++) {
        const uint8_t R = data[i],
                      G = data[i + 1],
                      B = data[i + 2];
        const uint8_t grayscale = (uint8_t)((0.3 * R) + (0.59 * G) + (0.11 * B));
        data[j] = grayscale;
    }
}


EXPORT_FN void cv_expand_grayscale_to_rgba(uint8_t* data, size_t width, size_t height, uint8_t channels) {
  assert(channels == 1 && "cv_expand_grayscale_to_rgba expects a grayscale image");

  const uint8_t rgba = 4;
  uint8_t* newData = (uint8_t*)malloc(sizeof(uint8_t) * width * height * rgba);

  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      size_t currentIndex = (i * width * rgba) + (j * rgba);

      uint8_t grayscaleValue = data[(i * width) + j];

      newData[currentIndex + 0] = grayscaleValue; // R
      newData[currentIndex + 1] = grayscaleValue; // G
      newData[currentIndex + 2] = grayscaleValue; // B
      newData[currentIndex + 3] = 255; // A
     }
   }

  memcpy(data, newData, sizeof(uint8_t) * width * height * rgba);
  free(newData);
} 
