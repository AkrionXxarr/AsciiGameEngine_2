/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "AG1_Engine.hpp"

#include "AsciiGame_1\UI\AG1_UI.hpp"
#include "AsciiGame_1\Display\AG1_Camera.hpp"
#include "AsciiGame_1\World\AG1_World.hpp"
#include "AsciiGame_1\Object\AG1_Objects.hpp"

#include "Akropolix\Display Device\Windows Console\ConsoleDefines.hpp"
#include "Akropolix\Utility\Logging\Log.hpp"

#include "AsciiGame_1\World\TestRoom.hpp"

using namespace aki::display::wincon;
using namespace aki::input::wincon;
using namespace aki::engine::wincon;

#define TEMP_LOG "TempFile.txt"

Engine::Engine() : MainConsoleEngine(80, 80, CONSOLE_FONT::_8x8)
{
    aki::log::ClearLogFile(TEMP_LOG);
}

Engine::~Engine()
{

}

bool Engine::Initialize()
{
    MainConsoleEngine::Initialize();

    COORD worldSize = { 256, 256 };

    ui = new UI(f_darkGray, f_halfYellow, f_fullGreen);
    world = new World(objectManager, ui);
    camera = new Camera((UIScreen*)ui->GetUIElement(UI_ELEMENT::UI_SCREEN), world);

    CHAR_INFO playerCI;
    TestRoom1* startRoom = new TestRoom1(camera, world, ui, objectManager);
    TestRoom2* nextRoom = new TestRoom2(camera, world, ui, objectManager);

    startRoom->AddRightRoom(nextRoom);
    nextRoom->AddLeftRoom(startRoom);

    playerCI.Attributes = f_white;
    playerCI.Char.UnicodeChar = '@';

    player = new Player(20.0f, playerCI, { 5, 5 }, 5, 100, camera, ui, startRoom, world, objectManager);

    startRoom->player = player;
    nextRoom->player = player;

    ui->SetFocusedElement(UI_ELEMENT::UI_SCREEN);

    objectManager->AddObject(player);
    objectManager->AddObject(ui);

    world->LoadRoom(startRoom);

    killGame = false;
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

    camera->Clear();

    if (input->GetKeyUp(KEYBOARD::ENTER))
    {
        if (ui->GetFocusedElement() == UI_ELEMENT::UI_COMMAND)
        {
            std::string str = ((UICommand*)ui->GetUIElement(UI_ELEMENT::UI_COMMAND))->GetCommand();
            ui->SetFocusedElement(UI_ELEMENT::UI_SCREEN);

            aki::log::LogMessage(str, TEMP_LOG);
        }
        else
        {
            ui->SetFocusedElement(UI_ELEMENT::UI_COMMAND);
        }
    }

    if (!HasFocus())
        Sleep(100);

    if (killGame)
        this->Stop();
}

void Engine::Clean()
{
    MainConsoleEngine::Clean();
    world->Clean();
}