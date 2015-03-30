#include "Engine.hpp"
#include "BasicRectangle.hpp"

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

    objectManager->AddObject(new BasicRectangle(4, 4, Vector2f(3, 3)));
    objectManager->AddObject(new BasicRectangle(3, 10, Vector2f(10, 10)));

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