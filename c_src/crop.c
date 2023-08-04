#include "crop.h"
#include "sobel.h"

#include <stdint.h>
#include <emscripten/emscripten.h>
#include <stdlib.h>

#include <assert.h>
#include <string.h>
#include <math.h>

#define WHITE 255

size_t cv_get_left_edge(uint8_t* edgeData, size_t width, size_t height, uint8_t channels) {
    assert(channels == 1 && "cv_get_left_edge expects GRAYSCALE image");

    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            size_t currentIndex = (i * width) + j;
            if (edgeData[currentIndex] == WHITE && edgeData[currentIndex + 1] == WHITE)
                return j;
        }
    }
    return 0;
}

void cv_crop_x_edge_grayscale(uint8_t* data, size_t width, size_t height, uint8_t channels, const size_t leftEdge) {
    size_t croppedWidth = width - leftEdge;
    size_t newDataSize = sizeof(uint8_t) * croppedWidth * height * channels;
    uint8_t* newData = (uint8_t*)malloc(newDataSize);

    for (size_t i = 0; i < height; i++) {
        for (size_t j = leftEdge; j < width; j++) {
            size_t currentIndex = (i * width * channels) + (j * channels);
            size_t newIndex = (i * croppedWidth * channels) + ((j - leftEdge) * channels);

            for (size_t k = 0; k < channels; k++) {
                newData[newIndex + k] = data[currentIndex + k];
            }
        }
    }

    memcpy(data, newData, newDataSize);
    free(newData);
}
