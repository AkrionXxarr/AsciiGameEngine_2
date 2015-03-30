/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include "Akropolix\Engine\Windows Console\MainConsoleEngine.hpp"

class Engine : public aki::engine::wincon::MainConsoleEngine
{
public:
    Engine(unsigned int width, unsigned int height);
    virtual ~Engine();

    virtual bool Initialize();

    virtual void Start();
    virtual void Stop();
    virtual void Tick(float deltaTime);

protected:
    virtual void Clean();
};