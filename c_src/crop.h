#ifndef CV_CROP_H
#define CV_CROP_H

#include <stdint.h>
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#define EXPORT_FN EMSCRIPTEN_KEEPALIVE
#else
#define EXPORT_FN
#endif

#include <stdlib.h>

EXPORT_FN size_t cv_get_left_edge(uint8_t* edgeData, size_t width, size_t height, uint8_t channels);
EXPORT_FN size_t cv_get_right_edge(uint8_t* edgeData, size_t width, size_t height, uint8_t channels);
EXPORT_FN size_t cv_get_top_edge(uint8_t* edgeData, size_t width, size_t height, uint8_t channels);
EXPORT_FN size_t cv_get_bottom_edge(uint8_t* edgeData, size_t width, size_t height, uint8_t channels);

EXPORT_FN size_t cv_crop_x_edge_grayscale_and_get_width(uint8_t* data, size_t width, size_t height, uint8_t channels, size_t leftEdge, size_t rightEdge);

EXPORT_FN size_t cv_crop_y_edge_grayscale_and_get_height(uint8_t* data, size_t width, size_t height, uint8_t channels, size_t topEdge, size_t bottomEdge);

#endif
