/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <Windows.h>

#include "Akropolix\Engine\Interface\IMainEngine.hpp"

#include "Akropolix\Utility\Time\WindowsTime.hpp"
#include "Akropolix\Display Device\Windows Console\Console.hpp"
#include "Akropolix\Render\Windows Console\ConsoleRenderContext.hpp"
#include "Akropolix\Object\Windows Console\ConsoleObjectManager.hpp"
#include "Akropolix\Input\Windows Console\ConsoleInputExt.hpp"


namespace Akropolix
{
    namespace Engine
    {
        namespace WinConsole
        {
            class MainConsoleEngine : public Engine::Interface::IMainEngine
            {
            public:
                MainConsoleEngine(unsigned int width, unsigned int height);
                ~MainConsoleEngine();

                virtual bool Initialize();

                virtual void Start();
                virtual void Stop();
                virtual void Tick(float deltaTime);

            protected:
                virtual void Clean();

            private:
                Akropolix::Time::WindowsTime* time;
                DisplayDevice::WinConsole::Console* console;
                std::shared_ptr<DisplayDevice::WinConsole::ConsoleBuffer> consoleBuffer;
                Akropolix::Render::WinConsole::ConsoleRenderContext* renderContext;
                Akropolix::Object::WinConsole::ConsoleObjectManager* objectManager;
                Akropolix::Input::WinConsole::ConsoleInputExt* input;
            };
        }
    };
};