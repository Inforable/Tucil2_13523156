#include "header/InputOutputHandler.hpp"
#include <iostream>
using namespace std;

InputOutputHandler::InputOutputHandler(int argc, char** argv) {
    if (argc < 6) {
        cerr << "Format Masih Error, Ada Inputan yang Belum Anda Masukkan" << endl;
        exit(1);
    }
    inputPath = argv[1];
    outputPath = argv[2];
    method = stoi(argv[3]);
    threshold = stof(argv[4]);
    minBlockSize = stoi(argv[5]);
}

string InputOutputHandler::getInputPath() const {
    return inputPath;
}

string InputOutputHandler::getOutputPath() const {
    return outputPath;
}

int InputOutputHandler::getMethod() const {
    return method;
}

float InputOutputHandler::getThreshold() const {
    return threshold;
}

int InputOutputHandler::getMinBlockSize() const {
    return minBlockSize;
}