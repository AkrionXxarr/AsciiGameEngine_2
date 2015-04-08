/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include "Akropolix\Object\Windows Console\ConsoleObject.hpp"

#include "AsciiGame_1\UI\AG1_UIInfo.hpp"
#include "AsciiGame_1\UI\AG1_UIMenu.hpp"
#include "AsciiGame_1\UI\AG1_UIMessage.hpp"
#include "AsciiGame_1\UI\AG1_UIScreen.hpp"
#include "AsciiGame_1\UI\AG1_UICommand.hpp"

// Dictates which element gets input focus
namespace UI_ELEMENT
{
    enum Type
    {
        UI_INFO,
        UI_MENU,
        UI_MESSAGE,
        UI_SCREEN,
        UI_COMMAND
    };
}

class UI : public aki::object::wincon::ConsoleObject
{
public:
    UI(WORD primaryColor, WORD secondaryColor, WORD tertiaryColor);
    virtual ~UI();

    virtual void Update(float deltaTime);
    virtual void Draw(aki::render::I::IRenderContext& renderContext);
    
    virtual void Input(aki::input::wincon::ConsoleInputExt& input);

    COORD GetUISize();

    void SetFocusedElement(UI_ELEMENT::Type element) { focusedElement = element; }

private:
    UIInfo* uiInfo;
    UIMenu* uiMenu;
    UIMessage* uiMessage;
    UIScreen* uiScreen;
    UICommand* uiCommand;

    UI_ELEMENT::Type focusedElement;
};