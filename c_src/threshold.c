#include "sobel.h"
#include <stddef.h>
#include <assert.h>
#include <stdint.h>

#include <emscripten/emscripten.h>

#define GRAY_1 17

EMSCRIPTEN_KEEPALIVE
void cv_apply_threshold(uint8_t* data, size_t width, size_t height, uint8_t channels, uint8_t threshold) {
  assert(channels == 1 && "cv_apply_threshold expects GRAYSCALE");

  for (int i = 0; i < width * height; i++) {
    data[i] = data[i] <= threshold ? GRAY_1 : WHITE;
  }
}
