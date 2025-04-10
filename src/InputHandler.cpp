#include "header/InputHandler.hpp"
#include <iostream>
#include <sstream>
using namespace std;

InputHandler::InputHandler() {
}

bool InputHandler::validate() {

    bool valid = true;
    if (method < 1 || method > 4) {
        cerr << "Metode tidak valid" << endl;
        valid = false;
    }
    if (threshold < 0) {
        cerr << "Threshold tidak valid. Masukkan angka >= 0." << endl;
        valid = false;
    }
    if (minBlockSize <= 0) {
        cerr << "Ukuran minimum blok tidak valid. Masukkan angka > 0." << endl;
        valid = false;
    }
    return valid;
}

void InputHandler::InputSingleLine() {
    string line;
    while (true) {
        cout << "Pilihan Metode Pengukuran Error: " << endl;
        cout << "1. Variance" << endl;
        cout << "2. Mean Absolute Deviation (MAD)" << endl;
        cout << "3. Max Pixel Difference" << endl;
        cout << "4. Entropy" << endl;
        cout << "Masukkan input dalam satu baris (<input path> <output path> <Metode> <threshold> <minBlockSize>): ";
        getline(cin, line);
        stringstream ss(line);
        ss >> inputPath >> outputPath >> method >> threshold >> minBlockSize;
        if (validate()) {
            break;
        } 
        cout << "Input tidak valid. Silakan coba lagi." << endl;
    }
}

void InputHandler::InputOnebyOne() {
    while (true) {
        cout << "Masukkan path gambar input: ";
        getline(cin, inputPath);

        cout << "Masukkan path gambar output: ";
        getline(cin, outputPath);

        string line;

        while (true) {
            cout << "Pilihan Metode Pengukuran Error: " << endl;
            cout << "1. Variance" << endl;
            cout << "2. Mean Absolute Deviation (MAD)" << endl;
            cout << "3. Max Pixel Difference" << endl;
            cout << "4. Entropy" << endl;
            cout << "Pilih metode error: ";
            getline(cin, line);
            stringstream ss(line);
            if (ss >> method && method >= 1 && method <= 4) break;
            cout << "Metode tidak valid. Masukkan angka antara 1 sampai 4.\n";
        }

        while (true) {
            cout << "Masukkan threshold (>= 0): ";
            getline(cin, line);
            stringstream ss(line);
            if (ss >> threshold && threshold >= 0) break;
            cout << "Threshold tidak valid. Masukkan angka >= 0.\n";
        }

        while (true) {
            cout << "Masukkan minimum block size (> 0): ";
            getline(cin, line);
            stringstream ss(line);
            if (ss >> minBlockSize && minBlockSize > 0) break;
            cout << "Ukuran minimum blok tidak valid. Masukkan angka > 0.\n";
        }
        break;
    }
}

string InputHandler::getInputPath() const {
    return inputPath;
}

string InputHandler::getOutputPath() const {
    return outputPath;
}

int InputHandler::getMethod() const {
    return method;
}

float InputHandler::getThreshold() const {
    return threshold;
}

int InputHandler::getMinBlockSize() const {
    return minBlockSize;
}