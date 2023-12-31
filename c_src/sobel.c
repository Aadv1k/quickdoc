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

EXPORT_FN void cv_apply_sobel_filter_grayscale(uint8_t* data, size_t width, size_t height, uint8_t channels) {
  assert(channels == 1 && "cv_apply_sobel_filter_grayscale expects a GRAYSCALE image");

  uint8_t* newData = (uint8_t*)malloc(sizeof(uint8_t) * width * height);

  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      int sumX = 0, sumY = 0;

      for (size_t x = 0; x < SOBEL_K; x++) {
        for (size_t y = 0; y < SOBEL_K; y++) {
          size_t currentIndex = (i + x) * width + (y + j);

          if (currentIndex >= width*height) continue;

          sumX += data[currentIndex] * sobelX[x][y];
          sumY += data[currentIndex] * sobelY[x][y];
        }
      }

      int grayscale = sqrt((sumX * sumX) + (sumY * sumY));
      int currentValue = grayscale >= THRESHOLD ? WHITE : BLACK;
      newData[i * width + j] = currentValue;
    }
  }


  memcpy(data, newData, sizeof(uint8_t) * width * height * channels);
  free(newData);
}
