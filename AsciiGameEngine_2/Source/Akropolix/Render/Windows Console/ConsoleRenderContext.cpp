/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include <math.h>

#include "Akropolix\render\Windows Console\ConsoleRenderContext.hpp"
#include "Akropolix\Display Device\Windows Console\Console.hpp"
#include "Akropolix\Utility\Math\Vector2f.hpp"

using namespace aki::math;

namespace aki
{
    namespace render
    {
        namespace wincon
        {
            ConsoleRenderContext::ConsoleRenderContext()
            {

            }

            ConsoleRenderContext::~ConsoleRenderContext()
            {

            }

            void ConsoleRenderContext::Initialize(std::shared_ptr<display::wincon::ConsoleBuffer> buffer)
            {
                if (this->buffer)
                    this->buffer.reset();

                this->buffer = buffer;
            }

            unsigned int ConsoleRenderContext::GetWidth()
            {
                return buffer->GetSizeAsCoord().X;
            }

            unsigned int ConsoleRenderContext::GetHeight()
            {
                return buffer->GetSizeAsCoord().Y;
            }

            void ConsoleRenderContext::DrawPoint(POINT pos, CHAR_INFO& ci)
            {
                if (pos.x < 0 || pos.y < 0 || pos.x >(buffer->GetSizeAsCoord().X - 1) || pos.y >(buffer->GetSizeAsCoord().Y - 1))
                    return;

                buffer->Put(pos.x, pos.y, ci);
            }

            void ConsoleRenderContext::DrawLine(POINT a, POINT b, CHAR_INFO& ci)
            {
                // Make sure the ends of the line get drawn
                DrawPoint(a, ci);
                DrawPoint(b, ci);

                bool vertProjIsLonger = (std::abs(b.y - a.y) > std::abs(b.x - a.x));


                ///////////////////////////////////////////
                //
                // First check if the slope of the line rests in the field marked #
                // If it does, flip the X and Y, placing the angle within the blank field
                //
                //          * * *
                //      * *###|###* *
                //    *#######|#######*
                //  *   \#####|#####/   *
                //  *     \###|###/     *
                // *        \#|#/        *
                // *---------------------*
                // *        /#|#\        *
                //  *     /###|###\     *
                //  *   /#####|#####\   *
                //    *#######|#######*
                //      * *###|###* *
                //          * * *
                if (vertProjIsLonger)
                {
                    LONG t = a.x;
                    a.x = a.y;
                    a.y = t;

                    t = b.x;
                    b.x = b.y;
                    b.y = t;
                }


                ///////////////////////////////////////////
                //
                // First check if the direction of the line rests within the field marked #
                // If it does, swap the points such (a->b becomes b->a), placing the
                // direction within the blank field directly opposite.
                //
                //          * * *
                //      * *   |   * *
                //    *       |       *
                //  *###\     |     /   *
                //  *#####\   |   /     *
                // *########\ | /        *
                // *---------------------*
                // *########/ | \        *
                //  *#####/   |   \     *
                //  *###/     |     \   *
                //    *       |       *
                //      * *   |   * *
                //          * * *
                if (a.x > b.x)
                {
                    POINT t = a;
                    a = b;
                    b = t;
                }

                float dx = float(b.x - a.x);
                float dy = std::fabs(float(b.y - a.y));

                float err = dx / 2.0f;
                int yStep = (a.y < b.y) ? 1 : -1;

                int y = a.y;

                for (int x = a.x; x < b.x; x++)
                {
                    if (vertProjIsLonger)
                        DrawPoint({ y, x }, ci);
                    else
                        DrawPoint({ x, y }, ci);

                    err -= dy;

                    if (err < 0)
                    {
                        y += yStep;
                        err += dx;
                    }
                }
            }
        };
    };
};