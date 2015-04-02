/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/
#include "Wall.hpp"

// !!! Pack these includes into ConsoleObject.hpp !!! //
#include "Akropolix\render\Windows Console\ConsoleRenderContext.hpp"
#include "Akropolix\input\Windows Console\ConsoleInputExt.hpp"
#include "Akropolix\Utility\Math\Vector2f.hpp"

using namespace aki::render::wincon;
using namespace aki::input::wincon;
using namespace aki::math;

Wall::Wall(Vector2f pos, Vector2f dir, float speed)
{
    this->pos = pos;
    this->dir = dir.Normalized();
    this->speed = speed;
}

Wall::~Wall()
{
}

void Wall::Update(float deltaTime)
{
    if (right)
    {
        dir = dir.Rotate(20 * speed * deltaTime);
    }
    if (left)
    {
        dir = dir.Rotate(-20 * speed * deltaTime);
    }
    if (up)
    {
        pos = pos + (dir * deltaTime * speed);
    }
    if (down)
    {
        pos = pos + (-dir * deltaTime * speed);
    }
}

void Wall::Draw(aki::render::I::IRenderContext& renderContext)
{
    ConsoleRenderContext& crc = (ConsoleRenderContext&)renderContext;

    CHAR_INFO eyePoint, eyeView;
    POINT eyePos, eyeDir;
    Vector2f v = (pos + (dir * 5));

    eyePoint.Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
    eyePoint.Char.UnicodeChar = 'O';

    eyeView.Attributes = FOREGROUND_RED;
    eyeView.Char.UnicodeChar = 0x07;

    eyePos.x = int(pos.x);
    eyePos.y = int(pos.y);

    eyeDir.x = int(v.x);
    eyeDir.y = int(v.y);

    crc.DrawLine(eyePos, eyeDir, eyeView);
    crc.DrawPoint(eyePos, eyePoint);
}

void Wall::Input(aki::input::wincon::ConsoleInputExt& input)
{
    right = input.GetKeyDown(KEYBOARD::ARROW_RIGHT);
    left = input.GetKeyDown(KEYBOARD::ARROW_LEFT);
    up = input.GetKeyDown(KEYBOARD::ARROW_UP);
    down = input.GetKeyDown(KEYBOARD::ARROW_DOWN);
}