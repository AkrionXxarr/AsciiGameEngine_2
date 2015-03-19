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

    pressedKeys = new bool[KEYBOARD::END_OF_ENUM];

    for (int i = 0; i < KEYBOARD::END_OF_ENUM; i++)
    {
        pressedKeys[i] = false;
    }

    mouseData.moved = false;
    mouseData.leftButtonPressed = false;
    mouseData.rightButtonPressed = false;
    mouseData.pos = { 0, 0 };

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
    if (pressedKeys)
        delete[] pressedKeys;
}

/////////////////////////////////
// ConsoleInput operations
//

void ConsoleInput::Tick()
{   
    POINT point;
    DWORD inputCount;

    releasedKeys.clear();

    mouseData.moved = false;
    mouseData.leftButtonPressed = false;
    mouseData.rightButtonPressed = false;
    mouseData.doubleClick = false;

    PeekConsoleInput(inputHandle, inputRecords, 32, &inputCount);

    for (unsigned int i = 0; i < inputCount; i++)
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

bool ConsoleInput::IsKeyUp(KEYBOARD key)
{
    bool keyMatched = false;

    for (int i = 0; i < releasedKeys.size(); i++)
    {
        if (releasedKeys[i] == key)
        {
            keyMatched = true;
            break;
        }
    }

    return keyMatched;
}

bool ConsoleInput::IsKeyDown(KEYBOARD key)
{
    return pressedKeys[key];
}

bool ConsoleInput::MouseMoved()
{
    return mouseData.moved;
}

bool ConsoleInput::LeftClick()
{
    return mouseData.leftButtonPressed;
}

bool ConsoleInput::RightClick()
{
    return mouseData.rightButtonPressed;
}

bool ConsoleInput::DoubleClick()
{
    return mouseData.doubleClick;
}

COORD ConsoleInput::GetMousePosition()
{
    return mouseData.pos;
}


//////////////////
// Utility
//
void ConsoleInput::KeyEvent(KEY_EVENT_RECORD keyEvent)
{
    if (keyEvent.wVirtualKeyCode == 0x32)
    {
        int x = 3;
        x = 0;
    }

    KEYBOARD key = KEYBOARD::NO_KEY;
    KEYBOARD controlKey = KEYBOARD::NO_KEY;

    if ((keyEvent.dwControlKeyState & SHIFT_PRESSED) != 0)
        controlKey = KEYBOARD::SHIFT;

    /*
    switch (keyEvent.dwControlKeyState)
    {
    case LEFT_ALT_PRESSED:
        controlKey = KEYBOARD::ALT_LEFT;
        break;
    case RIGHT_ALT_PRESSED:
        controlKey = KEYBOARD::ALT_RIGHT;
        break;
    case LEFT_CTRL_PRESSED:
        controlKey = KEYBOARD::CONTROL_LEFT;
        break;
    case RIGHT_CTRL_PRESSED:
        controlKey = KEYBOARD::CONTROL_RIGHT;
        break;
    case SHIFT_PRESSED:
        controlKey = KEYBOARD::SHIFT;
        break;
    default:
        controlKey = KEYBOARD::NO_KEY;
        break;
    }
    */

    switch (keyEvent.wVirtualKeyCode)
    {
        /* Letter keys */
    case 0x41: key = KEYBOARD::A; break;
    case 0x42: key = KEYBOARD::B; break;
    case 0x43: key = KEYBOARD::C; break;
    case 0x44: key = KEYBOARD::D; break;
    case 0x45: key = KEYBOARD::E; break;
    case 0x46: key = KEYBOARD::F; break;
    case 0x47: key = KEYBOARD::G; break;
    case 0x48: key = KEYBOARD::H; break;
    case 0x49: key = KEYBOARD::I; break;
    case 0x4A: key = KEYBOARD::J; break;
    case 0x4B: key = KEYBOARD::K; break;
    case 0x4C: key = KEYBOARD::L; break;
    case 0x4D: key = KEYBOARD::M; break;
    case 0x4E: key = KEYBOARD::N; break;
    case 0x4F: key = KEYBOARD::O; break;
    case 0x50: key = KEYBOARD::P; break;
    case 0x51: key = KEYBOARD::Q; break;
    case 0x52: key = KEYBOARD::R; break;
    case 0x53: key = KEYBOARD::S; break;
    case 0x54: key = KEYBOARD::T; break;
    case 0x55: key = KEYBOARD::U; break;
    case 0x56: key = KEYBOARD::V; break;
    case 0x57: key = KEYBOARD::W; break;
    case 0x58: key = KEYBOARD::X; break;
    case 0x59: key = KEYBOARD::Y; break;
    case 0x5A: key = KEYBOARD::Z; break;

        /* Number Keys */
    case 0x30: key = KEYBOARD::NUM_0; break;
    case 0x31: key = KEYBOARD::NUM_1; break;
    case 0x32: key = KEYBOARD::NUM_2; break;
    case 0x33: key = KEYBOARD::NUM_3; break;
    case 0x34: key = KEYBOARD::NUM_4; break;
    case 0x35: key = KEYBOARD::NUM_5; break;
    case 0x36: key = KEYBOARD::NUM_6; break;
    case 0x37: key = KEYBOARD::NUM_7; break;
    case 0x38: key = KEYBOARD::NUM_8; break;
    case 0x39: key = KEYBOARD::NUM_9; break;

        /* Arrow Keys */
    case VK_LEFT: key = KEYBOARD::ARROW_LEFT; break;
    case VK_RIGHT: key = KEYBOARD::ARROW_RIGHT; break;
    case VK_UP: key = KEYBOARD::ARROW_UP; break;
    case VK_DOWN: key = KEYBOARD::ARROW_DOWN; break;

        /* Numpad Keys */
    case VK_NUMPAD0: key = KEYBOARD::NUMPAD_0; break;
    case VK_NUMPAD1: key = KEYBOARD::NUMPAD_1; break;
    case VK_NUMPAD2: key = KEYBOARD::NUMPAD_2; break;
    case VK_NUMPAD3: key = KEYBOARD::NUMPAD_3; break;
    case VK_NUMPAD4: key = KEYBOARD::NUMPAD_4; break;
    case VK_NUMPAD5: key = KEYBOARD::NUMPAD_5; break;
    case VK_NUMPAD6: key = KEYBOARD::NUMPAD_6; break;
    case VK_NUMPAD7: key = KEYBOARD::NUMPAD_7; break;
    case VK_NUMPAD8: key = KEYBOARD::NUMPAD_8; break;
    case VK_NUMPAD9: key = KEYBOARD::NUMPAD_9; break;

    case VK_ADD: key = KEYBOARD::NUMPAD_ADD; break;
    case VK_SUBTRACT: key = KEYBOARD::NUMPAD_SUBTRACT; break;
    case VK_MULTIPLY: key = KEYBOARD::NUMPAD_MULTIPLY; break;
    case VK_DIVIDE: key = KEYBOARD::NUMPAD_DIVIDE; break;
    case VK_DECIMAL: key = KEYBOARD::NUMPAD_DECIMAL; break;

        /* Other Keys */
    case VK_BACK: key = KEYBOARD::BACKSPACE; break;
    case VK_TAB: key = KEYBOARD::TAB; break;
    case VK_INSERT: key = KEYBOARD::INSERT; break;
    case VK_DELETE: key = KEYBOARD::DEL; break;
    case VK_HOME: key = KEYBOARD::HOME; break;
    case VK_END: key = KEYBOARD::END; break;
    case VK_PRIOR: key = KEYBOARD::PAGE_UP; break;
    case VK_NEXT: key = KEYBOARD::PAGE_DOWN; break;
    case VK_APPS: key = KEYBOARD::MENU; break;
    case VK_SNAPSHOT: key = KEYBOARD::PRINT_SCREEN; break;
    case VK_PAUSE: key = KEYBOARD::PAUSE; break;
    case VK_ESCAPE: key = KEYBOARD::ESCAPE; break;

    case VK_OEM_3: key = KEYBOARD::GRAVE; break;
    case VK_SPACE: key = KEYBOARD::SPACE; break;
    case VK_OEM_2: key = KEYBOARD::SLASH_FORWARD; break;
    case VK_OEM_5: key = KEYBOARD::SLASH_BACKWARD; break;
    case VK_OEM_COMMA: key = KEYBOARD::COMMA; break;
    case VK_OEM_PERIOD: key = KEYBOARD::PERIOD; break;
    case VK_OEM_1: key = KEYBOARD::SEMICOLON; break;
    case VK_OEM_7: key = KEYBOARD::APOSTROPHE; break;
    case VK_OEM_MINUS: key = KEYBOARD::HYPHEN; break;
    case VK_OEM_PLUS: key = KEYBOARD::EQUALS; break;
    case VK_OEM_4: key = KEYBOARD::SQUARE_BRACKET_LEFT; break;
    case VK_OEM_6: key = KEYBOARD::SQUARE_BRACKET_RIGHT; break;

        /* Lock keys */
    case VK_CAPITAL: key = KEYBOARD::CAPS_LOCK; break;
    case VK_NUMLOCK: key = KEYBOARD::NUM_LOCK; break;
    case VK_SCROLL: key = KEYBOARD::SCROLL_LOCK; break;

        /* F Keys */
    case VK_F1: key = KEYBOARD::F1; break;
    case VK_F2: key = KEYBOARD::F2; break;
    case VK_F3: key = KEYBOARD::F3; break;
    case VK_F4: key = KEYBOARD::F4; break;
    case VK_F5: key = KEYBOARD::F5; break;
    case VK_F6: key = KEYBOARD::F6; break;
    case VK_F7: key = KEYBOARD::F7; break;
    case VK_F8: key = KEYBOARD::F8; break;
    case VK_F9: key = KEYBOARD::F9; break;
    case VK_F10: key = KEYBOARD::F10; break;
    case VK_F11: key = KEYBOARD::F11; break;
    case VK_F12: key = KEYBOARD::F12; break;

        /* Control Keys */
    case VK_MENU: key = KEYBOARD::ALT; break;
    case VK_CONTROL: key = KEYBOARD::CONTROL; break;
    case VK_SHIFT: key = KEYBOARD::SHIFT; break;
    case VK_LWIN: key = KEYBOARD::SYSTEM_LEFT; break;
    case VK_RWIN: key = KEYBOARD::SYSTEM_RIGHT; break;

        /* Default */
    default: key = KEYBOARD::UNHANDLED_KEY; break;
    }

    pressedKeys[key] = (keyEvent.bKeyDown != 0);

    if (!keyEvent.bKeyDown)
        releasedKeys.push_front(key);
}

void ConsoleInput::MouseEvent(MOUSE_EVENT_RECORD mouseEvent)
{
    switch (mouseEvent.dwEventFlags)
    {
    case 0:
        switch (mouseEvent.dwButtonState)
        {
        case FROM_LEFT_1ST_BUTTON_PRESSED:
            mouseData.leftButtonPressed = true;
            break;
        case RIGHTMOST_BUTTON_PRESSED:
            mouseData.rightButtonPressed = true;
            break;
        }
        break;
    case DOUBLE_CLICK:
        mouseData.doubleClick = true;
        break;
    case MOUSE_HWHEELED:
        break;
    case MOUSE_WHEELED:
        break;
    case MOUSE_MOVED:
        mouseData.pos = mouseEvent.dwMousePosition;
        mouseData.moved = true;
        break;
    }
}

void ConsoleInput::UpdateMouseDesktopPos()
{
}