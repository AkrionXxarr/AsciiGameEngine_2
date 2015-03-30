/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <memory>

#include "Object\Interface\IObject.hpp"

class IRenderContext;

class IObjectManager
{
public:
    IObjectManager() { }
    virtual ~IObjectManager() { }

    virtual void Update(float deltaTime) = 0;
    virtual void Draw(IRenderContext& renderContext) = 0;

    virtual void AddObject(IObject* object) = 0;
    virtual IObject* RemoveObject(unsigned int ID) = 0;

private:
    // Manager has no reason to be copied
    IObjectManager(const IObjectManager& other);
    void operator= (const IObjectManager& other);
};