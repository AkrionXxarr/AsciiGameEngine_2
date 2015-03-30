/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "Akropolix\Engine\Interface\ICoreEngine.hpp"

namespace Akropolix
{
    namespace Engine
    {
        class CoreEngine : public Interface::ICoreEngine
        {
        public:
            CoreEngine();
            virtual ~CoreEngine();

            virtual void Start(
                Time::Interface::ITime* time,
                DisplayDevice::Interface::IDisplayDevice* displayDevice,
                Render::Interface::IRenderContext* renderContext,
                Object::Interface::IObjectManager* objectManager,
                Interface::IMainEngine* mainEngine);
            virtual void Run();
            virtual void Stop();

        protected:
            virtual void Clean();
        };
    };
};