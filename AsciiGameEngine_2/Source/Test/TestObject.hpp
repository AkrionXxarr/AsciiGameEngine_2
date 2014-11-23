#pragma once

#include "Core\Object\Object.hpp"

class TestObject : public Object
{
public:
    TestObject(int depth, unsigned short color, float xFactor, float yFactor)
    { 
        this->depth = depth;
        this->color = color;
        this->xFactor = xFactor;
        this->yFactor = yFactor;
    }
    virtual ~TestObject() { }

    void Update(float deltaTime);
    void Draw(Renderer* renderer);

private:
    unsigned short color;
    float xFactor, yFactor;
};