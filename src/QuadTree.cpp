#include "header/Quadtree.hpp"

QuadTree::QuadTree(const Image& image, float threshold, int minBlockSize, int method) {
    width = image.getWidth();
    height = image.getHeight();
    root = new QuadNode(0, 0, width, height);
    root->build(image, threshold, minBlockSize, method);
}

QuadTree::~QuadTree() {
    delete root;
}

void QuadTree::fill(Image& output) const {
    root->fill(output);
}

int QuadTree::getDepth() const {
    return root->getDepth();
}

int QuadTree::countNodes() const {
    return root->countNodes();
}