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
    root->DrawAll(this);
    hConsole->Display();
}

void Renderer::DrawPixel(int x, int y, int z, CHAR_INFO& ci)
{
    if ((x < 0) || (x >= (width - 1))) { return; }
    if ((y < 0) || (y >= (height - 1))) { return; }
    if (zBuffer[(y * width) + x] < z) { return; }

    int index = (y * width) + x;

    zBuffer[index] = z;
    hConsole->GetConsoleBuffer()[index] = ci;
}

void Renderer::DrawBuffer(int x, int y, int z, int bufWidth, int bufHeight, CHAR_INFO* buffer)
{
    // Object isn't even on the screen, skip the draw completely
    if ((x >= width) && (y >= height)) { return; }
    if (((x + bufWidth) < 0) && ((y + bufHeight) < 0)) { return; }

    CHAR_INFO* consoleBuffer = hConsole->GetConsoleBuffer();

    for (int row = 0; row < bufHeight; row++)
    {
        for (int col = 0; col < bufWidth; col++)
        {
            DrawPixel(col + x, row + y, z, buffer[(row * bufWidth) + col]);
        }
    }
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