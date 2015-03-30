/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <Windows.h>

#include "Akropolix\Utility\Time\ITime.hpp"

namespace Akropolix
{
    namespace Time
    {
        class WindowsTime : public Interface::ITime
        {
        public:
            WindowsTime()
            {
                curTime = lastTime = GetTickCount();
                deltaTime = 0;
            }

            virtual ~WindowsTime() { }

            virtual void Tick()
            {
                lastTime = curTime;
                curTime = GetTickCount();
                deltaTime = curTime - lastTime;
            }

            virtual float DeltaTime()
            {
                return deltaTime / 1000.0f;
            }

        private:
            DWORD lastTime, curTime, deltaTime;
        };
    };
};