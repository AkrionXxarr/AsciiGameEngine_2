#include "Engine.hpp"
#include "BasicRectangle.hpp"
#include "Starfield.hpp"
#include "Akropolix\Display Device\Windows Console\ConsoleDefines.hpp"

using namespace aki::input::wincon;
using namespace aki::engine::wincon;
using namespace aki::math;

Engine::Engine(unsigned int width, unsigned int height) : MainConsoleEngine(width, height)
{

}

Engine::~Engine()
{

}

bool Engine::Initialize()
{
    MainConsoleEngine::Initialize();

    CHAR_INFO ci1;
    CHAR_INFO ci2;

    ci1.Attributes = f_darkGray;
    ci2.Attributes = f_halfGreen;

    ci1.Char.UnicodeChar = '.';
    ci2.Char.UnicodeChar = '.';

    objectManager->AddObject(new Starfield(
        consoleBuffer->GetSizeAsCoord().X,
        consoleBuffer->GetSizeAsCoord().Y,
        500,
        32.0f,
        30.0f,
        ci1
        ));

    objectManager->AddObject(new Starfield(
        consoleBuffer->GetSizeAsCoord().X,
        consoleBuffer->GetSizeAsCoord().Y,
        200,
        32.0,
        40.0f,
        ci2
        ));

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
}

void Engine::Clean()
{
    MainConsoleEngine::Clean();
}