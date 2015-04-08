/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "AsciiGame_1\UI\AG1_UI.hpp"

#include "Akropolix\Render\Windows Console\ConsoleRenderContext.hpp"

using namespace aki::render::wincon;
using namespace aki::render::I;
using namespace aki::input::wincon;

UI::UI(WORD primaryColor, WORD secondaryColor, WORD tertiaryColor)
{
    this->uiInfo = new UIInfo(primaryColor, secondaryColor, tertiaryColor);
    this->uiMenu = new UIMenu(primaryColor, secondaryColor, tertiaryColor);
    this->uiMessage = new UIMessage(primaryColor, secondaryColor, tertiaryColor);
    this->uiScreen = new UIScreen(primaryColor, secondaryColor, tertiaryColor);
    this->uiCommand = new UICommand(primaryColor, secondaryColor, tertiaryColor);

    uiInfo->InitElement();
    uiMenu->InitElement();
    uiMessage->InitElement();
    uiScreen->InitElement();
    uiCommand->InitElement();

    focusedElement = UI_ELEMENT::UI_SCREEN;
}

UI::~UI()
{
    if (uiInfo)
        delete uiInfo;
    if (uiMenu)
        delete uiMenu;
    if (uiMessage)
        delete uiMessage;
    if (uiScreen)
        delete uiScreen;
    if (uiCommand)
        delete uiCommand;
}

void UI::Update(float deltaTime)
{
    uiInfo->Update(deltaTime);
    uiMenu->Update(deltaTime);
    uiMessage->Update(deltaTime);
    uiScreen->Update(deltaTime);
    if (focusedElement == UI_ELEMENT::UI_COMMAND)
        uiCommand->Update(deltaTime);
}

void UI::Draw(IRenderContext& renderContext)
{
    uiInfo->Draw(renderContext);
    uiMenu->Draw(renderContext);
    uiMessage->Draw(renderContext);
    uiScreen->Draw(renderContext);
    uiCommand->Draw(renderContext);
}

void UI::Input(ConsoleInputExt& input)
{
    switch (focusedElement)
    {
    case UI_ELEMENT::UI_INFO:
        uiInfo->Input(input);
        break;

    case UI_ELEMENT::UI_MENU:
        uiMenu->Input(input);
        break;

    case UI_ELEMENT::UI_MESSAGE:
        uiMessage->Input(input);
        break;

    case UI_ELEMENT::UI_SCREEN:
        uiScreen->Input(input);
        break;

    case UI_ELEMENT::UI_COMMAND:
        uiCommand->Input(input);
        break;
    }
}

UIElement* const UI::GetUIElement(UI_ELEMENT::Type element)
{
    UIElement* t = nullptr;

    switch (element)
    {
    case UI_ELEMENT::UI_INFO:
        t = uiInfo;
        break;

    case UI_ELEMENT::UI_MENU:
        t = uiMenu;
        break;

    case UI_ELEMENT::UI_MESSAGE:
        t = uiMessage;
        break;

    case UI_ELEMENT::UI_SCREEN:
        t = uiScreen;
        break;

    case UI_ELEMENT::UI_COMMAND:
        t = uiCommand;
        break;
    }

    return t;
}

UI_ELEMENT::Type UI::GetFocusedElement()
{
    return focusedElement;
}

void UI::SetFocusedElement(UI_ELEMENT::Type element)
{
    if (element != focusedElement)
    {
        GetUIElement(focusedElement)->OnLoseFocus();
        focusedElement = element;
        GetUIElement(focusedElement)->OnGainFocus();
    }
}