#ifndef CV_SOBEL_H
#define CV_SOBEL_H

#include <emscripten/emscripten.h>
#include <stdint.h>
#include <stddef.h>

#define BLACK 0
#define WHITE 255

EMSCRIPTEN_KEEPALIVE void cv_apply_sobel_filter_grayscale(uint8_t* data, size_t width, size_t height, uint8_t channels);

#endif
