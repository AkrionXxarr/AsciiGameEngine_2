/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "Akropolix\Engine\Interface\ICoreEngine.hpp"

namespace aki
{
    namespace engine
    {
        class CoreEngine : public I::ICoreEngine
        {
        public:
            CoreEngine();
            virtual ~CoreEngine();

            virtual void Start(
                time::I::ITime* time,
                display::I::IDisplayDevice* displayDevice,
                render::I::IRenderContext* renderContext,
                object::I::IObjectManager* objectManager,
                I::IMainEngine* mainEngine);
            virtual void Run();
            virtual void Stop();

        protected:
            virtual void Clean();
        };
    };
};