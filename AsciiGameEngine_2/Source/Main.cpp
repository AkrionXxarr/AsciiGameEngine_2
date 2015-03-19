/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include <windows.h>
#include <stdio.h>
#include <iostream>

#include "Input\Windows Input\ConsoleInput.hpp"
#include "Utility\Math\Vector2f.hpp"
#include "Display Device\Windows Console\Console.hpp"
#include "Display Device\Windows Console\ConsoleDefines.hpp"

#define WIDTH 80
#define HEIGHT 30
#define SENSITIVITY 7.9

int main()
{
    std::shared_ptr<ConsoleBuffer> buffer = std::make_shared<ConsoleBuffer>(WIDTH, HEIGHT);
    ConsoleInput input(10); // Keep past 10 events
    Console console;

    console.CreateDevice(buffer, 0, FONT_10x18);
    console.ClearBuffer();

    CHAR_INFO ci;
    CHAR_INFO ci2;

    ci.Attributes = f_fullGreen;
    ci.Char.UnicodeChar = '.';

    ci2.Attributes = f_fullRed;
    ci2.Char.UnicodeChar = '.';

    Math::Vector2f charPos;
    Math::Vector2f charPos2;

    for (;;)
    {
        Sleep(10);
        console.ClearBuffer();
        input.Tick();
        
        if (input.IsKeyDown(KEYBOARD::ARROW_RIGHT))
        {
            ci.Char.UnicodeChar = 0x1A;
            ci2.Char.UnicodeChar = 0x1A;

            if ((charPos2.x + 1) < buffer->GetSizeAsCoord().X)
                charPos2.x++;
        }
        if (input.IsKeyDown(KEYBOARD::ARROW_LEFT))
        {
            ci.Char.UnicodeChar = 0x1B;
            ci2.Char.UnicodeChar = 0x1B;

            if ((charPos2.x - 1) >= 0)
                charPos2.x--;
        }
        if (input.IsKeyDown(KEYBOARD::ARROW_UP))
        {
            ci.Char.UnicodeChar = 0x1E;
            ci2.Char.UnicodeChar = 0x1E;

            if ((charPos2.y - 1) >= 0)
                charPos2.y--;
        }
        if (input.IsKeyDown(KEYBOARD::ARROW_DOWN))
        {
            ci.Char.UnicodeChar = 0x1F;
            ci2.Char.UnicodeChar = 0x1F;

            if ((charPos2.y + 1) < buffer->GetSizeAsCoord().Y)
                charPos2.y++;
        }

        if (input.IsKeyUp(KEYBOARD::NUM_1))
        {
            ci.Char.UnicodeChar = '1';
        }


        if (input.MouseMoved())
            charPos = Math::Vector2f(input.GetMousePosition().X, input.GetMousePosition().Y);

        if (input.LeftClick())
            ci.Char.UnicodeChar = '-';
        else if (input.RightClick())
            ci.Char.UnicodeChar = '#';
        else if (input.DoubleClick())
            ci.Char.UnicodeChar = 'D';

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