/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <Windows.h>

#include "Akropolix\Object\Windows Console\ConsoleObject.hpp"
#include "Akropolix\Utility\Math\Vector3f.hpp"

namespace aki
{
    namespace input
    {
        namespace wincon
        {
            class ConsoleInputExt;
        }
    }
}

class LineTest : public aki::object::wincon::ConsoleObject
{
public:
    LineTest(CHAR_INFO& ci);
    ~LineTest();

    virtual void Update(float deltaTime);
    virtual void Draw(aki::render::I::IRenderContext& renderContext);

    virtual void Input(aki::input::wincon::ConsoleInputExt& input);

private:
    aki::math::Vector2f* keyPos;
    POINT mousePos;
    CHAR_INFO ci;
    bool right, left, up, down;
};