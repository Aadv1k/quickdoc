#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <emscripten/emscripten.h>

#define SOBEL_K_SIZE 3

static int sobelX[SOBEL_K_SIZE][SOBEL_K_SIZE] = {
  {-1, -2, -1},
  {0, 0, 0},
  {1, 2, 1}
}

static int sobelY[SOBEL_K_SIZE][SOBEL_K_SIZE] = {
  {-1, 0, 1},
  {-2, 0, 2},
  {-1, 0, 1}
}

EMSCRIPTEN_KEEPALIVE unsigned char * cv_apply_sobel_filter(unsigned char * data, size_t width, size_t height, int channels) {

  size_t imgSize = sizeof(unsigned char) * width * height;
  unsigned char * copied = (unsigned char)malloc(imgSize);


  for (size_t i = 0; i < height*width; i++) {
    unsigned char R = data[i],
                  G = data[i+1],
                  B = data[i+2];

    unsigned char pixel = (0.299 * R) + (0.587 * G) + (0.114 * B);
    copied[i] = pixel;
  }

  memcpy(data, copied, imgSize);


  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      int sumX, sumY;
      int currentPixelIndex = i * height + j;

      for (int x = 0; x < SOBEL_K_SIZE; x++) {
        for (int y = 0; y < SOBEL_K_SIZE; y++) {
          sumX += sobelX[x][y] * data[currentPixelIndex];
          sumY += sobelY[x][y] * data[currentPixelIndex];
        }
      }
      data[currentPixelIndex] = sqrt((sumY * sumY) + (sumX * sumX));
    }
  }

  free(copied);

  return data;
}
