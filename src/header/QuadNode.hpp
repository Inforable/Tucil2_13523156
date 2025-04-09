// QuadNode.hpp
#ifndef QUADNODE_H
#define QUADNODE_H

#include "Image.hpp"

class QuadNode {
private:
    int x;
    int y;
    int width, height;
    Pixel color; // Warna rata-rata dari blok
    bool isLeaf;
    QuadNode* children[4]; // Array untuk menyimpan 4 anak node
public:
    QuadNode(int x, int y, int width, int height);
    ~QuadNode();

    void computeAverageColor(const Image& image);
    float computeError(const Image& image, int method);
    void build(const Image& image, float threshold, int minBlockSize, int method);
    void fill(Image& ouput) const;

    int getDepth() const;
    int countNodes() const;
};

#endif
// end of QuadNode.hpp