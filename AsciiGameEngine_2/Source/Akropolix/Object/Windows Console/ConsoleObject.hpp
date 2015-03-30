/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include "Akropolix\Object\Interface\IObject.hpp"

namespace Akropolix
{
    namespace Input
    {
        namespace WinConsole
        {
            class ConsoleInputExt;
        }
    }

    namespace Object
    {
        namespace WinConsole
        {
            class ConsoleObject : public Akropolix::Object::Interface::IObject
            {
            public:
                ConsoleObject() { }
                ~ConsoleObject() { }

                virtual void Update(float deltaTime) = 0;
                virtual void Draw(Render::Interface::IRenderContext& renderContext) = 0;

                virtual void Input(Input::WinConsole::ConsoleInputExt& input) = 0;
            };
        }
    }
}