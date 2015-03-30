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
#include "Akropolix\Input\Windows Input\ConsoleInputExt.hpp"


namespace Akropolix
{
    class MainConsoleEngine : public IMainEngine
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
        WindowsTime* time;
        Console* console;
        std::shared_ptr<ConsoleBuffer> consoleBuffer;
        ConsoleRenderContext* renderContext;
        ConsoleObjectManager* objectManager;
        ConsoleInputExt* input;
    };
};