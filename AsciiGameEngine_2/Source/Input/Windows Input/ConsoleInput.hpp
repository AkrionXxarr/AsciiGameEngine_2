/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <Windows.h>

class Vector2f;

class ConsoleInput
{
public:
    ConsoleInput(POINT mouseFreezePos);
    ~ConsoleInput();

    void Tick();

    Vector2f GetMouseDelta();

private:
    POINT lastMousePos, mouseFreezePos;
    Vector2f* mouseDelta;
};