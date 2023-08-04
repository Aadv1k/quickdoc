#ifndef CV_THRESHOLD
#define CV_THRESHOLD

#include <emscripten/emscripten.h>

EMSCRIPTEN_KEEPALIVE
void cv_apply_threshold(uint8_t* data, size_t width, size_t height, uint8_t channels, uint8_t threshold);

#endif
