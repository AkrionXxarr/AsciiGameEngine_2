#pragma once

#include <vector>

#include "Core\Display\ConsoleDefines.hpp"
#include "Core\Math\Vector2f.hpp"
#include "Core\Draw\Renderer.hpp"

class Object
{
public:
    Object();
    virtual ~Object();

    virtual void Destroy();

    void AddChild(Object* child);
    void RemoveChild(Object* child);

    void UpdateChildren(float deltaTime);
    void DrawChildren(Renderer* renderer);

protected:
    virtual void Update(float deltaTime) { }
    virtual void Draw(Renderer* renderer) { }

public:
    int depth;
    Vector2f position;
    Vector2f scale;
    Vector2f yBasis, xBasis;

protected:
    std::vector<Object*> children;
};