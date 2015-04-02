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

class Camera : public aki::object::wincon::ConsoleObject
{
public:
    Camera(
        aki::math::Vector2f pos, 
        aki::math::Vector2f dir, 
        float speed,
        aki::math::Vector2f wallA,
        aki::math::Vector2f wallB);
    ~Camera();

    virtual void Update(float deltaTime);
    virtual void Draw(aki::render::I::IRenderContext& renderContext);

    virtual void Input(aki::input::wincon::ConsoleInputExt& input);

private:
    aki::math::Vector2f pos, dir;
    aki::math::Vector2f wallA, wallB;

    float speed;
    float angle;
    bool sRight, sLeft, tRight, tLeft, forward, backward;
};