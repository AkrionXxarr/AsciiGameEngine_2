#pragma once

#include "Console.hpp"
#include "Renderer.hpp"

class GameCore;

class MainEngine
{
public:
    MainEngine(GameCore* game, unsigned short width, unsigned short height, CONSOLE_FONT_TYPE fontType = FONT_8x12);
    ~MainEngine();

    void Start();
    void Stop();
    void Run();

private:
    Console* console = nullptr;
    Renderer* renderer = nullptr;
    GameCore* game = nullptr;

    bool running = false;
};