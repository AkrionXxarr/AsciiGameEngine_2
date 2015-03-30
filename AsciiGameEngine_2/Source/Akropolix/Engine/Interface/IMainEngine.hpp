/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

namespace aki
{
    namespace engine
    {
        namespace I
        {
            class ICoreEngine;

            ///////////////////////////////////////////////////////////
            // engine the user inherits from to define more specific behavior
            //

            class IMainEngine
            {
            public:
                IMainEngine() { }
                virtual ~IMainEngine() { }

                virtual bool Initialize() = 0;

                virtual void Start() = 0;
                virtual void Stop() = 0;
                virtual void Tick(float deltaTime) = 0;

            protected:
                virtual void Clean() = 0;

            private:
                // engine has no reason to be copied
                IMainEngine(const IMainEngine& other);
                void operator= (const IMainEngine& other);

            protected:
                ICoreEngine* coreEngine;
            };
        };
    };
};