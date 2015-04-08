/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include "AsciiGame_1\UI\AG1_UIElement.hpp"

class UIInfo : public UIElement
{
public:
    UIInfo(WORD primaryColor, WORD secondaryColor, WORD tertiaryColor);
    ~UIInfo();

    virtual void InitElement();

    virtual void Update(float deltaTime);
    virtual void Draw(aki::render::I::IRenderContext& renderContext);

    virtual void Input(aki::input::wincon::ConsoleInputExt& input);

private:
    WORD primary, secondary, tertiary;
};