/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include "AG1_UIElement.hpp"

class UIScreen : public UIElement
{
public:
    UIScreen(WORD primaryColor, WORD secondaryColor, WORD tertiaryColor);
    ~UIScreen();

    virtual void InitElement();

    virtual void Update(float deltaTime);
    virtual void Draw(aki::render::I::IRenderContext& renderContext);

    virtual void Input(aki::input::wincon::ConsoleInputExt& input);

private:
    WORD primary, secondary, tertiary;
};