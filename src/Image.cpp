#include "header/Image.hpp"
#include "header/FreeImage.h"
#include <iostream>
#include <stdexcept>
using namespace std;

Image::Image() {
    width = 0;
    height = 0;
    data = nullptr;
}

Image::~Image() {
    deallocate();
}

bool Image::load(const string& path) {
    FreeImage_Initialise();

    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path.c_str(), 0);
    if (format == FIF_UNKNOWN) {
        format = FreeImage_GetFIFFromFilename(path.c_str());
    }

    if (format == FIF_UNKNOWN) {
        cerr << "Format Gambar Tidak Diketahui " << path << endl; // debugging
        return false;
    }

    FIBITMAP* bitmap = FreeImage_Load(format, path.c_str());

    if (!bitmap) {
        cerr << "Tidak Dapat Memuat Gambar: " << path << endl; // debugging
        return false;
    }

    FIBITMAP* rgb = FreeImage_ConvertTo24Bits(bitmap);
    FreeImage_Unload(bitmap);

    this->width = FreeImage_GetWidth(rgb);
    this->height = FreeImage_GetHeight(rgb);
    BYTE* bits = FreeImage_GetBits(rgb);

    allocate(this->width, this->height);

    for (int row = 0; row < this->height; row++) {
        for (int col = 0; col < this->width; col++) {
            BYTE* pixel = bits + (row * FreeImage_GetPitch(rgb)) + (col * 3);
            data[row][col] = { pixel[2], pixel[1], pixel[0] }; // RGB order
        }
    }

    FreeImage_Unload(rgb);
    FreeImage_DeInitialise();
    return true;
}

bool Image::save(const string& path) const {
    FreeImage_Initialise();

    FIBITMAP* bitmap = FreeImage_Allocate(this->width, this->height, 24);
    if (!bitmap) {
        cerr << "Tidak Dapat Mengalokasikan Gambar: " << path << endl; // debugging
        return false;
    }

    for (int row = 0; row < this->height; row++) {
        for (int col = 0; col < this->width; col++) {
            RGBQUAD color;
            color.rgbRed = data[row][col].r;
            color.rgbGreen = data[row][col].g;
            color.rgbBlue = data[row][col].b;
            FreeImage_SetPixelColor(bitmap, col, row, &color);
        }
    }

    FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(path.c_str());
    if (!FreeImage_Save(format, bitmap, path.c_str(), 0)) {
        cerr << "Tidak Dapat Menyimpan Gambar: " << path << endl; // debugging
        FreeImage_Unload(bitmap);
        FreeImage_DeInitialise();
        return false;
    }

    FreeImage_Unload(bitmap);
    FreeImage_DeInitialise();
    return true;
}

void Image::allocate(int w, int h) {
    this->width = w;
    this->height = h;
    data = new Pixel*[this->height];
    for (int i = 0; i < this->height; i++) {
        data[i] = new Pixel[this->width];
    }
}

void Image::deallocate() {
    if (data) {
        for (int i = 0; i < this->height; i++) {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr;
    }
}

Pixel Image::getPixel(int x, int y) const {
    return data[y][x];
}

void Image::setPixel(int x, int y, const Pixel& p) {
    data[y][x] = p;
}

int Image::getWidth() const {
    return this->width;
}

int Image::getHeight() const {
    return this->height;
}

void Image::free() {
    deallocate();
}