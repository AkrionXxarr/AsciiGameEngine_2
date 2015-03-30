/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "Akropolix\Render\Windows Console\ConsoleRenderContext.hpp"
#include "Akropolix\Display Device\Windows Console\Console.hpp"

namespace Akropolix
{
    namespace Render
    {
        namespace WinConsole
        {
            ConsoleRenderContext::ConsoleRenderContext()
            {

            }

            ConsoleRenderContext::~ConsoleRenderContext()
            {

            }

            void ConsoleRenderContext::Initialize(std::shared_ptr<DisplayDevice::WinConsole::ConsoleBuffer> buffer)
            {
                if (this->buffer)
                    this->buffer.reset();

                this->buffer = buffer;
            }

            void ConsoleRenderContext::DrawPoint(POINT& pos, CHAR_INFO& ci)
            {
                if (pos.x < 0 || pos.y < 0 || pos.x >(buffer->GetSizeAsCoord().X - 1) || pos.y >(buffer->GetSizeAsCoord().Y - 1))
                    return;

                buffer->Put(pos.x, pos.y, ci);
            }
        };
    };
};