#include "header/ErrorCalculation.hpp"
#include <cmath>
#include <vector>
#include <array>
#include <unordered_map>
using namespace std;

float ErrorCalculation::variance(const Image& image, int x, int y, int width, int height) {
    long long sumRed = 0, sumGreen = 0, sumBlue = 0;
    int total = width * height;
    for (int row = y; row < y + height; ++row) {
        for (int col = x; col < x + width; col++) {
            Pixel p = image.getPixel(col, row);
            sumRed += p.r;
            sumGreen += p.g;
            sumBlue += p.b;
        }
    }
    float meanRed = float(sumRed) / total;
    float meanGreen = float(sumGreen) / total;
    float meanBlue = float(sumBlue) / total;

    float varRed = 0, varGreen = 0, varBlue = 0;
    for (int row = y; row < y + height; row++) {
        for (int col = x; col < x + width; col++) {
            Pixel p = image.getPixel(col, row);
            varRed += (p.r - meanRed) * (p.r - meanRed);
            varGreen += (p.g - meanGreen) * (p.g - meanGreen);
            varBlue += (p.b - meanBlue) * (p.b - meanBlue);
        }
    }
    return (varRed + varGreen + varBlue) / (3 * total);
}

float ErrorCalculation::mad(const Image& image, int x, int y, int width, int height) {
    long long sumRed = 0, sumGreen = 0, sumBlue = 0;
    int total = width * height;
    for (int row = y; row < y + height; row++)
        for (int col = x; col < x + width; col++) {
            Pixel p = image.getPixel(col, row);
            sumRed += p.r;
            sumGreen += p.g;
            sumBlue += p.b;
        }
    float meanRed = float(sumRed) / total;
    float meanGreen = float(sumGreen) / total;
    float meanBlue = float(sumBlue) / total;

    float devRed = 0, devGreen = 0, devBlue = 0;
    for (int row = y; row < y + height; row++)
        for (int col = x; col < x + width; col++) {
            Pixel p = image.getPixel(col, row);
            devRed += abs(p.r - meanRed);
            devGreen += abs(p.g - meanGreen);
            devBlue += abs(p.b - meanBlue);
        }
    return (devRed + devGreen + devBlue) / (3 * total);
}

float ErrorCalculation::maxDiff(const Image& image, int x, int y, int width, int height) {
    int minRed = 255, minGreen = 255, minBlue = 255;
    int maxRed = 0, maxGreen = 0, maxBlue = 0;
    for (int row = y; row < y + height; row++)
        for (int col = x; col < x + width; col++) {
            Pixel p = image.getPixel(col, row);
            minRed = min(minRed, int(p.r));
            minGreen = min(minGreen, int(p.g));
            minBlue = min(minBlue, int(p.b));
            maxRed = max(maxRed, int(p.r));
            maxGreen = max(maxGreen, int(p.g));
            maxBlue = max(maxBlue, int(p.b));
        }
    return (maxRed - minRed + maxGreen - minGreen + maxBlue - minBlue) / 3.0f;
}

float ErrorCalculation::entropy(const Image& image, int x, int y, int width, int height) {
    std::array<int, 256> freqRed = {}, freqGreen = {}, freqBlue = {};
    int total = width * height;

    for (int row = y; row < y + height; row++)
        for (int col = x; col < x + width; col++) {
            Pixel p = image.getPixel(col, row);
            freqRed[p.r]++;
            freqGreen[p.g]++;
            freqBlue[p.b]++;
        }

    auto entropy_channel = [&](const std::array<int, 256>& freq) {
        float H = 0.0f;
        for (int f : freq) {
            if (f > 0) {
                float p = float(f) / total;
                H -= p * log2(p);
            }
        }
        return H;
    };

    return (entropy_channel(freqRed) + entropy_channel(freqGreen) + entropy_channel(freqBlue)) / 3.0f;
}