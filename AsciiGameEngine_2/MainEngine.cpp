#include "MainEngine.hpp"
#include "GameCore.hpp"

MainEngine::MainEngine(GameCore* game, unsigned short width, unsigned short height, CONSOLE_FONT_TYPE fontType)
{
    console = new Console(width, height, fontType);
    renderer = new Renderer();
    this->game = game;

    renderer->SetConsoleHandle(console);
    renderer->SetBufferClearOptions(CONSOLE_BUFFER | Z_BUFFER);
}

MainEngine::~MainEngine()
{
    if (console != nullptr)
        delete console;
    if (renderer != nullptr)
        delete renderer;
    if (game != nullptr)
        delete game;
}

void MainEngine::Start()
{
    if (running)
        return;

    Run();
}

void MainEngine::Stop()
{
    running = false;
}

void MainEngine::Run()
{
    running = true;

    game->Initialize();

    while (running)
    {
        game->Update(0);
        game->Draw(renderer);
    }
}