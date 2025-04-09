#include <iostream>
#include <chrono>
#include "header/InputOutputHandler.hpp"
#include "header/Image.hpp"
#include "header/QuadTree.hpp"
using namespace std;

int main(int argc, char** argv) {
    try {
        InputOutputHandler io(argc, argv);

        int method = io.getMethod();
        if (method < 1 || method > 4) {
            cerr << "Metode Tidak Valid" << endl;
            return 1;
        }

        float threshold = io.getThreshold();
        int minBlockSize = io.getMinBlockSize();

        if (threshold < 0) {
            cerr << "Threshold Tidak Valid" << endl;
            return 1;
        }

        if (minBlockSize <= 0) {
            cerr << "Ukuran Blok Minimum Tidak Valid" << endl;
            return 1;
        }

        Image img;
        if (!img.load(io.getInputPath())) {
            cerr << "Gagal Memuat Gambar" << endl;
            return 1;
        }

        cout << "Gambar dimuat: " << img.getWidth() << "x" << img.getHeight() << endl;

        auto start = chrono::high_resolution_clock::now();

        cout << "Memulai kompresi..." << endl; // debugging
        QuadTree QT(img, threshold, minBlockSize, method);
        cout << "Kompresi selesai." << endl; // debugging
        
        Image compressed(img.getWidth(), img.getHeight());
        QT.fill(compressed);

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

        if (!compressed.save(io.getOutputPath())) {
            cerr << "Gagal Menyimpan Gambar" << endl;
            return 1;
        }

        cout << "Gambar disimpan: " << io.getOutputPath() << endl;
        cout << "Waktu kompresi: " << duration << " ms" << endl;
        cout << "Kedalaman QuadTree: " << QT.getDepth() << endl;
        cout << "Jumlah node: " << QT.countNodes() << endl;
    } catch (const exception& e) {
        cerr << "Terjadi kesalahan: " << e.what() << endl;
        return 1;
    }
    return 0;
}