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
            class IRenderContext;
        }
    }

    namespace object
    {
        namespace I
        {
            class IObject
            {
            public:
                IObject() { }
                virtual ~IObject() { }

                virtual void Update(float deltaTime) = 0;
                virtual void Draw(render::I::IRenderContext& renderContext) = 0;

            public:
                unsigned int ID;
            };
        }
    }
}