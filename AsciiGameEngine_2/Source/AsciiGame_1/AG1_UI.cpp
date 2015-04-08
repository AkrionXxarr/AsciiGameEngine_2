/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "AG1_UI.hpp"

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