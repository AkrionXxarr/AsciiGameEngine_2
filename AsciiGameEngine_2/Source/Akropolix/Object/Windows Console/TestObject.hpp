#pragma once

#include "Akropolix\Object\Windows Console\ConsoleObject.hpp"
#include "Akropolix\Utility\math\Vector2f.hpp"

namespace aki
{
    namespace input
    {
        namespace wincon
        {
            class ConsoleInputExt;
        };
    };

    class TestObject : public object::wincon::ConsoleObject
    {
    public:
        TestObject(float x, float y) { pos = math::Vector2f(x, y); }
        ~TestObject() { }

        virtual void Update(float deltaTime);
        virtual void Draw(render::I::IRenderContext& renderContext);

        virtual void input(input::wincon::ConsoleInputExt& input);

    private:
        math::Vector2f pos;

        bool up, left, right, down;

    };
};