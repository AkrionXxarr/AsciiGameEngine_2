/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "Akropolix\Engine\Windows Console\MainConsoleEngine.hpp"
#include "Akropolix\Engine\CoreEngine.hpp"

using namespace aki::time;
using namespace aki::display::wincon;
using namespace aki::render::wincon;
using namespace aki::object::wincon;
using namespace aki::input::wincon;

namespace aki
{
    namespace engine
    {
        namespace wincon
        {
            MainConsoleEngine::MainConsoleEngine(unsigned int width, unsigned int height, CONSOLE_FONT::Type fontType)
            {
                this->fontType = fontType;

                time = new WindowsTime();
                console = new Console();
                consoleBuffer = std::make_shared<ConsoleBuffer>(width, height);
                renderContext = new ConsoleRenderContext();
                objectManager = new ConsoleObjectManager();
            }

            // Don't really like how memory is handled here, deal with later
            MainConsoleEngine::~MainConsoleEngine()
            {
                if (coreEngine)
                    delete coreEngine;
                if (time)
                    delete time;
                if (console)
                    delete console;
                if (renderContext)
                    delete renderContext;
                if (objectManager)
                    delete objectManager;
                if (input)
                    delete input;
            }

            bool MainConsoleEngine::Initialize()
            {
                coreEngine = new CoreEngine();
                console->CreateDevice(consoleBuffer, 0, fontType);
                input = new ConsoleInputExt(32, console->GetHandle());

                renderContext->Initialize(consoleBuffer);

                return true;
            }

            void MainConsoleEngine::Start()
            {
                if (coreEngine)
                    coreEngine->Start(time, console, renderContext, objectManager, this);
            }

            void MainConsoleEngine::Stop()
            {
                Clean();
            }

            void MainConsoleEngine::Tick(float deltaTime)
            {
                input->Tick();
                objectManager->Input(*input);
            }

            void MainConsoleEngine::Clean()
            {
            }

            bool MainConsoleEngine::HasFocus()
            {
                return coreEngine->HasFocus();
            }

            bool MainConsoleEngine::IsRunning()
            {
                return coreEngine->IsRunning();
            }
        }
    }
};