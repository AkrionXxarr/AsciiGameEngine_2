/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include <assert.h>

#include "Console.hpp"

////////////////////////////////
// Construct & Destruct
//

// Initialize basic console-related variables
Console::Console()
{
    ClearLogFile(DISPLAY_DEVICE_LOG);

    outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    if (outputHandle == INVALID_HANDLE_VALUE)
        LogWindowsError(DISPLAY_DEVICE_LOG);

    assert(outputHandle != INVALID_HANDLE_VALUE);
}

Console::~Console()
{
    inputHandle = nullptr;
    outputHandle = nullptr;
}


///////////////////////////
// Main functions
//

// Push the console buffer to the console, nothing more
void Console::Display()
{
    if (consoleBuffer->useDrawRect)
    {
        // Draw only a subrectangle of the buffer
        WriteConsoleOutputA(
            outputHandle, 
            consoleBuffer->buffer, 
            consoleBuffer->GetSizeAsCoord(), 
            { consoleBuffer->drawRect.Left, consoleBuffer->drawRect.Top }, 
            &consoleBuffer->drawRect
            );
    }
    else
    {
        // Draw the entire buffer
        WriteConsoleOutputA(
            outputHandle, 
            consoleBuffer->buffer, 
            consoleBuffer->GetSizeAsCoord(), 
            { 0, 0 }, 
            &screenRect
            );
    }
}

bool Console::CreateDevice(std::shared_ptr<ConsoleBuffer> cb, unsigned short cursorSize, CONSOLE_FONT_TYPE fontType)
{
    // CreateDevice was already called, clear the data and start anew
    if (consoleBuffer)
    {
        consoleBuffer.reset();
    }

    consoleBuffer = cb;
    this->fontType = fontType;

    if (!InitFont())
    {
        LogError("InitFont() failed.", DISPLAY_DEVICE_LOG);
        return false;
    }

    if (!InitSize())
    {
        LogError("InitSize() failed.", DISPLAY_DEVICE_LOG);
        return false;
    }

    if (!SetCursorSize(cursorSize))
    {
        LogError("SetCursorSize() failed.", DISPLAY_DEVICE_LOG);
        return false;
    }

    consoleWindow = GetConsoleWindow();
    if (consoleWindow == INVALID_HANDLE_VALUE)
    {
        LogWindowsError(DISPLAY_DEVICE_LOG);
        return false;
    }

    return true;
}


/////////////////////////////
// Utility functions
//

void Console::ClearBuffer(unsigned short attributes, char c)
{
    CHAR_INFO ci = { c, attributes };
    ClearBuffer(ci);
}

void Console::ClearBuffer(CHAR_INFO& ci)
{
    unsigned int size = consoleBuffer->GetSize();
    for (unsigned int i = 0; i < size; i++)
    {
        consoleBuffer->Put(i, ci);
    }
}

bool Console::HasFocus()
{
    return consoleWindow == GetForegroundWindow();
}


///////////////////////////
// Setters
//

bool Console::SetCursorSize(unsigned short size)
{
    switch (size)
    {
    case 0:
    case 1:
        cci.bVisible = false;
        cci.dwSize = 1;

    default:
        cci.bVisible = true;
        cci.dwSize = size;
    }

    if (!SetConsoleCursorInfo(outputHandle, &cci))
    {
        LogWindowsError(DISPLAY_DEVICE_LOG);
        return false;
    }

    return true;
}

bool Console::SetCursorPosition(COORD pos)
{
    cursorPos = pos;

    if (!SetConsoleCursorPosition(outputHandle, pos))
    {
        LogWindowsError(DISPLAY_DEVICE_LOG);
        return false;
    }

    return true;
}


/////////////////////////////
// Helper functions
//

bool Console::InitFont()
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);

    // Macro to help compact the if statements.
    // Compares "type" with the font type, sets cfi.dwFontSize to the x and y parameters
#define dwFontSize(type, x, y) if (fontType == type) { cfi.dwFontSize = { x, y }; }
    // ---

    if (!GetCurrentConsoleFontEx(outputHandle, NULL, &cfi))
    {
        LogWindowsError(DISPLAY_DEVICE_LOG);
        return false;
    }

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

    if (!SetCurrentConsoleFontEx(outputHandle, NULL, &cfi))
    {
        LogWindowsError(DISPLAY_DEVICE_LOG);
        return false;
    }

    return true;
}

bool Console::InitSize()
{
    SMALL_RECT temp = { 0, 0, 0, 0 };
    screenRect.Top = 0;
    screenRect.Left = 0;
    screenRect.Right = consoleBuffer->GetSizeAsCoord().X - 1;
    screenRect.Bottom = consoleBuffer->GetSizeAsCoord().Y - 1;

    // We need to shrink the window before changing the buffer size
    // or else SetConsoleScreenBufferSize may fail due to the buffer
    // being smaller than the window.
    if (!SetConsoleWindowInfo(outputHandle, TRUE, &temp))
    {
        LogWindowsError(DISPLAY_DEVICE_LOG);
        return false;
    }

    if (!SetConsoleScreenBufferSize(outputHandle, consoleBuffer->GetSizeAsCoord()))
    {
        LogWindowsError(DISPLAY_DEVICE_LOG);
        return false;
    }

    if (!SetConsoleWindowInfo(outputHandle, TRUE, &screenRect))
    {
        LogWindowsError(DISPLAY_DEVICE_LOG);
        return false;
    }

    return true;
}