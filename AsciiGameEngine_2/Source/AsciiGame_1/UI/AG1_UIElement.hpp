/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <Windows.h>

#include "Akropolix\Object\Windows Console\ConsoleObject.hpp"

class UIElement : public aki::object::wincon::ConsoleObject
{
public:
    UIElement() { uiBuffer = nullptr;  }
    virtual ~UIElement() { if (uiBuffer) delete[] uiBuffer; }

    virtual void InitElement() = 0;

    virtual void Update(float deltaTime) { }
    virtual void Draw(aki::render::I::IRenderContext& renderContext) { }

    virtual void Input(aki::input::wincon::ConsoleInputExt& input) { }

    virtual void OnGainFocus() { }
    virtual void OnLoseFocus() { }

    POINT GetPosition() { return { rect.left, rect.top }; }
    POINT GetSize() { return{ rect.right, rect.bottom }; }
    RECT GetRect() { return rect; }

protected:
    void Write(int x, int y, CHAR_INFO& ci)
    {
        if (x < 0 || y < 0 || x > rect.right || y > rect.bottom)
            return;

        uiBuffer[(y * rect.right) + x] = ci;
    }

protected:
    RECT rect;
    CHAR_INFO* uiBuffer;
};