/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

namespace Akropolix
{
    namespace Render
    {
        namespace Interface
        {
            class IRenderContext
            {
            public:
                IRenderContext() { }
                virtual ~IRenderContext() { }

            private:
                // Render context has no reason to be copied
                IRenderContext(const IRenderContext& other);
                void operator= (const IRenderContext& other);
            };
        };
    };
};