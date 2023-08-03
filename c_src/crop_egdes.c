#include "utils.h"

#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <emscripten/emscripten.h>

#define SOBEL_K 3
#define THRESHOLD 128

#define BLACK 0
#define WHITE 255

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

EMSCRIPTEN_KEEPALIVE size_t cv_trim_x_edges(uint8_t* edgeData, uint8_t* originalData, size_t width, size_t height, uint8_t channels) {
    assert(channels == 1);

    size_t minXIndex = width;
    size_t maxXIndex = 0;

    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width - 1; j++) {
            size_t currentIndex = i * width + j;
            if (edgeData[currentIndex] == WHITE && edgeData[currentIndex + 1] == WHITE) {
                minXIndex = minXIndex >= j ? j : minXIndex;
                maxXIndex = maxXIndex <= j + 1 ? j + 1 : maxXIndex;
            }
        }
    }

    if (minXIndex == width || maxXIndex == 0) {
        memset(originalData, BLACK, sizeof(uint8_t) * width * height);
        return 0;
    }

    size_t croppedWidth = maxXIndex - minXIndex + 1;
    for (size_t i = 0; i < height; i++) {
        memcpy(originalData + i * croppedWidth, edgeData + i * width + minXIndex, croppedWidth);
    }
    return minXIndex;
}

EMSCRIPTEN_KEEPALIVE void cv_apply_sobel_filter(uint8_t* data, size_t width, size_t height, uint8_t channels) {
  if (channels != 1)
    cv_squish_rgba_to_grayscale(data, width, height, channels);

  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {

      int sumX = 0, sumY = 0;

      for (size_t x = 0; x < SOBEL_K; x++) {
        for (size_t y = 0; y < SOBEL_K; y++) {
          size_t currentIndex = (i + x) * width + y + j;
          sumX += data[currentIndex] + sobelX[x][y];
          sumY += data[currentIndex] + sobelY[x][y];
        }
      }

      int grayscale = sqrt((sumX * sumX) + (sumY * sumY));
      int currentValue = grayscale >= THRESHOLD ? WHITE: BLACK;
      data[i * width + j] = currentValue;
    }
  }
}
