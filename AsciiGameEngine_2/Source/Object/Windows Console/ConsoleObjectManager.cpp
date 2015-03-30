/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "Object\Windows Console\ConsoleObjectManager.hpp"
#include "Object\Windows Console\ConsoleObject.hpp"

unsigned int BASIC_ID = 0;

ConsoleObjectManager::ConsoleObjectManager()
{

}

ConsoleObjectManager::~ConsoleObjectManager()
{
    for (unsigned int i = 0; i < objects.size(); i++)
    {
        if (objects[i])
            delete objects[i];

        objects[i] = nullptr;
    }
}

void ConsoleObjectManager::Update(float deltaTime)
{
    for (unsigned int i = 0; i < objects.size(); i++)
    {
        objects[i]->Update(deltaTime);
    }
}

void ConsoleObjectManager::Draw(IRenderContext& renderContext)
{
    for (unsigned int i = 0; i < objects.size(); i++)
    {
        objects[i]->Draw(renderContext);
    }
}

void ConsoleObjectManager::Input(ConsoleInputExt& input)
{
    for (unsigned int i = 0; i < objects.size(); i++)
    {
        objects[i]->Input(input);
    }
}

void ConsoleObjectManager::AddObject(IObject* object)
{
    object->ID = BASIC_ID++;
    objects.push_back((ConsoleObject*)object);
}

IObject* ConsoleObjectManager::RemoveObject(unsigned int ID)
{
    ConsoleObject* object = nullptr;
    std::vector<ConsoleObject*>::iterator itr;

    for (itr = objects.begin(); itr != objects.end(); itr++)
    {
        if ((*itr)->ID == ID)
            break;
    }

    if (itr != objects.end())
    {
        object = (*itr);
        objects.erase(itr);
    }

    return object;
}