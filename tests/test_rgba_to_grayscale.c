#include "../c_src/utils.h"
#include "test.h"


static uint8_t rgbaImage[WIDTH][HEIGHT][RGBA] = {
    { { 0, 0, 0, 255 }, { 64, 64, 64, 255 }, { 128, 128, 128, 255 } },
    { { 32, 32, 32, 255 }, { 96, 96, 96, 255 }, { 192, 192, 192, 255 } },
    { { 16, 16, 16, 255 }, { 128, 128, 128, 255 }, { 255, 255, 255, 255 } }
};

int main() {
    uint8_t* grayscaleData = (uint8_t*)malloc(sizeof(uint8_t) * WIDTH * HEIGHT);

    // Call cv_squish_rgba_to_grayscale with the sample RGBA image data
    cv_squish_rgba_to_grayscale((uint8_t*)rgbaImage, grayscaleData, WIDTH, HEIGHT, RGBA);

    // Define the expected grayscale data for the given RGBA image
    uint8_t expectedData[WIDTH][HEIGHT] = {
        { 0, 64, 128 },
        { 32, 96, 192 },
        { 16, 128, 255 }
    };

    // Check if the generated grayscale data matches the expected data
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            assert(isPixelEqual(grayscaleData[i * HEIGHT + j], expectedData[i][j]));
        }
    }

    free(grayscaleData);

    return 0;
}
