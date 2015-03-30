/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

namespace Akropolix
{
    class IRenderContext;

    namespace Object
    {
        namespace Interface
        {
            class IObject
            {
            public:
                IObject() { }
                virtual ~IObject() { }

                virtual void Update(float deltaTime) = 0;
                virtual void Draw(IRenderContext& renderContext) = 0;

            public:
                unsigned int ID;
            };
        };
    };
};