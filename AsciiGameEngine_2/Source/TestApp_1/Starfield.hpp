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

class Starfield : public aki::object::wincon::ConsoleObject
{
public:
    Starfield(unsigned int width, unsigned int height, unsigned int starCount, float spread, float speed, CHAR_INFO& ci);
    ~Starfield();

    virtual void Update(float deltaTime);
    virtual void Draw(aki::render::I::IRenderContext& renderContext);

    virtual void Input(aki::input::wincon::ConsoleInputExt& input) { }

private:
    void InitializeStar(int i);

private:
    unsigned int width, height, starCount;
    float spread, speed;
    aki::math::Vector3f* stars;
    CHAR_INFO ci;
};