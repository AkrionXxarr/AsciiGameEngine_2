/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <Windows.h>
#include <deque>

#include "Input\Windows Input\ConsoleInputDefines.hpp"

struct MouseData
{
    bool moved;
    bool leftButtonPressed;
    bool rightButtonPressed;
    bool doubleClick;
    COORD pos;
};

//////////////////////////////////////////////////////////////////////////////
// This class is intended to allow for mouse and keyboard input that
// doesn't require the console to be used with Win32 functionality.
//
class ConsoleInput
{
public:
    /* Construct & Destruct*/
    ConsoleInput(unsigned int bufferLimit);
    ~ConsoleInput();

    /* ConsoleInput operations */
    void Tick();

    bool IsKeyUp(KEYBOARD key);
    bool IsKeyDown(KEYBOARD key);

    bool MouseMoved();
    bool LeftClick();
    bool RightClick();
    bool DoubleClick();

    COORD GetMousePosition();

private:
    /* Utility */
    void KeyEvent(KEY_EVENT_RECORD keyEvent);
    void MouseEvent(MOUSE_EVENT_RECORD mouseEvent);
    void UpdateMouseDesktopPos();

private:
    unsigned int bufferLimit;

    HWND consoleWindow;
    HANDLE inputHandle;

    DWORD oldMode;
    INPUT_RECORD* inputRecords;

    bool* pressedKeys;
    std::deque<KEYBOARD> releasedKeys;

    MouseData mouseData;
};