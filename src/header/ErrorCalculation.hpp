// ErrorCalculation.hpp
#ifndef ERROR_CALCULATION_HPP
#define ERROR_CALCULATION_HPP

#include "Image.hpp"

class ErrorCalculation {
public:
    // Parameter variance
    static float variance(const Image& image, int x, int y, int width, int height);

    // Parameter Mean Absolute Deviation (MAD)
    static float mad(const Image& image, int x, int y, int width, int height);

    // Parameter Max Pixel Difference
    static float maxDiff(const Image& image, int x, int y, int width, int height);

    // Parameter Entropy
    static float entropy(const Image& image, int x, int y, int width, int height);
};

#endif
// end of ErrorCalculation.hpp