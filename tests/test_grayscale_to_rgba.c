#include "../c_src/utils.h"
#include "test.h"

static uint8_t grayscaleImage[WIDTH][HEIGHT] = {
    { 0, 64, 128 },
    { 32, 96, 192 },
    { 16, 128, 255 }
};


int main() {
    uint8_t* newData = (uint8_t*)malloc(sizeof(uint8_t) * WIDTH * HEIGHT * RGBA);

    cv_expand_grayscale_to_rgba((uint8_t*)grayscaleImage, newData, WIDTH, HEIGHT, 1);

    uint8_t expectedData[WIDTH][HEIGHT][RGBA] = {
        { { 0, 0, 0, 255 }, { 64, 64, 64, 255 }, { 128, 128, 128, 255 } },
        { { 32, 32, 32, 255 }, { 96, 96, 96, 255 }, { 192, 192, 192, 255 } },
        { { 16, 16, 16, 255 }, { 128, 128, 128, 255 }, { 255, 255, 255, 255 } }
    };

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            assert(EQUAL(&newData[(i * HEIGHT + j) * RGBA], expectedData[i][j]));
        }
    }

    free(newData);

    return 0;
}
