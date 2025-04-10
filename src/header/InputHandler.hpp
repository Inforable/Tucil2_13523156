// InputHandler.hpp
#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <string>
using namespace std;

class InputHandler {
private:
    string inputPath;
    string outputPath;
    int method;
    float threshold;
    int minBlockSize;

    bool checkValid();
public:
    InputHandler();

    void InputSingleLine();

    void InputOnebyOne();

    string getInputPath() const;
    string getOutputPath() const;
    int getMethod() const;
    float getThreshold() const;
    int getMinBlockSize() const;
};

#endif
// end of InputHandler.hpp