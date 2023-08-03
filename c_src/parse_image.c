#include "utils.h"
#include "sobel.h"
#include "crop.h"

#include <stdint.h>
#include <assert.h>
#include <stdlib.h>

#include <emscripten/emscripten.h>

EMSCRIPTEN_KEEPALIVE
void cv_parse_image_rgba(uint8_t* data, size_t width, size_t height, uint8_t channels) {
  assert(channels == 4 && "cv_parse_image_rgba only accepts RGBA");

  // convert to grayscale, then apply sobel filter
  cv_squish_rgba_to_grayscale(data, width, height, channels);
  cv_apply_sobel_filter_rgba(data, width, height, 1);

  // -> on detecting a "white pixel group" set all the preceding pixels to black. reverse and do the same
  // rotate the image, EG shift all the valid pixels immediately to the start
  // apply thresholding

  // clean up and resize baby
  cv_expand_grayscale_to_rgba(data, width, height, 1);

}
