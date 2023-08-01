#include <stdio.h>
#include <stdlib.h>

#include <emscripten/emscripten.h>

EMSCRIPTEN_KEEPALIVE
void cv_resize_down_by_xy(unsigned char* data, size_t width, size_t height, int channels, int factorX, int factorY) {
    size_t newWidth = width / factorX;
    size_t newHeight = height / factorY;
    size_t newChannels = channels;

    unsigned char* newData = (unsigned char*)malloc(newWidth * newHeight * newChannels);

    for (size_t y = 0; y < newHeight; ++y) {
        for (size_t x = 0; x < newWidth; ++x) {
            for (int c = 0; c < channels; ++c) {
                size_t sum = 0;
                for (int dy = 0; dy < factorY; ++dy) {
                    for (int dx = 0; dx < factorX; ++dx) {
                        size_t origX = x * factorX + dx;
                        size_t origY = y * factorY + dy;
                        size_t index = (origY * width + origX) * channels + c;
                        sum += data[index];
                    }
                }
                newData[(y * newWidth + x) * newChannels + c] = sum / (factorX * factorY);
            }
        }
    }
    free(data);
    data = newData;
}
