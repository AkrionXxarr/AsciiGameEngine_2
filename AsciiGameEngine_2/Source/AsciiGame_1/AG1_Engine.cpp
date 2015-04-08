/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "AG1_Engine.hpp"

#include "AG1_UI.hpp"

#include "Akropolix\Display Device\Windows Console\ConsoleDefines.hpp"

using namespace aki::display::wincon;
using namespace aki::input::wincon;
using namespace aki::engine::wincon;

Engine::Engine() : MainConsoleEngine(80, 80, CONSOLE_FONT::_8x8)
{

}

Engine::~Engine()
{

}

bool Engine::Initialize()
{
    MainConsoleEngine::Initialize();

    UI* ui = new UI(f_darkGray, f_fullGreen, f_fullCyan);

    ui->SetFocusedElement(UI_ELEMENT::UI_COMMAND);

    objectManager->AddObject(ui);

    return true;
}

void Engine::Start()
{
    MainConsoleEngine::Start();
}

void Engine::Stop()
{
    MainConsoleEngine::Stop();
}

void Engine::Tick(float deltaTime)
{
    MainConsoleEngine::Tick(deltaTime);

    if (!HasFocus())
        Sleep(100);
}

void Engine::Clean()
{
    MainConsoleEngine::Clean();
}