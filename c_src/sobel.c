#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <emscripten/emscripten.h>

#define SOBEL_K_SIZE 3

static int sobelX[SOBEL_K_SIZE][SOBEL_K_SIZE] = {
  {-1, -2, -1},
  {0, 0, 0},
  {1, 2, 1}
};

static int sobelY[SOBEL_K_SIZE][SOBEL_K_SIZE] = {
  {-1, 0, 1},
  {-2, 0, 2},
  {-1, 0, 1}
};

EMSCRIPTEN_KEEPALIVE unsigned char * cv_apply_sobel_filter(unsigned char * data, size_t width, size_t height, int channels) {
  unsigned char * copied = (unsigned char *)malloc(sizeof(unsigned char) * width * height);

  for (size_t i = 0; i < height * width * channels; i += channels) {
    unsigned char R = data[i],
                  G = data[i + 1],
                  B = data[i + 2];
    const unsigned char grayscale = (unsigned char)((0.3 * R) + (0.59 * G) + (0.11 * B));
    copied[i] = grayscale;
    if (channels == 4) {
      copied[i + 3] = data[i + 3]; // Copy alpha channel if available (RGBA format)
    }
  }

  memcpy(data, copied, sizeof(unsigned char) * width * height * channels);
  free(copied);

  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      int sumX = 0, sumY = 0;

      for (int x = 0; x < SOBEL_K_SIZE; x++) {
        for (int y = 0; y < SOBEL_K_SIZE; y++) {
          size_t currentPixelIndex = (i + x - 1) * width * channels + (j + y - 1) * channels;
          sumX += sobelX[x][y] * data[currentPixelIndex];
          sumY += sobelY[x][y] * data[currentPixelIndex];
        }
      }

      size_t pixelIndex = i * width * channels + j * channels;
      data[pixelIndex] = sqrt((sumY * sumY) + (sumX * sumX));
      if (channels == 4) {
        data[pixelIndex + 1] = data[pixelIndex]; // Copy grayscale value to green channel (G)
        data[pixelIndex + 2] = data[pixelIndex]; // Copy grayscale value to blue channel (B)
        data[pixelIndex + 3] = 255; // Set alpha channel to fully opaque (255)
      }
    }
  }

  return data;
}
