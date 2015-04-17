/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include "AsciiGame_1\UI\AG1_UIElement.hpp"
#include "AsciiGame_1\Display\AG1_Viewport.hpp"

class UIScreen : public UIElement, public Viewport
{
public:
    UIScreen(WORD primaryColor, WORD secondaryColor, WORD tertiaryColor);
    ~UIScreen();

    // UIElement
    virtual void InitElement();

    virtual void Update(float deltaTime);
    virtual void Draw(aki::render::I::IRenderContext& renderContext);

    virtual void Input(aki::input::wincon::ConsoleInputExt& input);

    // Viewport
    virtual void DrawPixel(int x, int y, CHAR_INFO& ci);

private:
    WORD primary, secondary, tertiary;
};