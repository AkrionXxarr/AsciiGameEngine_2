/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include <assert.h>

#include "Input\Windows Input\ConsoleInput.hpp"
#include "Utility\Math\Vector2f.hpp"
using namespace Math;

/////////////////////////////
// Construct & Destruct
//

ConsoleInput::ConsoleInput(unsigned int bufferLimit)
{
    this->bufferLimit = bufferLimit;
    inputRecords = new INPUT_RECORD[32];

    // Add 1 to buffer limit because a new element will be added
    // before the size is checked against the limit
    mouseScreenPos.resize(bufferLimit + 1);
    keyboardEvents.resize(bufferLimit + 1);
    mouseEvents.resize(bufferLimit + 1);

    inputHandle = GetStdHandle(STD_INPUT_HANDLE);
    consoleWindow = GetConsoleWindow();

    assert(inputHandle != INVALID_HANDLE_VALUE);
    assert(consoleWindow != INVALID_HANDLE_VALUE);

    GetConsoleMode(inputHandle, &oldMode);
    SetConsoleMode(inputHandle, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
}

ConsoleInput::~ConsoleInput()
{
    SetConsoleMode(inputHandle, oldMode);

    if (inputRecords)
        delete[] inputRecords;
}

/////////////////////////////////
// ConsoleInput operations
//

void ConsoleInput::Tick()
{   
    POINT point;
    DWORD inputCount;

    PeekConsoleInput(inputHandle, inputRecords, 32, &inputCount);

    for (int i = 0; i < inputCount; i++)
    {
        INPUT_RECORD input = inputRecords[i];

        switch (input.EventType)
        {
        case KEY_EVENT:
            KeyEvent(input.Event.KeyEvent);
            break;

        case MOUSE_EVENT:
            MouseEvent(input.Event.MouseEvent);
            break;
        }
    }

    FlushConsoleInputBuffer(inputHandle);

    GetCursorPos(&point);
}

/////////////////
// Peek & Get
//
KEY_EVENT_RECORD ConsoleInput::PeekKeyEvent()
{
    return keyboardEvents.front();
}

KEY_EVENT_RECORD ConsoleInput::GetKeyEvent()
{
    KEY_EVENT_RECORD keyEvent = keyboardEvents.front();
    keyboardEvents.pop_front();
    return keyEvent;
}

unsigned int ConsoleInput::GetKeyEventCount()
{
    return keyboardEvents.size();
}


MOUSE_EVENT_RECORD ConsoleInput::PeekMouseEvent()
{
    return mouseEvents.front();
}

MOUSE_EVENT_RECORD ConsoleInput::GetMouseEvent()
{
    MOUSE_EVENT_RECORD mouseEvent = mouseEvents.front();
    mouseEvents.pop_front();
    return mouseEvent;
}
unsigned int ConsoleInput::GetMouseEventCount()
{
    return mouseEvents.size();
}


POINT ConsoleInput::PeekMouseScreenPos()
{
    return mouseScreenPos.front();
}

POINT ConsoleInput::GetMouseScreenPos()
{
    POINT mousePos = mouseScreenPos.front();
    mouseScreenPos.pop_front();
    return mousePos;
}

unsigned int ConsoleInput::GetMouseScreenPosCount()
{
    return mouseScreenPos.size();
}


//////////////////
// Utility
//
void ConsoleInput::KeyEvent(KEY_EVENT_RECORD keyEvent)
{
    keyboardEvents.push_front(keyEvent);

    if (keyboardEvents.size() > bufferLimit)
        keyboardEvents.pop_back();
}

void ConsoleInput::MouseEvent(MOUSE_EVENT_RECORD mouseEvent)
{
    mouseEvents.push_front(mouseEvent);

    if (mouseEvents.size() > bufferLimit)
        mouseEvents.pop_back();
}

void ConsoleInput::UpdateMouseDesktopPos()
{
    POINT point;
    GetCursorPos(&point);
    
    mouseScreenPos.push_front(point);

    if (mouseScreenPos.size() > bufferLimit)
        mouseScreenPos.pop_back();
}