#include "Engine.hpp"
#include "BasicRectangle.hpp"
#include "Starfield.hpp"
#include "LineTest.hpp"
#include "Camera.hpp"

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

    ci1.Attributes = f_fullCyan;
    ci2.Attributes = f_darkGray;

    ci1.Char.UnicodeChar = '#';
    ci2.Char.UnicodeChar = '.';

    Vector2f pos(consoleBuffer->GetSizeAsCoord().X / 2, consoleBuffer->GetSizeAsCoord().Y / 2);
    Vector2f dir(0, -1);

    objectManager->AddObject(new Camera(pos, dir, 10, Vector2f(52, 10), Vector2f(105, 10)));

    //objectManager->AddObject(new LineTest(ci1));

    /*
    objectManager->AddObject(new Starfield(
        consoleBuffer->GetSizeAsCoord().X,
        consoleBuffer->GetSizeAsCoord().Y,
        50,
        32.0f,
        20.0f,
        ci1
        ));

    objectManager->AddObject(new Starfield(
        consoleBuffer->GetSizeAsCoord().X,
        consoleBuffer->GetSizeAsCoord().Y,
        20,
        32.0,
        25.0f,
        ci2
        ));
        */

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
    console->ClearBuffer();

    MainConsoleEngine::Tick(deltaTime);

    if (!HasFocus())
        Sleep(100);
}

void Engine::Clean()
{
    MainConsoleEngine::Clean();
}