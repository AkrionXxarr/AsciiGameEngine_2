/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

namespace Akropolix
{
    class IDisplayDevice;
    class IObjectManager;
    class IRenderContext;
    class ITime;

    namespace Engine
    {
        namespace Interface
        {
            class IMainEngine;

            ///////////////////////////////////////////////////////////
            // Handles the very basic fundamentals, such as managing the time
            // and ordering of critical tasks. (e.g. Update should always preceed Draw/Render)
            //

            class ICoreEngine
            {
            public:
                ICoreEngine() : running(false) { }
                virtual ~ICoreEngine() { }

                virtual void Start(
                    ITime* time,
                    IDisplayDevice* displayDevice,
                    IRenderContext* renderContext,
                    IObjectManager* objectManager,
                    IMainEngine* mainEngine) = 0;
                virtual void Run() = 0;
                virtual void Stop() = 0;

                bool HasFocus() { return hasFocus; }
                bool IsRunning() { return running; }

            protected:
                virtual void Clean() = 0;

            private:
                // Engine has no reason to be copied
                ICoreEngine(const ICoreEngine& other);
                void operator= (const ICoreEngine& other);

            protected:
                bool running;
                bool hasFocus;

                IMainEngine* mainEngine;
                IDisplayDevice* displayDevice;
                IObjectManager* objectManager;
                IRenderContext* renderContext;
                ITime* time;
            };
        };
    };
};