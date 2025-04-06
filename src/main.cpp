#include <iostream>
#include "header/InputOutputHandler.hpp"
#include "header/Image.hpp"
using namespace std;

int main(int argc, char** argv) {
    InputOutputHandler io(argc, argv);

    Image img;
    if (!img.load(io.getInputPath())) {
        cerr << "Gagal Memuat Gambar" << endl;
        return 1;
    }

    cout << "Gambar dimuat: " << img.getWidth() << "x" << img.getHeight() << endl;

    if (!img.save(io.getOutputPath())) {
        cerr << "Gagal Menyimpan Gambar" << endl;
        return 1;
    }

    cout << "Gambar Disimpan di: " << io.getOutputPath() << endl;
    return 0;
}