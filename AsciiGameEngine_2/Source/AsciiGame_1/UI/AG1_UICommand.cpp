/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "AsciiGame_1\UI\AG1_UICommand.hpp"
#include "Akropolix\Render\Windows Console\ConsoleRenderContext.hpp"

using namespace aki::render::wincon;
using namespace aki::render::I;
using namespace aki::input::wincon;

UICommand::UICommand(WORD primaryColor, WORD secondaryColor, WORD tertiaryColor)
{
    primary = primaryColor;
    secondary = secondaryColor;
    tertiary = tertiaryColor;

    cmdPos = 0;

    rect.left = 0; rect.top = 51;
    rect.right = 52; rect.bottom = 3;

    prePadding = 2; // Space before the >
    postPadding = 2; // Space after the >
    maxCmdLength = ((rect.right - 2) - prePadding) - postPadding;

    cursorIsShowing = true;
    cursorFlashInterval = 0.5f;
    cursorFlashTime = 0;

    uiBuffer = new CHAR_INFO[rect.right * rect.bottom];
}

UICommand::~UICommand()
{
}

void UICommand::InitElement()
{
    CHAR_INFO ci;
    POINT size = GetSize();

    ci.Attributes = tertiary;
    ci.Char.UnicodeChar = 0x08;

    // Corners
    Write(0, 0, ci); // Top left
    Write(size.x - 1, 0, ci); // Top right
    Write(0, size.y - 1, ci); // Bottom left
    Write(size.x - 1, size.y - 1, ci); // Bottom right

    ci.Attributes = primary;

    // Top and Bottom edges
    ci.Char.UnicodeChar = 0xCD;
    for (int x = 1; x < (size.x - 1); x++)
    {
        Write(x, 0, ci); // Top
        Write(x, size.y - 1, ci); // Bottom
    }

    // Left and Right edges
    ci.Char.UnicodeChar = 0xBA;
    for (int y = 1; y < (size.y - 1); y++)
    {
        Write(0, y, ci); // Left
        Write(size.x - 1, y, ci); // Right
    }

    // Center
    ci.Attributes = 0;
    ci.Char.UnicodeChar = ' ';
    for (int y = 1; y < (size.y - 1); y++)
    {
        for (int x = 1; x < (size.x - 1); x++)
        {
            Write(x, y, ci);
        }
    }
}

void UICommand::Update(float deltaTime)
{
    // Write the current input to the buffer
    CHAR_INFO ci;

    ci.Attributes = tertiary;
    ci.Char.UnicodeChar = '>';

    Write(prePadding, 1, ci);

    ci.Attributes = secondary;

    int x = 0;
    for (x; x < command.size(); x++)
    {
        ci.Char.UnicodeChar = command[x];

        Write(x + (prePadding + postPadding), 1, ci);
    }

    for (int t = x; t < maxCmdLength; t++)
    {
        ci.Char.UnicodeChar = ' ';
        Write(t + (prePadding + postPadding), 1, ci);
    }

    if (cursorIsShowing)
    {
        if (x < maxCmdLength)
        {
            ci.Attributes = tertiary;
            ci.Char.UnicodeChar = 0xDB;
            Write(x + (prePadding + postPadding), 1, ci);
        }
    }

    cursorFlashTime += deltaTime;

    if (cursorFlashTime >= cursorFlashInterval)
    {
        cursorFlashTime = 0;
        cursorIsShowing = !cursorIsShowing;
    }
}

void UICommand::Draw(IRenderContext& renderContext)
{
    ConsoleRenderContext& crc = (ConsoleRenderContext&)renderContext;

    for (int y = 0; y < rect.bottom; y++)
    {
        for (int x = 0; x < rect.right; x++)
        {
            crc.DrawPoint({ x + rect.left, y + rect.top }, uiBuffer[(y * rect.right) + x]);
        }
    }
}

void UICommand::Input(ConsoleInputExt& input)
{
    if (input.GetAnyKeyDown())
    {
        char c = input.GetCharacter();
        KEYBOARD::TYPE key = input.GetMostRecentKeyDown();

        switch (c)
        {
        case 0: // Invalid
            break;

        case 0x08: // Backspace
            if (cmdPos > 0)
            {
                cursorFlashTime = 0; // Reset to halt the flash while typing
                cursorIsShowing = true; // Make sure cursor can be seen while typing
                command.pop_back();
                cmdPos--;
            }
            break;

        case 0x09: // Tab
            break;

        default:
            if (cmdPos < maxCmdLength)
            {
                cursorFlashTime = 0; // Reset to halt the flash while typing
                cursorIsShowing = true; // Make sure cursor can be seen while typing
                command.push_back(c);
                cmdPos++;
            }
        }
    }
}

void UICommand::OnGainFocus()
{
    cursorIsShowing = true;
}

void UICommand::OnLoseFocus()
{
    ClearCommandLine();
}

void UICommand::ClearCommandLine()
{
    CHAR_INFO ci;

    ci.Attributes = 0;
    ci.Char.UnicodeChar = ' ';

    for (int x = 1; x < (rect.right - 1); x++)
    {
        Write(x, 1, ci);
    }

    command = "";
    cmdPos = 0;
}