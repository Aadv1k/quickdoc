#ifndef CV_CROP_H
#define CV_CROP_H

#include <stdint.h>
#include <emscripten/emscripten.h>
#include <stdlib.h>

EMSCRIPTEN_KEEPALIVE size_t cv_trim_x_edges(uint8_t* edgeData, uint8_t* originalData, size_t width, size_t height, uint8_t channels);

#endif
