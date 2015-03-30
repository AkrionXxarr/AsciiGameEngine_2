#pragma once

#include "Akropolix\Object\Windows Console\ConsoleObject.hpp"
#include "Akropolix\Utility\Math\Vector2f.hpp"

namespace Akropolix
{
    class ConsoleInputExt;

    class TestObject : public ConsoleObject
    {
    public:
        TestObject(float x, float y) { pos = Math::Vector2f(x, y); }
        ~TestObject() { }

        virtual void Update(float deltaTime);
        virtual void Draw(IRenderContext& renderContext);

        virtual void Input(ConsoleInputExt& input);

    private:
        Math::Vector2f pos;

        bool up, left, right, down;

    };
};