#include "BasicRectangle.hpp"
#include "Akropolix\render\Windows Console\ConsoleRenderContext.hpp"
#include "Akropolix\input\Windows Console\ConsoleInputExt.hpp"

using namespace aki::math;
using namespace aki::render::I;
using namespace aki::render::wincon;
using namespace aki::input::wincon;

BasicRectangle::BasicRectangle(unsigned int width, unsigned int height, Vector2f pos)
{
    this->width = width;
    this->height = height;
    this->pos = pos;
}

BasicRectangle::~BasicRectangle()
{

}

void BasicRectangle::Update(float deltaTime)
{
    if (right)
        pos.x += 20 * deltaTime;
    if (left)
        pos.x -= 20 * deltaTime;
    if (up)
        pos.y -= 20 * deltaTime;
    if (down)
        pos.y += 20 * deltaTime;
}

void BasicRectangle::Draw(IRenderContext& renderContext)
{
    ConsoleRenderContext& crc = (ConsoleRenderContext&)renderContext;

    CHAR_INFO ci;

    ci.Attributes = FOREGROUND_RED;
    ci.Char.UnicodeChar = '#';

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int x = int(pos.x + (i - 1));
            int y = int(pos.y + (j - 1));

            POINT p = { x, y };

            crc.DrawPoint(p, ci);
        }
    }
}

void BasicRectangle::Input(ConsoleInputExt& input)
{
    right = input.GetKeyDown(KEYBOARD::ARROW_RIGHT);
    left = input.GetKeyDown(KEYBOARD::ARROW_LEFT);
    up = input.GetKeyDown(KEYBOARD::ARROW_UP);
    down = input.GetKeyDown(KEYBOARD::ARROW_DOWN);
}

