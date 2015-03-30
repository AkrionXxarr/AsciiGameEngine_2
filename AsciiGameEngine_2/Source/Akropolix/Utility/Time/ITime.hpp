/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

namespace Akropolix
{
    namespace Time
    {
        namespace Interface
        {
            class ITime
            {
            public:
                ITime() { }
                virtual ~ITime() { }

                virtual void Tick() = 0;

                virtual float DeltaTime() = 0;
            };
        };
    };
};