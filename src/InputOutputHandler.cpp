#include "header/InputOutputHandler.hpp"
#include <iostream>
using namespace std;

InputOutputHandler::InputOutputHandler(int argc, char** argv) {
    if (argc < 3) {
        cerr << "Format Masih Error, Ada Inputan yang Belum Anda Masukkan" << endl;
        exit(1);
    }
    inputPath = argv[1];
    outputPath = argv[2];
}

string InputOutputHandler::getInputPath() const {
    return inputPath;
}

string InputOutputHandler::getOutputPath() const {
    return outputPath;
}