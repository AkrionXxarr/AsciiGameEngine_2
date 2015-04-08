/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <Windows.h>
#include <memory>

#include "Akropolix\Render\Interface\IRenderContext.hpp"

namespace aki
{
    namespace display
    {
        namespace wincon
        {
            class ConsoleBuffer;
        };
    };

    namespace render
    {
        namespace wincon
        {
            class ConsoleRenderContext : public render::I::IRenderContext
            {
            public:
                ConsoleRenderContext();
                ~ConsoleRenderContext();

                void Initialize(std::shared_ptr<display::wincon::ConsoleBuffer> buffer);

                virtual unsigned int GetWidth();
                virtual unsigned int GetHeight();

                void Clear();

                // Draw to console buffer or supplied buffer
                void DrawPoint(POINT pos, CHAR_INFO& ci, CHAR_INFO* other = nullptr, COORD bufferSize = { 0, 0 });
                void DrawLine(POINT a, POINT b, CHAR_INFO& ci, CHAR_INFO* other = nullptr, COORD bufferSize = { 0, 0 });

            private:
                std::shared_ptr<display::wincon::ConsoleBuffer> buffer;
            };
        };
    };
};