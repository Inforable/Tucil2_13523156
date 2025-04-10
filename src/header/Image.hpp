// Image.hpp
#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#
using namespace std;

struct Pixel {
    unsigned char r, g, b; // Warna Merah, Hijau, Biru (RGB)
};

class Image {
private:
    int width;
    int height;
    Pixel** data; // Array 2D dari Pixel

    void allocate(int w, int h);
    
    void deallocate();

public:
    Image();
    Image(int w, int h);
    ~Image();

    // Melakukan Pemuatan Gambar
    bool load(const string& path);

    // Melakukan Penyimpanan Gambar
    bool save(const string& path) const;

    void free();

    int getWidth() const;
    int getHeight() const;
    Pixel getPixel(int x, int y) const;
    void setPixel(int x, int y, const Pixel& p);
};

#endif
// end of Image.hpp