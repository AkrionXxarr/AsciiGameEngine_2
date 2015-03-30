/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "Akropolix\Engine\Windows Console\MainConsoleEngine.hpp"

#define WIDTH 80
#define HEIGHT 80

using namespace Akropolix;

int main()
{
    Engine::WinConsole::MainConsoleEngine mainEngine(WIDTH, HEIGHT);

    if (!mainEngine.Initialize())
        return 0;

    mainEngine.Start();

    return 0;
}

/*
int main()
{
    std::shared_ptr<ConsoleBuffer> buffer = std::make_shared<ConsoleBuffer>(WIDTH, HEIGHT);
    
    Console console;
    WindowsTime time;

    console.CreateDevice(buffer, 1, FONT_10x18);
    console.ClearBuffer();

    ConsoleInputExt input(10, console.GetHandle()); // Keep past 10 events

    CHAR_INFO ci;
    CHAR_INFO ci2;

    CHAR_INFO lineChar;

    POINT p = { 0, 0 };
    Math::Vector2f a;
    Math::Vector2f b;

    ci.Attributes = f_fullGreen;
    ci.Char.UnicodeChar = '.';

    ci2.Attributes = f_fullRed;
    ci2.Char.UnicodeChar = '.';

    lineChar.Attributes = f_white;
    lineChar.Char.UnicodeChar = '@';

    Math::Vector2f charPos = Math::Vector2f(20, 20);
    Math::Vector2f charPos2;

    bool lockCursor = false;

    time.Tick();

    for (;;)
    {
        Sleep(10);
        time.Tick();
        console.ClearBuffer();
        input.Tick();

        float deltaTime = time.DeltaTime();
        
        ci.Char.UnicodeChar = '.';
        ci2.Char.UnicodeChar = '.';

        if (input.GetKeyDown(KEYBOARD::ARROW_RIGHT))
        {
            ci.Char.UnicodeChar = 0x1A;
            ci2.Char.UnicodeChar = 0x1A;

            if ((charPos2.x + 1) < buffer->GetSizeAsCoord().X)
                charPos2.x += (20 * deltaTime);
        }
        if (input.GetKeyDown(KEYBOARD::ARROW_LEFT))
        {
            ci.Char.UnicodeChar = 0x1B;
            ci2.Char.UnicodeChar = 0x1B;

            if ((charPos2.x - 1) >= 0)
                charPos2.x -= (20 * deltaTime);
        }
        if (input.GetKeyDown(KEYBOARD::ARROW_UP))
        {
            ci.Char.UnicodeChar = 0x1E;
            ci2.Char.UnicodeChar = 0x1E;

            if ((charPos2.y - 1) >= 0)
                charPos2.y -= (20 * deltaTime);
        }
        if (input.GetKeyDown(KEYBOARD::ARROW_DOWN))
        {
            ci.Char.UnicodeChar = 0x1F;
            ci2.Char.UnicodeChar = 0x1F;

            if ((charPos2.y + 1) < buffer->GetSizeAsCoord().Y)
                charPos2.y += (20 * deltaTime);
        }

        if (input.GetAnyKeyDown())
        {
            ci2.Char.UnicodeChar = input.GetCharacter();
            if (ci2.Char.UnicodeChar == 0)
                ci2.Char.UnicodeChar = '.';
        }

        if (input.GetMouseUp(MOUSE_BUTTON::CLICK_LEFT))
        {
            input.LockCursor(true);
            lockCursor = true;
        }
        else if (input.GetMouseUp(MOUSE_BUTTON::CLICK_RIGHT))
        {
            input.LockCursor(false);
            lockCursor = false;
        }

        //if (input.GetMouseAction(MOUSE_ACTION::MOVED))
        //charPos = Math::Vector2f(input.GetMousePosition().X, input.GetMousePosition().Y);

        if (lockCursor)
        {
            if (input.GetMouseAction(MOUSE_ACTION::MOVED))
            {
                p = input.GetDelta();
                a = Math::Vector2f(buffer->GetSizeAsCoord().X / 2.0f, buffer->GetSizeAsCoord().Y / 2.0f);
                b = Math::Vector2f(a.x + p.x, a.y + p.y);

                charPos.x += p.x / 10.0f;
                charPos.y += p.y / 10.0f;

                if (charPos.x < 0) charPos.x = 0;
                else if (charPos.x > buffer->GetSizeAsCoord().X - 1) charPos.x = buffer->GetSizeAsCoord().X - 1;
                if (charPos.y < 0) charPos.y = 0;
                else if (charPos.y > buffer->GetSizeAsCoord().Y - 1) charPos.y = buffer->GetSizeAsCoord().Y - 1;

                int length = (b - a).Length();

                for (int i = 0; i <= length; i++)
                {
                    Math::Vector2f t = a.Lerp(b, float(i) / float(length));
                    int x = int(t.x);
                    int y = int(t.y);

                    if (x > 0 && y > 0 && x < buffer->GetSizeAsCoord().X - 1 && y < buffer->GetSizeAsCoord().Y - 1)
                    {
                        buffer->Put(x, y, lineChar);
                    }
                }
            }
        }

        
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                int x = int(charPos.x + (i - 1));
                int y = int(charPos.y + (j - 1));

                if (x < 0) x = 0;
                else if (x > (buffer->GetSizeAsCoord().X - 1)) x = buffer->GetSizeAsCoord().X - 1;
                if (y < 0) y = 0;
                else if (y >(buffer->GetSizeAsCoord().Y - 1)) y = buffer->GetSizeAsCoord().Y - 1;

                buffer->Put(x, y, ci);
            }
        }

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                int x = int(charPos2.x + (i - 1));
                int y = int(charPos2.y + (j - 1));

                if (x < 0) x = 0;
                else if (x >(buffer->GetSizeAsCoord().X - 1)) x = buffer->GetSizeAsCoord().X - 1;
                if (y < 0) y = 0;
                else if (y >(buffer->GetSizeAsCoord().Y - 1)) y = buffer->GetSizeAsCoord().Y - 1;

                buffer->Put(x, y, ci2);
            }
        }

        console.Display();
    }
}
*/