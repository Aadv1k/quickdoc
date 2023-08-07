#include "crop.h"
#include "sobel.h"

#include <stdint.h>
#include <stdlib.h>

#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

EXPORT_FN
size_t cv_get_top_edge(uint8_t* edgeData, size_t width, size_t height, uint8_t channels) {
    size_t minIndex = height;

    for (size_t i = 3; i < height - 3; i++) {
        for (size_t j = 3; j < width - 3; j++) {
            size_t currentIndex = (i * width + j) * channels;
            if (
                edgeData[currentIndex] == WHITE
                && edgeData[currentIndex + 1] == WHITE
                && edgeData[currentIndex + 2] == WHITE) {
                if (i < minIndex) {
                    minIndex = i;
                }
                break;
            }
        }
    }
    return minIndex;
}

EXPORT_FN
size_t cv_get_bottom_edge(uint8_t* edgeData, size_t width, size_t height, uint8_t channels) {
    (void)channels;
    size_t maxIndex = 0; // Initialize to the topmost row (out of image bounds)

    for (size_t i = height - 1; i != 0; i--) {
        for (size_t j = 0; j < width; j++) {
            size_t currentIndex = (i * width) + j;
            if (edgeData[currentIndex] == WHITE) {
                if (i > maxIndex) {
                    maxIndex = i;
                }
                break; // Move to the previous row after finding the first white pixel
            }
        }
    }

    return maxIndex;
}

EXPORT_FN
size_t cv_get_left_edge(uint8_t* edgeData, size_t width, size_t height, uint8_t channels) {
    assert(channels == 1 && "cv_get_left_edge expects GRAYSCALE image");
    size_t minIndex = width - 1;

    for (size_t i = 3; i < height - 3; i++) {
        for (size_t j = 3; j < width - 3; j++) {
            size_t currentIndex = (i * width) + j;

            if (
                (edgeData[currentIndex] == WHITE && edgeData[currentIndex + 1] == WHITE) &&
                (edgeData[(i - 1) * width + j] == WHITE && edgeData[(i - 2) * width + j] == WHITE && edgeData[(i - 3) * width + j] == WHITE) &&
                (edgeData[(i + 1) * width + j] == WHITE && edgeData[(i + 2) * width + j] == WHITE && edgeData[(i + 3) * width + j] == WHITE)
                ) {
              if (j < minIndex) minIndex = j;
            }
        }
    }

    return minIndex;
}

EXPORT_FN
size_t cv_get_right_edge(uint8_t* edgeData, size_t width, size_t height, uint8_t channels) {
    assert(channels == 1 && "cv_get_right_edge expects GRAYSCALE image");

    size_t maxIndex = 0;

    size_t rowMargin = 3;
    size_t colMargin = 3;

    for (size_t i = rowMargin; i < height - rowMargin; i++) {
        for (size_t j = width - colMargin - 1; j >= colMargin; j--) {
            size_t currentIndex = (i * width) + j;


            if (edgeData[currentIndex] >= 200) {
                if (j > maxIndex) {
                    maxIndex = j;
                }
            }
        }
    }
    return maxIndex;
}

EXPORT_FN
size_t cv_crop_x_edge_grayscale_and_get_width(uint8_t* data, size_t width, size_t height, uint8_t channels, size_t leftEdge, size_t rightEdge) {
    if (leftEdge > width / 2) leftEdge = width / 2;
    if (rightEdge > width / 2) rightEdge = 0;

    size_t croppedWidth = width - (leftEdge + rightEdge);
    size_t newDataSize = sizeof(uint8_t) * croppedWidth * height * channels;
    uint8_t* newData = (uint8_t*)malloc(newDataSize);

    for (size_t i = 0; i < height; i++) {
        for (size_t j = leftEdge, k = 0; j < width - rightEdge; j++, k++) {
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
    size_t croppedHeight = bottomEdge - topEdge;
    size_t croppedWidth = width * channels;
    size_t newDataSize = sizeof(uint8_t) * croppedHeight * croppedWidth;
    uint8_t* newData = (uint8_t*)malloc(newDataSize);

    for (size_t i = topEdge; i < bottomEdge; i++) {
        size_t currentIndex = i * width * channels;
        size_t newIndex = (i - topEdge) * croppedWidth;
        memcpy(newData + newIndex, data + currentIndex, croppedWidth);
    }

    memcpy(data, newData, newDataSize);
    free(newData);

    return croppedHeight;
}
