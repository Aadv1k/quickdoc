#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include <emscripten/emscripten.h>

EMSCRIPTEN_KEEPALIVE void cv_apply_otsu_threshold_rgba(unsigned char *data, size_t width, size_t height, int channels) {
    if (channels != 4) {
        return;
    }

    // Calculate the intensity values of each pixel (assuming RGBA order)
    unsigned char *intensity = (unsigned char *)malloc(width * height * sizeof(unsigned char));
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            size_t index = (y * width + x) * channels;
            unsigned char r = data[index];
            unsigned char g = data[index + 1];
            unsigned char b = data[index + 2];

            // Calculate the intensity using a common formula
            intensity[y * width + x] = 0.2989 * r + 0.5870 * g + 0.1140 * b;
        }
    }

    // Compute the histogram of intensity values
    int histogram[256] = {0};
    for (size_t i = 0; i < width * height; i++) {
        histogram[intensity[i]]++;
    }

    // Total number of pixels
    int total = width * height;

    // Calculate the sum of pixel intensities
    double sum = 0;
    for (int i = 0; i < 256; i++) {
        sum += i * histogram[i];
    }

    double sumB = 0;
    int wB = 0;
    int wF = 0;

    double varMax = 0;
    int threshold = 0;

    for (int t = 0; t < 256; t++) {
        wB += histogram[t];
        if (wB == 0) continue;

        wF = total - wB;
        if (wF == 0) break;

        sumB += t * histogram[t];
        double mB = sumB / wB;
        double mF = (sum - sumB) / wF;

        double varBetween = wB * wF * (mB - mF) * (mB - mF);

        if (varBetween > varMax) {
            varMax = varBetween;
            threshold = t;
        }
    }

    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            size_t index = (y * width + x) * channels;
            unsigned char i = intensity[y * width + x];

            if (i < threshold) {
                data[index] = data[index + 1] = data[index + 2] = 0; // Black
            } else {
                data[index] = data[index + 1] = data[index + 2] = 255; // White
            }
        }
    }

    free(intensity);
}
