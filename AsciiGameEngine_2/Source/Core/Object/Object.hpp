#pragma once

#include <Windows.h>
#include <vector>

#include "Core\Display\ConsoleDefines.hpp"
#include "Core\Math\Vector2f.hpp"
#include "Core\Engine\Renderer.hpp"

class Component;

class Object
{
public:
    Object();
    virtual ~Object();

    virtual void Destroy();

    void AddChild(Object* child);
    void RemoveChild(Object* child);

    void AddComponent(Component* component);
    void RemoveComponent(Component* component);

    void Update(float deltaTime);
    void UpdateAll(float deltaTime);

    void Draw(Renderer* renderer);
    void DrawAll(Renderer* renderer);

public:
    int depth;
    Vector2f position;
    Object* parent;

private:
    std::vector<Object*> children;
    std::vector<Component*> components;
};