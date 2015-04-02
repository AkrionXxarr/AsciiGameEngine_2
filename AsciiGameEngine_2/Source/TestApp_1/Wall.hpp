/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <Windows.h>

#include "Akropolix\Object\Windows Console\ConsoleObject.hpp"
#include "Akropolix\Utility\Math\Vector2f.hpp"

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

class Wall : public aki::object::wincon::ConsoleObject
{
public:
    Wall(aki::math::Vector2f pos, aki::math::Vector2f dir, float speed);
    ~Wall();

    virtual void Update(float deltaTime);
    virtual void Draw(aki::render::I::IRenderContext& renderContext);

    virtual void Input(aki::input::wincon::ConsoleInputExt& input);

private:
    aki::math::Vector2f pos, dir;

    float speed;
    bool right, left, up, down;
};