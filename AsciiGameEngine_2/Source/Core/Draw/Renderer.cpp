#include <limits>

#include "Renderer.hpp"
#include "Core\Display\Console.hpp"
#include "Core\Object\Object.hpp"

Renderer::Renderer()
{
    SetBufferClearOptions(Z_BUFFER);
}

Renderer::~Renderer()
{
    if (zBuffer != nullptr)
        delete[] zBuffer;
}

void Renderer::Draw(Object* root)
{
    ClearBuffers();
    root->DrawChildren(this);
    hConsole->Display();
}

void Renderer::DrawPixel(int x, int y, int z, char c, unsigned short color)
{
    if ((x < 0) || (x >= (width - 1))) { return; }
    if ((y < 0) || (y >= (height - 1))) { return; }
    if (zBuffer[(y * width) + x] < z) { return; }

    CHAR_INFO ci;
    ci.Attributes = color;
    ci.Char.UnicodeChar = c;

    zBuffer[(y * width) + x] = z;
    hConsole->GetConsoleBuffer()[(y * width) + x] = ci;
}

void Renderer::ClearBuffers()
{
    // Check bitflags macro
#define IF_CLEAR(b) if ((bufferClearOptions & b) == b)

    IF_CLEAR(Z_BUFFER)
    {
        for (int i = 0; i < bufferSize; i++)
            zBuffer[i] = std::numeric_limits<int>::max();
    }

    IF_CLEAR(CONSOLE_BUFFER)
    {
        hConsole->ClearBuffer();
    }
}

void Renderer::SetConsoleHandle(Console* hConsole)
{
    this->hConsole = hConsole;

    width = hConsole->GetBufferSizeAsCoord().X;
    height = hConsole->GetBufferSizeAsCoord().Y;
    bufferSize = width * height;

    zBuffer = new int[hConsole->GetBufferSize()];
}

void Renderer::SetBufferClearOptions(unsigned short bufferClearOptions)
{
    this->bufferClearOptions = bufferClearOptions;
}