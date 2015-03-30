/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "Akropolix\Engine\Interface\ICoreEngine.hpp"

namespace Akropolix
{
    namespace Engine
    {
        class CoreEngine : public ICoreEngine
        {
        public:
            CoreEngine();
            virtual ~CoreEngine();

            virtual void Start(
                ITime* time,
                IDisplayDevice* displayDevice,
                IRenderContext* renderContext,
                IObjectManager* objectManager,
                IMainEngine* mainEngine);
            virtual void Run();
            virtual void Stop();

        protected:
            virtual void Clean();
        };
    };
};