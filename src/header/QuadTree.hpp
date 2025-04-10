// QuadTree.hpp
#ifndef QUADTREE_H
#define QUADTREE_H

#include "QuadNode.hpp"
#include "Image.hpp"

class QuadTree {
private:
    QuadNode* root;
    int width, height;
public:
    // Ctor
    QuadTree(const Image& image, float threshold, int minBlockSize, int method);

    // Dtor
    ~QuadTree();

    // Mengisi gambar dengan warna rata-rata
    void fill(Image& output) const;
    
    int getDepth() const;
    int countNodes() const;
};

#endif