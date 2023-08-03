#include <assert.h> 
#include <stdint.h>
#include <stdio.h>

#define WIDTH 3
#define HEIGHT 3

#define RGBA 4


static inline int isPixelEqual(uint8_t pixel1, uint8_t pixel2) {
    return pixel1 == pixel2;
}
