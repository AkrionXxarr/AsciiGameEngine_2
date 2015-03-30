/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

namespace aki
{
    namespace display
    {
        namespace I
        {
            class IDisplayDevice;
        }
    }

    namespace object
    {
        namespace I
        {
            class IObjectManager;
        }
    }

    namespace render
    {
        namespace I
        {
            class IRenderContext;
        }
    }

    namespace time
    {
        namespace I
        {
            class ITime;
        }
    }

    namespace engine
    {
        namespace I
        {
            class IMainEngine;

            ///////////////////////////////////////////////////////////
            // Handles the very basic fundamentals, such as managing the time
            // and ordering of critical tasks. (e.g. Update should always preceed Draw/render)
            //

            class ICoreEngine
            {
            public:
                ICoreEngine() : running(false) { }
                virtual ~ICoreEngine() { }

                virtual void Start(
                    time::I::ITime* time,
                    display::I::IDisplayDevice* displayDevice,
                    render::I::IRenderContext* renderContext,
                    object::I::IObjectManager* objectManager,
                    IMainEngine* mainEngine) = 0;
                virtual void Run() = 0;
                virtual void Stop() = 0;

                bool HasFocus() { return hasFocus; }
                bool IsRunning() { return running; }

            protected:
                virtual void Clean() = 0;

            private:
                // engine has no reason to be copied
                ICoreEngine(const ICoreEngine& other);
                void operator= (const ICoreEngine& other);

            protected:
                bool running;
                bool hasFocus;

                IMainEngine* mainEngine;
                display::I::IDisplayDevice* displayDevice;
                object::I::IObjectManager* objectManager;
                render::I::IRenderContext* renderContext;
                time::I::ITime* time;
            };
        }
    }
}