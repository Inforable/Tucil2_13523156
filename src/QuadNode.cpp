#include "header/QuadNode.hpp"
#include <cmath>
#include <algorithm>
using namespace std;

QuadNode::QuadNode(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->isLeaf = true;
    for (int i = 0; i < 4; i++) {
        children[i] = nullptr;
    }
}

QuadNode::~QuadNode() {
    for (int i = 0; i < 4; i++) {
        delete children[i];
    }
}

void QuadNode::computeAverageColor(const Image& image) {
    long sumRed = 0;
    long sumGreen = 0;
    long sumBlue = 0;

    for (int row = y; row < y + height; row++) {
        for (int col = x; col < x + width; col++) {
            Pixel p = image.getPixel(col, row);
            sumRed += p.r;
            sumGreen += p.g;
            sumBlue += p.b;
        }
    }

    int totalPixels = width * height;
    color.r = sumRed / totalPixels;
    color.g = sumGreen / totalPixels;
    color.b = sumBlue / totalPixels;
}

float QuadNode::computeError(const Image& image, int method) {
    computeAverageColor(image);
    float error = 0.0;
    int totalPixels = width * height;

    if (method == 1) {
        float sumVarRed = 0;
        float sumVarGreen = 0;
        float sumVarBlue = 0;

        for (int row = y; row < y + height; row++) {
            for (int col = x; col < x + width; col++) {
                Pixel p = image.getPixel(col, row);
                sumVarRed += (p.r - color.r) * (p.r - color.r);
                sumVarGreen += (p.g - color.g) * (p.g - color.g);
                sumVarBlue += (p.b - color.b) * (p.b - color.b);
            }
        }
        error = (sumVarRed + sumVarGreen + sumVarBlue) / (3 * totalPixels);
    } else if (method == 2) {
        float sumDevRed = 0;
        float sumDevGreen = 0;
        float sumDevBlue = 0;

        for (int row = y; row < y + height; row++) {
            for (int col = x; col < x + width; col++) {
                Pixel p = image.getPixel(col, row);
                sumDevRed += abs(p.r - color.r);
                sumDevGreen += abs(p.g - color.g);
                sumDevBlue += abs(p.b - color.b);
            }
        }
        error = (sumDevRed + sumDevGreen + sumDevBlue) / (3 * totalPixels);
    } else if (method == 3) {
        int minRed = 255, minGreen = 255, minBlue = 255;
        int maxRed = 0, maxGreen = 0, maxBlue = 0;

        for (int row = y; row < y + height; row++) {
            for (int col = x; col < x + width; col++) {
                Pixel p = image.getPixel(col, row);
                minRed = min(minRed, (int)p.r);
                minGreen = min(minGreen, (int)p.g);
                minBlue = min(minBlue, (int)p.b);
                maxRed = max(maxRed, (int)p.r);
                maxGreen = max(maxGreen, (int)p.g);
                maxBlue = max(maxBlue, (int)p.b);
            }
        }

        float rangeRed = maxRed - minRed;
        float rangeGreen = maxGreen - minGreen;
        float rangeBlue = maxBlue - minBlue;

        error = (rangeRed + rangeGreen + rangeBlue) / (3 * 255.0f);
    } else if (method == 4) {
        int frequencyRed[256] = {0};
        int frequencyGreen[256] = {0};
        int frequencyBlue[256] = {0};

        for (int row = y; row < y + height; row++) {
            for (int col = x; col < x + width; col++) {
                Pixel p = image.getPixel(col, row);
                frequencyRed[p.r]++;
                frequencyGreen[p.g]++;
                frequencyBlue[p.b]++;
            }
        }

        float entropyRed = 0.0;
        float entropyGreen = 0.0;
        float entropyBlue = 0.0;

        for (int i = 0; i < 256; i++) {
            if (frequencyRed[i] > 0) {
                float prob = (float)frequencyRed[i] / totalPixels;
                entropyRed -= prob * log2(prob);
            }
            if (frequencyGreen[i] > 0) {
                float prob = (float)frequencyGreen[i] / totalPixels;
                entropyGreen -= prob * log2(prob);
            }
            if (frequencyBlue[i] > 0) {
                float prob = (float)frequencyBlue[i] / totalPixels;
                entropyBlue -= prob * log2(prob);
            }
        }

        error = (entropyRed + entropyGreen + entropyBlue) / 3.0f;
    } else {
        return 0;
    }

    return error;
}

void QuadNode::build(const Image& image, float threshold, int minBlockSize, int method) {
    float error = computeError(image, method);

    if (error > threshold && (width / 2 >= minBlockSize || height / 2 >= minBlockSize)) {
        isLeaf = false;
        int halfW = width / 2;
        int halfH = height / 2;
        children[0] = new QuadNode(x, y, halfW, halfH);
        children[1] = new QuadNode(x + halfW, y, width - halfW, halfH);
        children[2] = new QuadNode(x, y + halfH, halfW, height - halfH);
        children[3] = new QuadNode(x + halfW, y + halfH, width - halfW, height - halfH);

        for (int i = 0; i < 4; i++) {
            children[i]->build(image, threshold, minBlockSize, method);
        }
    } else {
        isLeaf = true;
    }
}

void QuadNode::fill(Image& output) const {
    if (isLeaf) {
        for (int row = y; row < y + height; row++) {
            for (int col = x; col < x + width; col++) {
                output.setPixel(col, row, color);
            }
        }
    } else {
        for (int i = 0; i < 4; i++) {
            if (children[i]) {
                children[i]->fill(output);
            }
        }
    }
}

int QuadNode::getDepth() const {
    if (isLeaf) {
        return 1;
    }
    int maxDepth = 0;
    for (int i = 0; i < 4; i++) {
        if (children[i]) {
            maxDepth = max(maxDepth, children[i]->getDepth());
        }
    }
    return maxDepth + 1;
}

int QuadNode::countNodes() const {
    if (isLeaf) {
        return 1;
    }
    int count = 1;
    for (int i = 0; i < 4; i++) {
        if (children[i]) {
            count += children[i]->countNodes();
        }
    }
    return count;
}