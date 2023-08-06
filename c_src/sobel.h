#ifndef CV_SOBEL_H
#define CV_SOBEL_H

#include <stdint.h>
#include <stddef.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#define EXPORT_FN EMSCRIPTEN_KEEPALIVE
#else
#define EXPORT_FN
#endif

#define BLACK 0
#define WHITE 255


EXPORT_FN void cv_apply_sobel_filter_grayscale(uint8_t* data, uint8_t* newData, size_t width, size_t height, uint8_t channels);

#endif
