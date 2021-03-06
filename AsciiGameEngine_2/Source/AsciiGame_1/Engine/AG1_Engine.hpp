/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include "Akropolix\Engine\Windows Console\MainConsoleEngine.hpp"

class UI;
class Camera;
class World;
class Player;

class Engine : public aki::engine::wincon::MainConsoleEngine
{
public:
    Engine();
    virtual ~Engine();

    virtual bool Initialize();

    virtual void Start();
    virtual void Stop();
    virtual void Tick(float deltaTime);

protected:
    virtual void Clean();

private:
    UI* ui;
    Camera* camera;
    World* world;
    Player* player;
};