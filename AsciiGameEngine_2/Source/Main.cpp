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

/*
HANDLE hStdin;
DWORD fdwSaveOldMode;

VOID ErrorExit(LPSTR);
VOID KeyEventProc(KEY_EVENT_RECORD);
VOID MouseEventProc(MOUSE_EVENT_RECORD);
VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);

int main(VOID)
{
    DWORD cNumRead, fdwMode, i;
    INPUT_RECORD irInBuf[128];
    int counter = 0;

    // Get the standard input handle.

    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE)
        ErrorExit("GetStdHandle");

    // Save the current input mode, to be restored on exit.

    if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
        ErrorExit("GetConsoleMode");

    // Enable the window and mouse input events.

    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    if (!SetConsoleMode(hStdin, fdwMode))
        ErrorExit("SetConsoleMode");

    // Loop to read and handle the next 100 input events.

    while (counter++ <= 1000)
    {
        // Wait for the events.

        if (!ReadConsoleInput(
            hStdin,      // input buffer handle
            irInBuf,     // buffer to read into
            128,         // size of read buffer
            &cNumRead)) // number of records read
            ErrorExit("ReadConsoleInput");

        // Dispatch the events to the appropriate handler.

        for (i = 0; i < cNumRead; i++)
        {
            switch (irInBuf[i].EventType)
            {
            case KEY_EVENT: // keyboard input
                KeyEventProc(irInBuf[i].Event.KeyEvent);
                break;

            case MOUSE_EVENT: // mouse input
                MouseEventProc(irInBuf[i].Event.MouseEvent);
                break;

            case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing
                ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
                break;

            case FOCUS_EVENT:  // disregard focus events

            case MENU_EVENT:   // disregard menu events
                break;

            default:
                ErrorExit("Unknown event type");
                break;
            }
        }
    }

    // Restore input mode on exit.

    SetConsoleMode(hStdin, fdwSaveOldMode);

    return 0;
}

VOID ErrorExit(LPSTR lpszMessage)
{
    fprintf(stderr, "%s\n", lpszMessage);

    // Restore input mode on exit.

    SetConsoleMode(hStdin, fdwSaveOldMode);

    ExitProcess(0);
}

VOID KeyEventProc(KEY_EVENT_RECORD ker)
{
    printf("Key event: ");

    if (ker.bKeyDown)
        printf("key pressed\n");
    else printf("key released\n");
}

VOID MouseEventProc(MOUSE_EVENT_RECORD mer)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
    printf("Mouse event: ");

    switch (mer.dwEventFlags)
    {
    case 0:

        if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            printf("left button press \n");
        }
        else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
        {
            printf("right button press \n");
        }
        else
        {
            printf("button press\n");
        }
        break;
    case DOUBLE_CLICK:
        printf("double click\n");
        break;
    case MOUSE_HWHEELED:
        printf("horizontal mouse wheel\n");
        break;
    case MOUSE_MOVED:
        printf("mouse moved: ");
        std::cout << mer.dwMousePosition.X << ", " << mer.dwMousePosition.Y << "\n";
        POINT p;
        GetCursorPos(&p);
        std::cout << p.x << ", " << p.y << "\n";
        break;
    case MOUSE_WHEELED:
        printf("vertical mouse wheel\n");
        break;
    default:
        printf("unknown\n");
        break;
    }
}

VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
    printf("Resize event\n");
    printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
}
*/