/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <Windows.h>

class Vector2f;

//////////////////////////////////////////////////////////////////////////////
// This class is intended to allow for mouse and keyboard input that
// doesn't require the console to be used with Win32 functionality.
//
class ConsoleInput
{
public:
    ConsoleInput(POINT mouseFreezePos);
    ~ConsoleInput();

    // Handles all the input updates
    void Tick();

    Vector2f GetMouseDelta();

private:
    POINT lastMousePos, mouseFreezePos;
    Vector2f* mouseDelta;
};