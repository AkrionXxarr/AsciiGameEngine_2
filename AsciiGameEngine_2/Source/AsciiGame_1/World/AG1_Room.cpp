/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "AsciiGame_1\World\AG1_Room.hpp"

Room::Room(Camera* const camera) : camera(camera)
{
    player = nullptr;
}

Room::~Room()
{
    for (int i = 0; i < physObjects.size(); i++)
    {
        if (physObjects[i])
        {
            delete physObjects[i];
            physObjects[i] = nullptr;
        }
    }

    for (int i = 0; i < other.size(); i++)
    {
        if (other[i])
        {
            delete other[i];
            other[i] = nullptr;
        };
    }
}

void Room::Load(aki::object::wincon::ConsoleObjectManager& objectManager)
{
    for (int i = 0; i < physObjects.size(); i++)
    {
        physObjects[i]->OnLoad();
        objectManager.AddObject(physObjects[i]);
    }

    for (int i = 0; i < other.size(); i++)
    {
        other[i]->OnLoad();
        objectManager.AddObject(other[i]);
    }
}

void Room::Unload(aki::object::wincon::ConsoleObjectManager& objectManager)
{
    for (int i = 0; i < physObjects.size(); i++)
    {
        physObjects[i]->OnUnload();
        objectManager.RemoveObject(physObjects[i]->ID);
    }

    for (int i = 0; i < other.size(); i++)
    {
        other[i]->OnUnload();
        objectManager.RemoveObject(other[i]->ID);
    }
}