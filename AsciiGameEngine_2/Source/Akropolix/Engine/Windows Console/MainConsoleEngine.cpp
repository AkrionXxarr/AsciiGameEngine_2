/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "Akropolix\Engine\Windows Console\MainConsoleEngine.hpp"
#include "Akropolix\Engine\CoreEngine.hpp"

#include "Akropolix\Object\Windows Console\TestObject.hpp"

MainConsoleEngine::MainConsoleEngine(unsigned int width, unsigned int height)
{
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
    console->CreateDevice(consoleBuffer, 0, FONT_8x8);
    input = new ConsoleInputExt(10, console->GetHandle());

    renderContext->Initialize(consoleBuffer);

    objectManager->AddObject(new TestObject(0, 0));
    objectManager->AddObject(new TestObject(4, 0));
    objectManager->AddObject(new TestObject(0, 4));
    objectManager->AddObject(new TestObject(4, 4));

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
    console->ClearBuffer();
    input->Tick();
    objectManager->Input(*input);

    if (input->GetKeyUp(KEYBOARD::SPACE))
    {
        objectManager->RemoveObject(2);
    }
}

void MainConsoleEngine::Clean()
{
}