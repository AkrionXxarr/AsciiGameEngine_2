#include "Object.hpp"
#include "Component.hpp"

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
    {
        if (obj != nullptr)
        {
            obj->Destroy();
            delete obj;
            obj = nullptr;
        }
    }

    for each (Component* comp in components)
    {
        if (comp != nullptr)
        {
            comp->Destroy();
            delete comp;
            comp = nullptr;
        }
    }
}

void Object::AddChild(Object* child)
{
    this->children.push_back(child);
    child->parent = this;
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

void Object::AddComponent(Component* component)
{
    this->components.push_back(component);
    component->object = this;
}

void Object::RemoveComponent(Component* component)
{
    unsigned int element = 0;
    bool foundComponent = false;

    for (unsigned int i = 0; i < components.size(); i++)
    {
        if (components[i] == component)
        {
            element = i;
            foundComponent = true;
            break;
        }
    }

    if (foundComponent)
        components.erase(components.begin() + element);
}

void Object::UpdateAll(float deltaTime)
{
    Update(deltaTime);

    for each (Object* obj in children)
        obj->UpdateAll(deltaTime);
}

void Object::Update(float deltaTime)
{
    for each (Component* comp in components)
        comp->Update(deltaTime);
}

void Object::DrawAll(Renderer* renderer)
{
    Draw(renderer);

    for each (Object* obj in children)
        obj->DrawAll(renderer);
}

void Object::Draw(Renderer* renderer)
{
    for each (Component* comp in components)
        comp->Draw(renderer);
}