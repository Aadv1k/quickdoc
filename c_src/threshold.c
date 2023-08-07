#include "sobel.h"
#include <stddef.h>
#include <assert.h>
#include <stdint.h>


#define GRAY_1 33

EXPORT_FN
void cv_apply_threshold(uint8_t* data, size_t width, size_t height, uint8_t channels, uint8_t threshold) {
  assert(channels == 1 && "cv_apply_threshold expects GRAYSCALE");

  for (size_t i = 0; i < width * height; i++) {
    data[i] = data[i] <= threshold ? GRAY_1 : WHITE;
  }
}
