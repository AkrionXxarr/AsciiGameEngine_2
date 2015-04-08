/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include "AsciiGame_1\UI\AG1_UIElement.hpp"

class UIMessage : public UIElement
{
public:
    UIMessage(WORD primaryColor, WORD secondaryColor, WORD tertiaryColor);
    ~UIMessage();

    virtual void InitElement();

    virtual void Update(float deltaTime);
    virtual void Draw(aki::render::I::IRenderContext& renderContext);

private:
    WORD primary, secondary, tertiary;
};