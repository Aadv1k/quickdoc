#ifndef CV_CROP_H
#define CV_CROP_H

#include <stdint.h>
#include <emscripten/emscripten.h>
#include <stdlib.h>

EMSCRIPTEN_KEEPALIVE size_t cv_get_left_edge(uint8_t* edgeData, size_t width, size_t height, uint8_t channels);

EMSCRIPTEN_KEEPALIVE void cv_crop_x_edge_grayscale(uint8_t* data, size_t width, size_t height, uint8_t channels, const size_t leftEdge);

#endif
