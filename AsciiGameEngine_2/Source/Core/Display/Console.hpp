#pragma once

#include "ConsoleDefines.hpp"

enum CONSOLE_FONT_TYPE
{
    FONT_4x6,
    FONT_6x8,
    FONT_8x8,
    FONT_16x8,
    FONT_5x12,
    FONT_7x12,
    FONT_8x12,
    FONT_16x12,
    FONT_12x16,
    FONT_10x18,
    NOT_SET
};

class Console
{
public:
    Console(unsigned short width, unsigned short height, CONSOLE_FONT_TYPE fontType = FONT_8x12);
    ~Console();

    void Display(); // Push the console buffer to the console window
    void ClearBuffer() { ClearBuffer(0); }
    void ClearBuffer(unsigned short clearColor); // Clear the buffer, clearColor is optional and defaults to black

    unsigned int GetBufferSize() { return bufferSize.X * bufferSize.Y; }
    COORD GetBufferSizeAsCoord() { return bufferSize; }
    CHAR_INFO* GetConsoleBuffer() { return consoleBuffer; }

    void SetCursorSize(unsigned short size = 0);
    void SetCursorPosition(short x, short y) { SetCursorPosition({ x, y }); }
    void SetCursorPosition(COORD pos);

private:
    void InitFont();
    void InitSize();

private:
    COORD bufferSize;
    COORD cursorPos;
    CONSOLE_FONT_TYPE fontType = NOT_SET;
    SMALL_RECT screenRect;
    CONSOLE_CURSOR_INFO cci;

    HANDLE outputHandle = nullptr;
    CHAR_INFO* consoleBuffer = nullptr;
};