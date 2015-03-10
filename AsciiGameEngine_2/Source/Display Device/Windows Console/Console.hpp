/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

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

///////////////////////////////////////////////////////////////////////////////////////////////////
// The buffer that the Console class will render from. It has the capacity to instruct
// the console class to push the whole buffer or only a portion of the buffer.
//
// This class will be accessed through a shared pointer.
//
// Console has friend access as the raw buffer is needed for the WriteConsoleOutput function.
//
class ConsoleBuffer
{
    friend class Console;

public:
    /* Construct / Destruct */
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

    /* Buffer write */
    void Put(unsigned int i, CHAR_INFO& ci)
    {
        buffer[i] = ci;
    }
    void Put(unsigned int x, unsigned int y, CHAR_INFO& ci)
    {
        buffer[(y * width) + x] = ci;
    }

    /* Getters */
    unsigned int GetSize() { return size; }
    COORD GetSizeAsCoord() { return { width, height }; }

private:
    ConsoleBuffer(const ConsoleBuffer& other);
    void operator= (const ConsoleBuffer& other);

public:
    /* Variables */
    bool useDrawRect = false;
    SMALL_RECT drawRect;

private:
    /* Variables */
    CHAR_INFO* buffer = nullptr;
    unsigned int width, height;
    unsigned int size;
};

///////////////////////////////////////////////////////////////////////////////////////////
// Handles Windows Console relevant data and operations.
//
// Expected usage will have the render context share a pointer with the console buffer
// and for Display() to be called to push the buffer to the console window.
//
class Console
{
public:
    /* Construct & Destruct */
    Console();
    ~Console();

    /* Main functions */
    void Display(); // Push the console buffer to the console window

    bool CreateDevice(
        std::shared_ptr<ConsoleBuffer> cb,
        unsigned short cursorSize = 25,
        CONSOLE_FONT_TYPE fontType = FONT_8x12);

    std::shared_ptr<ConsoleBuffer> GetBuffer() { return consoleBuffer; }

    /* Utility functions */
    void ClearBuffer() { ClearBuffer(0, ' '); }
    void ClearBuffer(unsigned short attributes, char c);
    void ClearBuffer(CHAR_INFO& ci);

    /* Getters & Setters */
    COORD GetCursorPosition() { return cursorPos; }

    void SetCursorSize(unsigned short size = 0);
    void SetCursorPosition(short x, short y) { SetCursorPosition({ x, y }); }
    void SetCursorPosition(COORD pos);

private:
    /* Helper functions */
    void InitFont();
    void InitSize();

    // Display device should not be copied
    Console(const Console& other);
    void operator= (const Console& other);

private:
    /* Variables */
    std::shared_ptr<ConsoleBuffer> consoleBuffer;
    HANDLE outputHandle = nullptr;
    HANDLE inputHandle = nullptr;
    COORD cursorPos;
    SMALL_RECT screenRect;
    CONSOLE_CURSOR_INFO cci;
    CONSOLE_FONT_TYPE fontType = NOT_SET;
};