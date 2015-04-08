/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <Windows.h>
#include <deque>

#include "Akropolix\input\Windows Console\ConsoleInputDefines.hpp"
#include "Akropolix\Utility\Logging\log.hpp"

#define INPUT_LOG "InputLog.txt"

namespace aki
{
    namespace input
    {
        namespace wincon
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
                bool GetKeyUp(KEYBOARD::TYPE key);
                bool GetKeyDown(KEYBOARD::TYPE key);

                bool GetAnyKeyUp();
                bool GetAnyKeyDown();

                KEYBOARD::TYPE GetMostRecentKeyDown();
                KEYBOARD::TYPE GetMostRecentKeyUp();

                // Mouse
                bool GetMouseDown(MOUSE_BUTTON::TYPE button);
                bool GetMouseUp(MOUSE_BUTTON::TYPE button);
                bool GetMouseAction(MOUSE_ACTION::TYPE action);

                bool GetAnyMouseUp();
                bool GetAnyMouseDown();

                MOUSE_BUTTON::TYPE GetMostRecentMouseDown();
                MOUSE_BUTTON::TYPE GetMostRecentMouseUp();

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
                std::deque<KEYBOARD::TYPE> releasedKeys;
                KEYBOARD::TYPE mostRecentKeyDown;
                KEYBOARD::TYPE mostRecentKeyUp;

                // Mouse
                bool* mouseActions;
                bool* pressedMouseButtons;
                std::deque<MOUSE_BUTTON::TYPE> releasedMouseButtons;
                MOUSE_BUTTON::TYPE mostRecentMouseDown;
                MOUSE_BUTTON::TYPE mostRecentMouseUp;

                COORD mousePosition;

                /* Other */
                HANDLE inputHandle;
                HWND consoleWindow;
                bool hasFocus;
                bool regainedFocus;

            private:
                /* Variables */
                DWORD oldMode; // input settings before being changed

                unsigned int inputBufferSize; // Maximum records to process
                INPUT_RECORD* inputRecords;
            };
        };
    };
};