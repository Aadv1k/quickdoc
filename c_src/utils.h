#ifndef CV_UTILS_H
#define CV_UTILS_H

#include <emscripten/emscripten.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

EMSCRIPTEN_KEEPALIVE void cv_squish_rgba_to_grayscale(uint8_t* data, size_t width, size_t height, uint8_t channels);
EMSCRIPTEN_KEEPALIVE void cv_expand_grayscale_to_rgba(uint8_t* data, size_t width, size_t height, uint8_t channels);


#endif
