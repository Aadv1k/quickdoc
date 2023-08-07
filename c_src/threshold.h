#ifndef CV_THRESHOLD
#define CV_THRESHOLD

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#define EXPORT_FN EMSCRIPTEN_KEEPALIVE
#else
#define EXPORT_FN
#endif

EXPORT_FN
void cv_apply_threshold(uint8_t* data, size_t width, size_t height, uint8_t channels, uint8_t threshold);

#endif
