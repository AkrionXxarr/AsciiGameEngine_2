#include "Akropolix\Object\Windows Console\TestObject.hpp"
#include "Akropolix\Render\Windows Console\ConsoleRenderContext.hpp"
#include "Akropolix\Input\Windows Console\ConsoleInputExt.hpp"

using namespace Akropolix::Render::WinConsole;
using namespace Akropolix::Render::Interface;
using namespace Akropolix::Input::WinConsole;

namespace Akropolix
{
    void TestObject::Update(float deltaTime)
    {
        if (right)
            pos.x += 20 * deltaTime;
        if (left)
            pos.x -= 20 * deltaTime;
        if (up)
            pos.y -= 20 * deltaTime;
        if (down)
            pos.y += 20 * deltaTime;
    }

    void TestObject::Draw(IRenderContext& renderContext)
    {
        ConsoleRenderContext& crc = (ConsoleRenderContext&)renderContext;

        CHAR_INFO ci;

        ci.Attributes = FOREGROUND_RED;
        ci.Char.UnicodeChar = '#';

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                int x = int(pos.x + (i - 1));
                int y = int(pos.y + (j - 1));

                POINT p = { x, y };

                crc.DrawPoint(p, ci);
            }
        }
    }

    void TestObject::Input(ConsoleInputExt& input)
    {
        right = input.GetKeyDown(KEYBOARD::ARROW_RIGHT);
        left = input.GetKeyDown(KEYBOARD::ARROW_LEFT);
        up = input.GetKeyDown(KEYBOARD::ARROW_UP);
        down = input.GetKeyDown(KEYBOARD::ARROW_DOWN);

        if (right)
        {
            int x = 0;
            x = 5;
        }
    }
};