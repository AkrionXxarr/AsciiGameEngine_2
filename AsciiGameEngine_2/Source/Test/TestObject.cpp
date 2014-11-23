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
    for (int x = v.x; x < 15 + v.x; x++)
    {
        for (int y = v.y; y < 15 + v.y; y++)
        {
            renderer->DrawPixel(x, y, depth, '#', color);
        }
    }
}