#include <stdio.h>
#include <stdlib.h>

#include <emscripten/emscripten.h>

EMSCRIPTEN_KEEPALIVE
void cv_resize_down_by_xy(unsigned char* data, size_t width, size_t height, int channels, int factorX, int factorY) {
    size_t newWidth = width / factorX;
    size_t newHeight = height / factorY;

    unsigned char* newData = (unsigned char*)malloc(newWidth * newHeight * channels * sizeof(unsigned char));

    if (!newData) {
        // Error handling for memory allocation failure
        return;
    }

    for (size_t y = 0; y < newHeight; y++) {
        for (size_t x = 0; x < newWidth; x++) {
            for (int ch = 0; ch < channels; ch++) {
                unsigned int sum = 0;
                for (int fy = 0; fy < factorY; fy++) {
                    for (int fx = 0; fx < factorX; fx++) {
                        size_t srcX = x * factorX + fx;
                        size_t srcY = y * factorY + fy;
                        size_t srcIndex = (srcY * width + srcX) * channels + ch;
                        sum += data[srcIndex];
                    }
                }
                unsigned char average = (unsigned char)(sum / (factorX * factorY));
                size_t dstIndex = (y * newWidth + x) * channels + ch;
                newData[dstIndex] = average;
            }
        }
    }

    // Copy the resized data back to the original array
    for (size_t i = 0; i < newWidth * newHeight * channels; i++) {
        data[i] = newData[i];
    }

    // Free the temporary data array
    free(newData);
}
