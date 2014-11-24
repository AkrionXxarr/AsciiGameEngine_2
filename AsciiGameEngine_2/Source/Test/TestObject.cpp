#include "TestObject.hpp"

#include <math.h>

float counter = 0;
void TestObject::Update(float deltaTime)
{
    counter += 0.0005f;

    position.x = std::sin(counter) * xFactor;
    position.y = std::cos(counter) * yFactor;
}

void TestObject::Draw(Renderer* renderer)
{
    Vector2f v = position.AsInt();
    renderer->DrawBuffer(v.x, v.y, depth, 15, 10, buffer);
}