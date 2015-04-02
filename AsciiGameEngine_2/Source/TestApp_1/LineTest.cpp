/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/
#include "LineTest.hpp"

// !!! Pack these includes into ConsoleObject.hpp !!! //
#include "Akropolix\render\Windows Console\ConsoleRenderContext.hpp"
#include "Akropolix\input\Windows Console\ConsoleInputExt.hpp"
#include "Akropolix\Utility\Math\Vector2f.hpp"

using namespace aki::render::wincon;
using namespace aki::input::wincon;

LineTest::LineTest(CHAR_INFO& ci)
{
    this->ci = ci;

    keyPos = new aki::math::Vector2f();
    mousePos = { 0, 0 };
}

LineTest::~LineTest()
{
    if (keyPos)
        delete keyPos;
}

void LineTest::Update(float deltaTime)
{
    if (right)
        keyPos->x += 20 * deltaTime;
    if (left)
        keyPos->x -= 20 * deltaTime;
    if (up)
        keyPos->y -= 20 * deltaTime;
    if (down)
        keyPos->y += 20 * deltaTime;
}

void LineTest::Draw(aki::render::I::IRenderContext& renderContext)
{
    ConsoleRenderContext& crc = (ConsoleRenderContext&)renderContext;

    POINT a = { keyPos->x, keyPos->y };
    CHAR_INFO t;
    t.Attributes = FOREGROUND_INTENSITY | FOREGROUND_RED;
    t.Char.UnicodeChar = 'X';

    crc.DrawLine(a, mousePos, ci);

    crc.DrawPoint(a, t);
    crc.DrawPoint(mousePos, t);
}

void LineTest::Input(aki::input::wincon::ConsoleInputExt& input)
{
    right = input.GetKeyDown(KEYBOARD::ARROW_RIGHT);
    left = input.GetKeyDown(KEYBOARD::ARROW_LEFT);
    up = input.GetKeyDown(KEYBOARD::ARROW_UP);
    down = input.GetKeyDown(KEYBOARD::ARROW_DOWN);

    if (input.GetMouseAction(MOUSE_ACTION::MOVED))
    {
        COORD c = input.GetMousePosition();
        mousePos.x = c.X;
        mousePos.y = c.Y;
    }
}