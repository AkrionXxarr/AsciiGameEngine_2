/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

namespace aki
{
    namespace render
    {
        namespace I
        {
            class IRenderContext
            {
            public:
                IRenderContext() { }
                virtual ~IRenderContext() { }

                virtual unsigned int GetWidth() = 0;
                virtual unsigned int GetHeight() = 0;

            private:
                // render context has no reason to be copied
                IRenderContext(const IRenderContext& other);
                void operator= (const IRenderContext& other);
            };
        }
    }
}