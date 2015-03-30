/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <Windows.h>
#include <deque>

#include "Akropolix\Input\Windows Input\ConsoleInputDefines.hpp"
#include "Akropolix\Utility\Logging\Log.hpp"

#define INPUT_LOG "InputLog.txt"

namespace Akropolix
{
    //////////////////////////////////////////////////////////////////////////////
    // This class is intended to allow for mouse and keyboard input that
    // doesn't require the console to be used with Win32 functionality.
    //
    // A buffer of booleans is used to keep track of key/button presses
    // which can be indexed by the appropriate enum code.
    //
    // Dequeues are used for Key/Button Up events.
    //
    class ConsoleInput
    {
    public:
        /* Construct & Destruct*/
        ConsoleInput(unsigned int inputBufferSize, HWND consoleWindow);
        virtual ~ConsoleInput();

        /* ConsoleInpu operations */
        virtual void Tick();

        /* Getters */
        // Keyboard
        bool GetKeyUp(KEYBOARD key);
        bool GetKeyDown(KEYBOARD key);

        // Mouse
        bool GetMouseDown(MOUSE_BUTTON button);
        bool GetMouseUp(MOUSE_BUTTON button);
        bool GetMouseAction(MOUSE_ACTION action);

        COORD GetMousePosition();
        void GetMouseDesktopPosition(POINT& pos);

    private:
        /* Utility */
        void KeyEvent(KEY_EVENT_RECORD keyEvent);
        void MouseEvent(MOUSE_EVENT_RECORD mouseEvent);
        void ClearInputEvents();

    protected:
        /* Variables */
        // Keyboard
        bool* pressedKeys;
        std::deque<KEYBOARD> releasedKeys;

        // Mouse
        bool* mouseActions;
        bool* pressedMouseButtons;
        std::deque<MOUSE_BUTTON> releasedMouseButtons;

        COORD mousePosition;

        /* Other */
        HANDLE inputHandle;
        HWND consoleWindow;
        bool hasFocus;
        bool regainedFocus;

    private:
        /* Variables */
        DWORD oldMode; // Input settings before being changed

        unsigned int inputBufferSize; // Maximum records to process
        INPUT_RECORD* inputRecords;
    };
};