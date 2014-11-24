#include "TestComponent.hpp"
#include "Core\Object\Object.hpp"
#include "Core\Engine\Renderer.hpp"
#include "Core\Math\Vector2f.hpp"

#include <math.h>

void TestComponent::Destroy()
{
    if (buffer != nullptr)
        delete[] buffer;
}

float counter = 0;
void TestComponent::Update(float deltaTime)
{
    counter += 0.0005f;

    object->position.x = std::sin(counter) * xFactor;
    object->position.y = std::cos(counter) * yFactor;
}

void TestComponent::Draw(Renderer* renderer)
{
    Vector2f v = object->position.AsInt();
    renderer->DrawBuffer(v.x, v.y, depth, 15, 10, buffer);
}