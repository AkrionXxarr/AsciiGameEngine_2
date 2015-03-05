/*
* Copyright (c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <Windows.h>

#include "Display Device\Interface\IDisplayDevice.hpp"

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

/*
* What is required to interact with a Windows console. Only responsible for
* what data is relevant, not how that data is treated.
*/
struct IWindowsConsole
{
protected:
    HANDLE outputHandle = nullptr;
    HANDLE inputHandle = nullptr;
    CHAR_INFO* consoleBuffer = nullptr;
    COORD bufferSize = { 0, 0 };
    COORD cursorPos = { 0, 0 };
    CONSOLE_CURSOR_INFO cci = { true, 25 };
    CONSOLE_FONT_TYPE fontType = NOT_SET;

private:
    IWindowsConsole(const IWindowsConsole& other);
    void operator = (const IWindowsConsole& other);
};