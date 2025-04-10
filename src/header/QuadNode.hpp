#ifndef QUADNODE_H
#define QUADNODE_H

#include "Image.hpp"

class QuadNode {
private:
    int x, y;
    int width, height;
    Pixel color; // warna rata-rata
    bool isLeaf;
    QuadNode* children[4];

public:
    // Ctor
    QuadNode(int x, int y, int width, int height);
    
    // Dtor
    ~QuadNode();

    // Menghitung warna rata-rata dari blok
    void computeAverageColor(const Image& image);

    // Melakukan Perhitungan Error
    float computeError(const Image& image, int method);

    // Membangun QuadNode
    void build(const Image& image, float threshold, int minBlockSize, int method);

    // Mengisi gambar dengan warna rata-rata
    void fill(Image& output) const;

    int getDepth() const;
    int countNodes() const;
};

#endif
// end of QuadNode.hpp