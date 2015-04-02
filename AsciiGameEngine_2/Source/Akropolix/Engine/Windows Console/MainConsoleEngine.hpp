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


namespace aki
{
    namespace engine
    {
        namespace wincon
        {
            class MainConsoleEngine : public engine::I::IMainEngine
            {
            public:
                MainConsoleEngine(unsigned int width, unsigned int height);
                virtual ~MainConsoleEngine();

                virtual bool Initialize();

                virtual void Start();
                virtual void Stop();
                virtual void Tick(float deltaTime);

                bool HasFocus();
                bool IsRunning();

            protected:
                virtual void Clean();

            protected:
                aki::time::WindowsTime* time;
                display::wincon::Console* console;
                std::shared_ptr<display::wincon::ConsoleBuffer> consoleBuffer;
                aki::render::wincon::ConsoleRenderContext* renderContext;
                aki::object::wincon::ConsoleObjectManager* objectManager;
                aki::input::wincon::ConsoleInputExt* input;
            };
        }
    };
};