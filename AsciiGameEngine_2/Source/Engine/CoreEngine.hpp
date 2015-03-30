/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "Engine\Interface\ICoreEngine.hpp"

class CoreEngine : public ICoreEngine
{
public:
    CoreEngine();
    virtual ~CoreEngine();

    virtual void Start(
        ITime* time,
        IDisplayDevice* displayDevice,
        IRenderContext* renderContext,
        IObjectManager* objectManager,
        IMainEngine* mainEngine);
    virtual void Run();
    virtual void Stop();

protected:
    virtual void Clean();
};