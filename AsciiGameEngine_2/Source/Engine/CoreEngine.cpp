/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "CoreEngine.hpp"
#include "Engine\Interface\IMainEngine.hpp"
#include "Display Device\Interface\IDisplayDevice.hpp"
#include "Utility\Time\ITime.hpp"
#include "Object\Interface\IObjectManager.hpp"

CoreEngine::CoreEngine()
{
    mainEngine = nullptr;
    displayDevice = nullptr;
    time = nullptr;
    renderContext = nullptr;
    objectManager = nullptr;
}

CoreEngine::~CoreEngine()
{

}

void CoreEngine::Start(
    ITime* time,
    IDisplayDevice* displayDevice,
    IRenderContext* renderContext,
    IObjectManager* objectManager,
    IMainEngine* mainEngine)
{
    if (!running)
    {
        this->mainEngine = mainEngine;
        this->displayDevice = displayDevice;
        this->time = time;
        this->renderContext = renderContext;
        this->objectManager = objectManager;

        Run();
    }
}

void CoreEngine::Run()
{
    running = true;

    time->Tick();

    while (running)
    {
        hasFocus = displayDevice->HasFocus();

        time->Tick();
        float deltaTime = time->DeltaTime();

        mainEngine->Tick(deltaTime);

        objectManager->Update(deltaTime);
        objectManager->Draw(*renderContext);

        displayDevice->Display();
    }
}

void CoreEngine::Stop()
{
    if (running)
    {
        running = false;

        mainEngine->Stop();

        Clean();
    }
}

void CoreEngine::Clean()
{
    displayDevice = nullptr;
    time = nullptr;
    renderContext = nullptr;
    objectManager = nullptr;
}