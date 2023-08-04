#include "crop.h"
#include "sobel.h"

#include <stdint.h>
#include <emscripten/emscripten.h>
#include <stdlib.h>

#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#define WHITE 255

EMSCRIPTEN_KEEPALIVE
size_t cv_get_left_edge(uint8_t* edgeData, size_t width, size_t height, uint8_t channels) {
    assert(channels == 1 && "cv_get_left_edge expects GRAYSCALE image");

    size_t minIndex = width - 1; // Initialize with the maximum possible value (rightmost index)

    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            size_t currentIndex = (i * width) + j;
            if (edgeData[currentIndex] == WHITE && edgeData[currentIndex + 1] == WHITE) {
                if (j < minIndex) {
                    minIndex = j; // Update minIndex if we find a smaller index
                }
            }
        }
    }
    return minIndex;
}

EMSCRIPTEN_KEEPALIVE
size_t cv_get_right_edge(uint8_t* edgeData, size_t width, size_t height, uint8_t channels) {
    assert(channels == 1 && "cv_get_right_edge expects GRAYSCALE image");

    for (size_t i = 0; i < height; i++) {
        for (size_t j = width - 1; j > 0; j--) {
            size_t currentIndex = (i * width) + j;
            if (edgeData[currentIndex] == WHITE && edgeData[currentIndex - 1] == WHITE)
                return j;
        }
    }
    return width - 1;
}


EMSCRIPTEN_KEEPALIVE
size_t cv_crop_x_edge_grayscale_and_get_width(uint8_t* data, size_t width, size_t height, uint8_t channels, size_t leftEdge, size_t rightEdge) {
    //size_t croppedWidth = width - ((leftEdge >= width/2 ? 0 : leftEdge) + (rightEdge >= width/2 ? width - 1 : rightEdge));

    rightEdge = width;

    size_t croppedWidth = width - leftEdge;
    size_t newDataSize = sizeof(uint8_t) * croppedWidth * height * channels;
    uint8_t* newData = (uint8_t*)malloc(newDataSize);

    for (size_t i = 0; i < height; i++) {
        for (size_t j = leftEdge; j <= rightEdge; j++) {
            size_t currentIndex = (i * width * channels) + (j * channels);
            size_t newIndex = (i * croppedWidth * channels) + ((j - leftEdge) * channels);

            for (size_t k = 0; k < channels; k++) {
                newData[newIndex + k] = data[currentIndex + k];
            }
        }
    }

    memcpy(data, newData, newDataSize);
    free(newData);

    return croppedWidth;
}

