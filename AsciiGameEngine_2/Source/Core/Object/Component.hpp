#pragma once

class Renderer;
class Object;

class Component
{
public:
    Component() { }
    virtual ~Component() { }

    virtual void Destroy() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw(Renderer* renderer) = 0;

public:
    Object* object;
};