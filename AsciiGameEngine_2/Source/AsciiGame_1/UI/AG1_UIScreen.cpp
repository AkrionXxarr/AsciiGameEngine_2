/*UIScreen
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "AsciiGame_1\UI\AG1_UIScreen.hpp"
#include "Akropolix\Render\Windows Console\ConsoleRenderContext.hpp"

using namespace aki::render::wincon;
using namespace aki::render::I;
using namespace aki::input::wincon;

UIScreen::UIScreen(WORD primaryColor, WORD secondaryColor, WORD tertiaryColor) : Viewport({ 50, 50 })
{
    primary = primaryColor;
    secondary = secondaryColor;
    tertiary = tertiaryColor;

    rect.left = 0; rect.top = 0;
    rect.right = 52; rect.bottom = 52;

    uiBuffer = new CHAR_INFO[rect.right * rect.bottom];
}

UIScreen::~UIScreen()
{
}

// UIElement
void UIScreen::InitElement()
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

void UIScreen::Update(float deltaTime)
{
}

void UIScreen::Draw(IRenderContext& renderContext)
{
    ConsoleRenderContext& crc = (ConsoleRenderContext&)renderContext;
    
    // So many for loops! >C
    for (int y = 0; y < viewBufferSize.Y; y++)
    {
        for (int x = 0; x < viewBufferSize.X; x++)
        {
            Write(x + 1, y + 1, viewBuffer[(y * viewBufferSize.X) + x].ci);
        }
    }

    for (int y = 0; y < rect.bottom; y++)
    {
        for (int x = 0; x < rect.right; x++)
        {
            crc.DrawPoint({ x + rect.left, y + rect.top }, uiBuffer[(y * rect.right) + x]);
        }
    }
}

void UIScreen::Input(ConsoleInputExt& input)
{

}

// Viewport
void UIScreen::DrawPixel(int x, int y, CHAR_INFO& ci)
{
    if (x > 1 || y > 1 || x < (rect.right - 1) || y < (rect.bottom - 1))
        return;

    uiBuffer[(y * rect.right) + x] = ci;
}

