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

#define WIDTH 160
#define HEIGHT 90
#define SENSITIVITY 150

int main()
{
    std::shared_ptr<ConsoleBuffer> buffer = std::make_shared<ConsoleBuffer>(WIDTH, HEIGHT);
    Console console;
    ConsoleInput input({ 250, 250 });
    Vector2f v;
    Vector2f charPos;
    CHAR_INFO ci;

    ci.Attributes = FOREGROUND_INTENSITY | FOREGROUND_GREEN;
    ci.Char.UnicodeChar = '@';

    console.CreateDevice(buffer, 0, FONT_8x8);
    console.ClearBuffer();

    buffer->useDrawRect = true;

    for (;;)
    {
        input.Tick();
        v = input.GetMouseDelta();
        charPos = charPos + (v * SENSITIVITY);

        if (charPos.x < 0) charPos.x = 0;
        else if (charPos.x >= WIDTH) charPos.x = WIDTH - 1;
        if (charPos.y < 0) charPos.y = 0;
        else if (charPos.y >= HEIGHT) charPos.y = HEIGHT - 1;

        buffer->Put(unsigned int(charPos.x), unsigned int(charPos.y), ci);
        buffer->drawRect = { charPos.x, charPos.y, charPos.x, charPos.y };

        console.Display();
        console.ClearBuffer();
    }
}