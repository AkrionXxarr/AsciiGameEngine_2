/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include "Akropolix\Object\Interface\IObject.hpp"

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

namespace aki
{
    namespace object
    {
        namespace wincon
        {
            class ConsoleObject : public aki::object::I::IObject
            {
            public:
                ConsoleObject() { }
                ~ConsoleObject() { }

                virtual void Update(float deltaTime) = 0;
                virtual void Draw(render::I::IRenderContext& renderContext) = 0;

                virtual void Input(input::wincon::ConsoleInputExt& input) = 0;
            };
        }
    }
}