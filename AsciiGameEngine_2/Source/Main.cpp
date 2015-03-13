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
    ConsoleInput input({ 50, 50 });
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