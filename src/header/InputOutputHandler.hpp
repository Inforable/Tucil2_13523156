// InputOutputHandler.hpp
#ifndef INPUT_OUTPUT_HANDLER_H
#define INPUT_OUTPUT_HANDLER_H

#include <string>
using namespace std;

class InputOutputHandler {
private:
    string inputPath;
    string outputPath;
    int method;
    float threshold;
    int minBlockSize;
public:
    InputOutputHandler(int argc, char** argv);

    string getInputPath() const;
    string getOutputPath() const;
    int getMethod() const;
    float getThreshold() const;
    int getMinBlockSize() const;
};

#endif
// end of InputOutputHandler.hpp