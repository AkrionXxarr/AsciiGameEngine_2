/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

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

class BasicRectangle : public aki::object::wincon::ConsoleObject
{
public:
    BasicRectangle(unsigned int width, unsigned int height, aki::math::Vector2f pos);
    ~BasicRectangle();

    virtual void Update(float deltaTime);
    virtual void Draw(aki::render::I::IRenderContext& renderContext);

    virtual void Input(aki::input::wincon::ConsoleInputExt& input);

private:
    aki::math::Vector2f pos;
    unsigned int width, height;
    bool up, down, left, right;
};