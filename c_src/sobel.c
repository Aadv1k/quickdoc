#include "sobel.h"

#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define SOBEL_K 3
#define THRESHOLD 128

static int sobelX[SOBEL_K][SOBEL_K] = {
  {-1, -2, -1},
  {0, 0, 0},
  {1, 2, 1}
};

static int sobelY[SOBEL_K][SOBEL_K] = {
  {-1, 0, 1},
  {-2, 0, 2},
  {-1, 0, 1}
};

EMSCRIPTEN_KEEPALIVE void cv_apply_sobel_filter_rgba(uint8_t* data, size_t width, size_t height, uint8_t channels) {
  assert(channels == 1 && "cv_apply_sobel_filter_rgba expects a GRAYSCALE image");
  
  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      int sumX = 0, sumY = 0;

      for (size_t x = 0; x < SOBEL_K; x++) {
        for (size_t y = 0; y < SOBEL_K; y++) {
          size_t currentIndex = (i + x) * width + y + j;
          sumX += data[currentIndex] * sobelX[x][y];
          sumY += data[currentIndex] * sobelY[x][y];
        }
      }

      int grayscale = sqrt((sumX * sumX) + (sumY * sumY));
      int currentValue = grayscale >= THRESHOLD ? WHITE : BLACK;
      data[i * width + j] = currentValue;
    }
  }
}
