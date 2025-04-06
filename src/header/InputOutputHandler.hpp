// InputOutputHandler.hpp
#ifndef INPUT_OUTPUT_HANDLER_H
#define INPUT_OUTPUT_HANDLER_H

#include <string>
using namespace std;

class InputOutputHandler {
private:
    string inputPath;
    string outputPath;

public:
    InputOutputHandler(int argc, char** argv);

    string getInputPath() const;
    string getOutputPath() const;
};

#endif
// end of InputOutputHandler.hpp