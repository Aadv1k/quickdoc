#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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

EMSCRIPTEN_KEEPALIVE
void cv_apply_sobel_filter_rgba(unsigned char * data, size_t width, size_t height, int channels) {
  for (int i = 0; i < height*width*channels; i+=channels) {
      unsigned char R = data[i],
                    G = data[i+1],
                    B = data[i+2];

      unsigned char grayPixel = ((0.3 * R) + (0.59 * G) + (0.11 * B));

      data[i] = grayPixel;
      data[i+1] = grayPixel;
      data[i+2] = grayPixel;
      data[i+3] = 255;
  }
}
