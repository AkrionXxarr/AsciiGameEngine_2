/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <Windows.h>
#include <deque>

namespace Math
{
    class Vector2f;
}

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

    /* Peek & Get */
    KEY_EVENT_RECORD PeekKeyEvent();
    KEY_EVENT_RECORD GetKeyEvent();
    unsigned int GetKeyEventCount();

    MOUSE_EVENT_RECORD PeekMouseEvent();
    MOUSE_EVENT_RECORD GetMouseEvent();
    unsigned int GetMouseEventCount();

    POINT PeekMouseScreenPos();
    POINT GetMouseScreenPos();
    unsigned int GetMouseScreenPosCount();

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

    std::deque<POINT> mouseScreenPos;
    std::deque<KEY_EVENT_RECORD> keyboardEvents;
    std::deque<MOUSE_EVENT_RECORD> mouseEvents;
};