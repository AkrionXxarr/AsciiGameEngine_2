/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <Windows.h>
#include <string>

#include "Akropolix\Object\Windows Console\ConsoleObject.hpp"

class Camera;

class GameObject : public aki::object::wincon::ConsoleObject
{
public:
    GameObject(Camera* camera, std::string name) : camera(camera), name(name), isVisible(true) { }
    virtual ~GameObject() { }

    virtual void Update(float deltaTime) { }
    virtual void Draw(aki::render::I::IRenderContext& renderContext) { }

    virtual void Input(aki::input::wincon::ConsoleInputExt& input) { }

    virtual void OnLoad() { }
    virtual void OnUnload() { }

    void IsVisible(bool visible) { isVisible = visible; }
    bool IsVisible() { return isVisible; }

    const std::string& GetName() { return name; }

protected:
    bool isVisible;

    std::string name;
    Camera* const camera;
};