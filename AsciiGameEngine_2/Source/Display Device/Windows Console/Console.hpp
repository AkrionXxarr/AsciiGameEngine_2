#pragma once

#include <Windows.h>
#include <assert.h>
#include <memory>

// Raster fonts only
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

class ConsoleBuffer
{
public:
    ConsoleBuffer(unsigned int width, unsigned int height) : width(width), height(height)
    {
        buffer = new CHAR_INFO[width * height];
        size = width * height;
    }

    ~ConsoleBuffer()
    {
        if (buffer != nullptr)
            delete[] buffer;
    }

    void Put(unsigned int i, CHAR_INFO& ci)
    {
        buffer[i] = ci;
    }
    void Put(unsigned int x, unsigned int y, CHAR_INFO& ci)
    {
        buffer[(y * width) + x] = ci;
    }

    const CHAR_INFO* GetBuffer() const { return buffer; }

    unsigned int GetSize() { return size; }
    COORD GetSizeAsCoord() { return { width, height }; }

public:
    bool useDrawRect = false;
    SMALL_RECT drawRect;

private:
    CHAR_INFO* buffer = nullptr;
    unsigned int width, height;
    unsigned int size;
};

/*
*
*/
// Raster fonts only
class Console
{
public:
    Console();
    ~Console();

    void Display(); // Push the console buffer to the console window

    void ClearBuffer() { ClearBuffer(0, ' '); }
    void ClearBuffer(unsigned short attributes, char c);
    void ClearBuffer(CHAR_INFO& ci);


    bool CreateDevice(
        std::shared_ptr<ConsoleBuffer> cb,
        unsigned short cursorSize = 25,
        CONSOLE_FONT_TYPE fontType = FONT_8x12);

    COORD GetCursorPosition() { return cursorPos; }

    void SetCursorSize(unsigned short size = 0);
    void SetCursorPosition(short x, short y) { SetCursorPosition({ x, y }); }
    void SetCursorPosition(COORD pos);

private:
    void InitFont();
    void InitSize();

private:
    std::shared_ptr<ConsoleBuffer> consoleBuffer;
    HANDLE outputHandle = nullptr;
    HANDLE inputHandle = nullptr;
    COORD cursorPos;
    SMALL_RECT screenRect;
    CONSOLE_CURSOR_INFO cci;
    CONSOLE_FONT_TYPE fontType = NOT_SET;

private:
    // Display device should not be copied
    Console(const Console& other);
    void operator= (const Console& other);
};