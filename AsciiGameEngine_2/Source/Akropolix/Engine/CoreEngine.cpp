/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "Akropolix\Engine\CoreEngine.hpp"
#include "Akropolix\Engine\Interface\IMainEngine.hpp"
#include "Akropolix\Display Device\Interface\IDisplayDevice.hpp"
#include "Akropolix\Utility\Time\ITime.hpp"
#include "Akropolix\Object\Interface\IObjectManager.hpp"

using namespace aki::time::I;
using namespace aki::display::I;
using namespace aki::engine::I;
using namespace aki::render::I;
using namespace aki::object::I;

namespace aki
{
    namespace engine
    {
        CoreEngine::CoreEngine()
        {
            mainEngine = nullptr;
            displayDevice = nullptr;
            time = nullptr;
            renderContext = nullptr;
            objectManager = nullptr;
        }

        CoreEngine::~CoreEngine()
        {

        }

        void CoreEngine::Start(
            ITime* time,
            IDisplayDevice* displayDevice,
            IRenderContext* renderContext,
            IObjectManager* objectManager,
            IMainEngine* mainEngine)
        {
            if (!running)
            {
                this->mainEngine = mainEngine;
                this->displayDevice = displayDevice;
                this->time = time;
                this->renderContext = renderContext;
                this->objectManager = objectManager;

                Run();
            }
        }

        void CoreEngine::Run()
        {
            running = true;

            time->Tick();

            while (running)
            {
                hasFocus = displayDevice->HasFocus();

                time->Tick();
                float deltaTime = time->DeltaTime();

                mainEngine->Tick(deltaTime);

                // Hack to fix crash, since running goes faulse after Tick and Clean kills the pointers.
                if (!running)
                    break;

                objectManager->Update(deltaTime);
                objectManager->Draw(*renderContext);

                displayDevice->Display();
            }
        }

        void CoreEngine::Stop()
        {
            if (running)
            {
                running = false;

                //mainEngine->Stop();

                Clean();
            }
        }

        void CoreEngine::Clean()
        {
            mainEngine->Clean();

            displayDevice = nullptr;
            time = nullptr;
            renderContext = nullptr;
            objectManager = nullptr;
        }
    }
}