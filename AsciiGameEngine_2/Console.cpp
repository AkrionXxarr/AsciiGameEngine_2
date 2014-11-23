#include <assert.h>

#include "Console.hpp"

// Collect parameters, get and verify the output handle, initialize the console
Console::Console(unsigned short width, unsigned short height, CONSOLE_FONT_TYPE fontType)
{
    bufferSize = { width, height };
    consoleBuffer = new CHAR_INFO[width * height];
    outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    this->fontType = fontType;

    assert(outputHandle != INVALID_HANDLE_VALUE);

    InitFont();
    InitSize();

    SetCursorSize(25);
}

Console::~Console()
{
    if (consoleBuffer != nullptr)
        delete[] consoleBuffer;
}

// Push the console buffer to the console, nothing more.
void Console::Display()
{
    WriteConsoleOutput(outputHandle, consoleBuffer, bufferSize, { 0, 0 }, &screenRect);
}

void Console::ClearBuffer(unsigned short clearColor)
{
    for (int i = 0; i < GetBufferSize(); i++)
    {
        consoleBuffer[i].Attributes = clearColor;
        consoleBuffer[i].Char.UnicodeChar = ' ';
    }
}

void Console::SetCursorSize(unsigned short size)
{
    switch (size)
    {
    case 0:
    case 1:
        cci.bVisible = false;
        cci.dwSize = 1;
        break;

    default:
        cci.bVisible = true;
        cci.dwSize = size;
    };

    SetConsoleCursorInfo(outputHandle, &cci);
}

void Console::SetCursorPosition(COORD pos)
{
    cursorPos = pos;
    SetConsoleCursorPosition(outputHandle, pos);
}

void Console::InitFont()
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);

    // Macro to help compact the if statements.
    // Compares "type" with the font type, sets cfi.dwFontSize to the x and y parameters
#define dwFontSize(type, x, y) if (fontType == type) { cfi.dwFontSize = { x, y }; }
    // ---

    GetCurrentConsoleFontEx(outputHandle, NULL, &cfi);
    cfi.FontWeight = 400;
    cfi.nFont = fontType;

    dwFontSize(FONT_4x6, 4, 6);
    dwFontSize(FONT_6x8, 6, 8);
    dwFontSize(FONT_8x8, 8, 8);
    dwFontSize(FONT_16x8, 16, 8);
    dwFontSize(FONT_5x12, 5, 12);
    dwFontSize(FONT_7x12, 7, 12);
    dwFontSize(FONT_8x12, 8, 12);
    dwFontSize(FONT_16x12, 16, 12);
    dwFontSize(FONT_12x16, 12, 16);
    dwFontSize(FONT_10x18, 10, 18);

    SetCurrentConsoleFontEx(outputHandle, NULL, &cfi);
}

void Console::InitSize()
{
    screenRect.Top = 0;
    screenRect.Left = 0;
    screenRect.Right = bufferSize.X - 1;
    screenRect.Bottom = bufferSize.Y - 1;

    SetConsoleScreenBufferSize(outputHandle, bufferSize);
    SetConsoleWindowInfo(outputHandle, TRUE, &screenRect);
}