#ifndef CV_UTILS_H
#define CV_UTILS_H

#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#define EXPORT_FN EMSCRIPTEN_KEEPALIVE
#else
#define EXPORT_FN
#endif


EXPORT_FN void cv_squish_rgba_to_grayscale(uint8_t* data, size_t width, size_t height, uint8_t channels);

EXPORT_FN void cv_expand_grayscale_to_rgba(uint8_t* data, size_t width, size_t height, uint8_t channels);

#endif
