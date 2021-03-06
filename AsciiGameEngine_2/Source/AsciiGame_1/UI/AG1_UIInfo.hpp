/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <string>

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

    void DrawHealth(int health, int maxHealth);

private:
    WORD primary, secondary, tertiary;

    float timeElapsed;
    unsigned int frameCount;
    std::string fps;
};