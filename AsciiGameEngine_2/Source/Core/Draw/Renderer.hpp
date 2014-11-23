#pragma once

#define Z_BUFFER       0x0001
#define CONSOLE_BUFFER 0x0002

#include "Core\Display\Console.hpp"

class Object;

// Manages general rendering resources such as the handle to the console, zbuffer, etc.
class Renderer
{
public:
    Renderer();
    ~Renderer();

    void Draw(Object* root);
    void DrawPixel(int x, int y, int z, char c, unsigned short color);

    void ClearBuffers();

    void SetConsoleHandle(Console* hConsole);
    void SetBufferClearOptions(unsigned short bufferClearOptions);

private:
    Console* hConsole = nullptr;
    unsigned short width, height;
    unsigned int bufferSize;
    int* zBuffer = nullptr;
    unsigned short bufferClearOptions;
};