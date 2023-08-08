#include "crop.h"
#include "sobel.h"

#include <stdint.h>
#include <stdlib.h>

#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

EXPORT_FN
size_t cv_get_top_edge(uint8_t* edgeData, size_t width, size_t height, uint8_t channels, int offset) {
    (void)channels;
    size_t widestStretch = 0, widestXIndex = 0;

    for (size_t i = offset + 3; i < height - 3; i++) {
        for (size_t j = 3; j < width; j++) {
            size_t currentIndex = (i * width) + j;
            if (edgeData[currentIndex] == BLACK) continue;

            size_t xx = j;
            while (xx <= width - 2 && edgeData[(i * width) + xx] == WHITE && edgeData[((i + 1) * width) + xx] == WHITE) {
                xx++;
            }

            size_t currentStretch = xx - j;
            if (currentStretch >= widestStretch) {
                widestStretch = currentStretch;
                widestXIndex = j;
            }

            j = xx;
        }
    }
    return widestXIndex;
}

EXPORT_FN
size_t cv_get_left_edge(uint8_t* edgeData, size_t width, size_t height, uint8_t channels, int offset) {
    (void)channels;
    size_t longestEdge = 0, longestXIndex = 0;

    for (size_t i = 2; i < height - 2; i++) {
        for (size_t j = offset + 2; j < width - 2; j++) {

            size_t currentIndex = (i * width) + j;
            if (edgeData[currentIndex] == BLACK) continue;

            size_t yy = i;
            while (yy <= height - 2 && (edgeData[(yy * width) + j] == WHITE &&
                                    edgeData[(yy * width) + j + 1] == WHITE)
                   ) yy++;

            if (yy - i >= longestEdge) {
                longestEdge = yy - i;
                longestXIndex = j;
            }

        }
    }
    return longestXIndex;
}


EXPORT_FN
size_t cv_crop_x_edge_grayscale_and_get_width(uint8_t* data, size_t width, size_t height, uint8_t channels, size_t leftEdge, size_t rightEdge) {
    // this looks weird because we are dealing with unsigned numbers 
    size_t croppedWidth = width - (leftEdge + (width - rightEdge));
    size_t newDataSize = sizeof(uint8_t) * croppedWidth * height * channels;
    uint8_t* newData = (uint8_t*)malloc(newDataSize);

    for (size_t i = 0; i < height; i++) {
        for (size_t j = leftEdge, k = 0; j < rightEdge; j++, k++) {
            newData[i * croppedWidth + k] = data[i * width + j];
        }
    }

    memcpy(data, newData, newDataSize);
    free(newData);

    return croppedWidth;
}

EXPORT_FN
size_t cv_crop_y_edge_grayscale_and_get_height(uint8_t* data, size_t width, size_t height, uint8_t channels, size_t topEdge, size_t bottomEdge) {
    (void)height;
    size_t croppedHeight = height - (topEdge + (height - bottomEdge));
    size_t newDataSize = sizeof(uint8_t) * croppedHeight * width;
    uint8_t* newData = (uint8_t*)malloc(newDataSize);

    for (size_t i = topEdge; i < bottomEdge; i++) {
        size_t currentIndex = i * width * channels;
        size_t newIndex = (i - topEdge) * width;
        memcpy(newData + newIndex, data + currentIndex, width);
    }

    memcpy(data, newData, newDataSize);
    free(newData);

    return croppedHeight;
}
