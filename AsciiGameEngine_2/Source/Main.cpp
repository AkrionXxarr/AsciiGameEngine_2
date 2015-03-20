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
        
        if (input.GetKeyDown(KEYBOARD::ARROW_RIGHT))
        {
            ci.Char.UnicodeChar = 0x1A;
            ci2.Char.UnicodeChar = 0x1A;

            if ((charPos2.x + 1) < buffer->GetSizeAsCoord().X)
                charPos2.x++;
        }
        if (input.GetKeyDown(KEYBOARD::ARROW_LEFT))
        {
            ci.Char.UnicodeChar = 0x1B;
            ci2.Char.UnicodeChar = 0x1B;

            if ((charPos2.x - 1) >= 0)
                charPos2.x--;
        }
        if (input.GetKeyDown(KEYBOARD::ARROW_UP))
        {
            ci.Char.UnicodeChar = 0x1E;
            ci2.Char.UnicodeChar = 0x1E;

            if ((charPos2.y - 1) >= 0)
                charPos2.y--;
        }
        if (input.GetKeyDown(KEYBOARD::ARROW_DOWN))
        {
            ci.Char.UnicodeChar = 0x1F;
            ci2.Char.UnicodeChar = 0x1F;

            if ((charPos2.y + 1) < buffer->GetSizeAsCoord().Y)
                charPos2.y++;
        }

        if (input.GetKeyDown(KEYBOARD::SHIFT))
        {
            if (input.GetKeyUp(KEYBOARD::NUM_1))
            {
                ci.Char.UnicodeChar = '!';
            }
        }

        if (input.GetMouseAction(MOUSE_ACTION::MOUSE_WHEEL_LEFT))
            ci.Char.UnicodeChar = 'L';
        if (input.GetMouseAction(MOUSE_ACTION::MOUSE_WHEEL_RIGHT))
            ci.Char.UnicodeChar = 'R';
        if (input.GetMouseAction(MOUSE_ACTION::MOUSE_WHEEL_FORWARD))
            ci.Char.UnicodeChar = 'F';
        if (input.GetMouseAction(MOUSE_ACTION::MOUSE_WHEEL_BACKWARD))
            ci.Char.UnicodeChar = 'B';

        if (input.GetMouseDown(MOUSE_BUTTON::CLICK_LEFT))
        {
            if (input.GetMouseAction(MOUSE_ACTION::CLICK_DOUBLE))
                ci.Char.UnicodeChar = 'D';
            else
                ci.Char.UnicodeChar = '-';

        }
        else if (input.GetMouseUp(MOUSE_BUTTON::CLICK_RIGHT))
        {
            ci.Char.UnicodeChar = '#';
        }

        if (input.GetMouseAction(MOUSE_ACTION::MOVED))
            charPos = Math::Vector2f(input.GetMousePosition().X, input.GetMousePosition().Y);

        if (input.GetKeyDown(KEYBOARD::F1)) ci.Char.UnicodeChar = '1';
        else if (input.GetKeyDown(KEYBOARD::F2)) ci.Char.UnicodeChar = '2';
        else if (input.GetKeyDown(KEYBOARD::F3)) ci.Char.UnicodeChar = '3';
        else if (input.GetKeyDown(KEYBOARD::F4)) ci.Char.UnicodeChar = '4';
        else if (input.GetKeyDown(KEYBOARD::F5)) ci.Char.UnicodeChar = '5';
        else if (input.GetKeyDown(KEYBOARD::F6)) ci.Char.UnicodeChar = '6';
        else if (input.GetKeyDown(KEYBOARD::F7)) ci.Char.UnicodeChar = '7';
        else if (input.GetKeyDown(KEYBOARD::F8)) ci.Char.UnicodeChar = '8';
        else if (input.GetKeyDown(KEYBOARD::F9)) ci.Char.UnicodeChar = '9';
        else if (input.GetKeyDown(KEYBOARD::F10)) ci.Char.UnicodeChar = 'A';
        else if (input.GetKeyDown(KEYBOARD::F11)) ci.Char.UnicodeChar = 'B';
        else if (input.GetKeyDown(KEYBOARD::F12)) ci.Char.UnicodeChar = 'C';

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