#include "Object.hpp"

Object::Object()
{

}

Object::~Object()
{
    for (int i = 0; i < children.size(); i++)
        delete children[i];
}

void Object::Destroy()
{
    for each (Object* obj in children)
        obj->Destroy();
}

void Object::AddChild(Object* child)
{
    this->children.push_back(child);
}

void Object::RemoveChild(Object* child)
{
    unsigned int element = 0;
    bool foundChild = false;

    for (unsigned int i = 0; i < children.size(); i++)
    {
        if (children[i] == child)
        {
            element = i;
            foundChild = true;
            break;
        }
    }

    if (foundChild)
        children.erase(children.begin() + element);
}

void Object::UpdateChildren(float deltaTime)
{
    Update(deltaTime);

    for each (Object* obj in children)
        obj->UpdateChildren(deltaTime);
}

void Object::DrawChildren(Renderer* renderer)
{
    Draw(renderer);

    for each (Object* obj in children)
        obj->DrawChildren(renderer);
}