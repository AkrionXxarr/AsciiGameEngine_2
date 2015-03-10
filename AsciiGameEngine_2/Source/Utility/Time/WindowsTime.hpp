/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <Windows.h>

class WindowsTime
{
public:
    WindowsTime()
    {
        curTime = lastTime = GetTickCount();
        deltaTime = 0;
    }

    ~WindowsTime() { }

    void Tick()
    {
        lastTime = curTime;
        curTime = GetTickCount();
        deltaTime = curTime - lastTime;
    }

public:
    DWORD lastTime, curTime, deltaTime;
};