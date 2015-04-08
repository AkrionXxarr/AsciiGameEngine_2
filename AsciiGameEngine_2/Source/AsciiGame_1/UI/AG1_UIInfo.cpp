/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "AsciiGame_1\UI\AG1_UIInfo.hpp"
#include "Akropolix\Render\Windows Console\ConsoleRenderContext.hpp"

using namespace aki::render::wincon;
using namespace aki::render::I;
using namespace aki::input::wincon;

UIInfo::UIInfo(WORD primaryColor, WORD secondaryColor, WORD tertiaryColor)
{
    primary = primaryColor;
    secondary = secondaryColor;
    tertiary = tertiaryColor;

    rect.left = 51; rect.top = 51;
    rect.right = 29; rect.bottom = 29;

    uiBuffer = new CHAR_INFO[rect.right * rect.bottom];
}

UIInfo::~UIInfo()
{
}

void UIInfo::InitElement()
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

void UIInfo::Update(float deltaTime)
{

}

void UIInfo::Draw(IRenderContext& renderContext)
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

void UIInfo::Input(ConsoleInputExt& input)
{

}