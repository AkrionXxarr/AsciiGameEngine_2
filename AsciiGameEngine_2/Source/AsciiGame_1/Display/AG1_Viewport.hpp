/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <Windows.h>

struct ViewBuffer
{
    CHAR_INFO ci;
    int depth;
};

class Viewport
{
public:
    Viewport(COORD size) 
    { 
        this->viewBufferSize = size;
        viewBuffer = new ViewBuffer[size.X * size.Y];

        CHAR_INFO ci;
        ci.Attributes = 0;
        ci.Char.UnicodeChar = ' ';

        for (int i = 0; i < (size.X * size.Y); i++)
        {
            viewBuffer[i].ci = ci;
            viewBuffer[i].depth = 0;
        }
    }
    virtual ~Viewport() 
    { 
        if (viewBuffer)
            delete[] viewBuffer;
    }

public:
    ViewBuffer* viewBuffer;
    COORD viewBufferSize;
};