/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "AsciiGame_1\World\AG1_Room.hpp"

Room::Room(Camera* const camera) : camera(camera)
{

}

Room::~Room()
{
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i])
        {
            delete objects[i];
            objects[i] = nullptr;
        }
    }
}

void Room::Load(aki::object::wincon::ConsoleObjectManager& objectManager)
{
    for (int i = 0; i < objects.size(); i++)
    {
        objects[i]->OnLoad();
        objectManager.AddObject(objects[i]);
    }
}

void Room::Unload(aki::object::wincon::ConsoleObjectManager& objectManager)
{
    for (int i = 0; i < objects.size(); i++)
    {
        objects[i]->OnUnload();
        objectManager.RemoveObject(objects[i]->ID);
    }
}