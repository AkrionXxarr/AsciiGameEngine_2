#pragma once

#include <Windows.h>

class DrawProgram
{
public:
    DrawProgram() { }
    ~DrawProgram() { }

    virtual void Draw(CHAR_INFO* consoleBuffer, COORD& bufferSize, int* zBuffer) = 0;

private:
    int depth = 0;
};