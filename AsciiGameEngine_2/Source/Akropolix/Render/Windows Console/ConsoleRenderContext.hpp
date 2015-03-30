/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <Windows.h>
#include <memory>

#include "Akropolix\Render\Interface\IRenderContext.hpp"

namespace Akropolix
{
    namespace DisplayDevice
    {
        namespace WinConsole
        {
            class ConsoleBuffer;
        };
    };

    namespace Render
    {
        namespace WinConsole
        {
            class ConsoleRenderContext : public Render::Interface::IRenderContext
            {
            public:
                ConsoleRenderContext();
                ~ConsoleRenderContext();

                void Initialize(std::shared_ptr<DisplayDevice::WinConsole::ConsoleBuffer> buffer);

                void Clear();

                void DrawPoint(POINT& pos, CHAR_INFO& ci);

            private:
                std::shared_ptr<DisplayDevice::WinConsole::ConsoleBuffer> buffer;
            };
        };
    };
};