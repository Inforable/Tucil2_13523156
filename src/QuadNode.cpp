#include "header/QuadNode.hpp"
#include "header/ErrorCalculation.hpp"
#include <algorithm>

QuadNode::QuadNode(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height), isLeaf(true) {
    for (int i = 0; i < 4; ++i) {
        children[i] = nullptr;
    }
}

QuadNode::~QuadNode() {
    for (int i = 0; i < 4; ++i) {
        delete children[i];
    }
}

void QuadNode::computeAverageColor(const Image& image) {
    long sumR = 0, sumG = 0, sumB = 0;
    for (int row = y; row < y + height; ++row) {
        for (int col = x; col < x + width; ++col) {
            Pixel p = image.getPixel(col, row);
            sumR += p.r;
            sumG += p.g;
            sumB += p.b;
        }
    }
    int total = width * height;
    color.r = sumR / total;
    color.g = sumG / total;
    color.b = sumB / total;
}

float QuadNode::computeError(const Image& image, int method) {
    switch (method) {
        case 1:
            return ErrorCalculation::variance(image, x, y, width, height);
        case 2:
            return ErrorCalculation::mad(image, x, y, width, height);
        case 3:
            return ErrorCalculation::maxDiff(image, x, y, width, height);
        case 4:
            return ErrorCalculation::entropy(image, x, y, width, height);
        default:
            return 0.0f;
    }
}

void QuadNode::build(const Image& image, float threshold, int minBlockSize, int method) {
    float error = computeError(image, method);

    bool checkError = error < threshold;
    bool checkSize = (width <= minBlockSize || height <= minBlockSize);

    if (checkError || checkSize) {
        isLeaf = true;
        computeAverageColor(image);
        return;
    }

    isLeaf = false;
    int halfWidth = width / 2;
    int halfHeight = height / 2;

    children[0] = new QuadNode(x, y, halfWidth, halfHeight);
    children[1] = new QuadNode(x + halfWidth, y, width - halfWidth, halfHeight);
    children[2] = new QuadNode(x, y + halfHeight, halfWidth, height - halfHeight);
    children[3] = new QuadNode(x + halfWidth, y + halfHeight, width - halfWidth, height - halfHeight);

    for (int i = 0; i < 4; ++i) {
        children[i]->build(image, threshold, minBlockSize, method);
    }
}

void QuadNode::fill(Image& output) const {
    if (isLeaf) {
        for (int row = y; row < y + height; ++row) {
            for (int col = x; col < x + width; ++col) {
                output.setPixel(col, row, color);
            }
        }
    } else {
        for (int i = 0; i < 4; ++i) {
            if (children[i]) {
                children[i]->fill(output);
            }
        }
    }
}

int QuadNode::getDepth() const {
    if (isLeaf) return 0;
    int maxDepth = 0;
    for (int i = 0; i < 4; ++i) {
        if (children[i]) {
            maxDepth = std::max(maxDepth, children[i]->getDepth());
        }
    }
    return maxDepth + 1;
}

int QuadNode::countNodes() const {
    if (isLeaf) return 1;
    int count = 1;
    for (int i = 0; i < 4; ++i) {
        if (children[i]) {
            count += children[i]->countNodes();
        }
    }
    return count;
}