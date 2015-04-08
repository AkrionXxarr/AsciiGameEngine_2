/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <string>

#include "AsciiGame_1\UI\AG1_UIElement.hpp"
#include "Akropolix\Input\Windows Console\ConsoleInputExt.hpp"

class UICommand : public UIElement
{
public:
    UICommand(WORD primaryColor, WORD secondaryColor, WORD tertiaryColor);
    ~UICommand();

    virtual void InitElement();

    virtual void Update(float deltaTime);
    virtual void Draw(aki::render::I::IRenderContext& renderContext);

    virtual void Input(aki::input::wincon::ConsoleInputExt& input);

    virtual void OnGainFocus();
    virtual void OnLoseFocus();

    std::string GetCommand() { return command; }

private:
    void ClearCommandLine();

private:
    WORD primary, secondary, tertiary;

    std::string command;
    unsigned int cmdPos;
    unsigned int prePadding, postPadding;
    unsigned int maxCmdLength;

    aki::input::wincon::KEYBOARD::TYPE lastKey;
};