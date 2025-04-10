#include <iostream>
#include <chrono>
#include <sstream>
#include <filesystem>
#include "header/InputHandler.hpp"
#include "header/Image.hpp"
#include "header/QuadTree.hpp"

namespace fs = std::filesystem;
using namespace std;

int main(int argc, char** argv) {
    InputHandler io;

    try {
        int choice;
        while (true) {
            cout << "========== INPUT ==========" << endl;
            cout << "Pilih Cara untuk Input: " << endl;
            cout << "1. Input dalam Satu Baris Sekaligus dengan format (<input path> <output path> <Metode> <threshold> <minBlockSize>)" << endl;
            cout << "2. Input Satu per Satu" << endl;
            cout << "Pilihan: ";

            string line;
            getline(cin, line);
            stringstream ss(line);
            if (!(ss >> choice)) {
                cout << "Input harus berupa angka!\n";
                continue;
            }

            if (choice == 1) {
                io.InputSingleLine();
                break;
            } else if (choice == 2) {
                io.InputOnebyOne();
                break;
            } else {
                cerr << "Pilihan tidak valid." << endl;
            }
        }

        Image img;
        if (!img.load(io.getInputPath())) {
            cerr << "Gagal Memuat Gambar" << endl;
            return 1;
        }

        uintmax_t sizeBefore = fs::file_size(io.getInputPath());

        cout << "Gambar dimuat: " << img.getWidth() << "x" << img.getHeight() << endl;

        auto start = chrono::high_resolution_clock::now();

        cout << "Memulai kompresi..." << endl; // debugging
        QuadTree QT(img, io.getThreshold(), io.getMinBlockSize(), io.getMethod());
        cout << "Kompresi selesai." << endl; // debugging
        
        Image compressed(img.getWidth(), img.getHeight());
        QT.fill(compressed);

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

        if (!compressed.save(io.getOutputPath())) {
            cerr << "Gagal Menyimpan Gambar" << endl;
            return 1;
        }

        uintmax_t sizeAfter = fs::file_size(io.getOutputPath());

        double compressionPercentage = (1.0 - static_cast<double>(sizeAfter) / sizeBefore) * 100.0;

        cout << endl <<  "========== OUTPUT ==========" << endl;
        cout << "Gambar disimpan: " << io.getOutputPath() << endl;
        cout << "Ukuran gambar sebelum kompresi: " << sizeBefore << " bytes" << endl;
        cout << "Ukuran gambar setelah kompresi: " << sizeAfter << " bytes" << endl;
        cout << "Persentase kompresi: " << compressionPercentage << "%" << endl;
        cout << "Waktu kompresi: " << duration << " ms" << endl;
        cout << "Kedalaman QuadTree: " << QT.getDepth() << endl;
        cout << "Jumlah node: " << QT.countNodes() << endl;
    } catch (const exception& e) {
        cerr << "Terjadi kesalahan: " << e.what() << endl;
        return 1;
    }
    return 0;
}