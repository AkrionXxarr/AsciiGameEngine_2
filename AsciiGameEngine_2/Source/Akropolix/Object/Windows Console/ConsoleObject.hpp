/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include "Akropolix\Object\Interface\IObject.hpp"

namespace Akropolix
{
    class ConsoleInputExt;

    class ConsoleObject : public IObject
    {
    public:
        ConsoleObject() { }
        ~ConsoleObject() { }

        virtual void Update(float deltaTime) = 0;
        virtual void Draw(IRenderContext& renderContext) = 0;

        virtual void Input(ConsoleInputExt& input) = 0;
    };
};