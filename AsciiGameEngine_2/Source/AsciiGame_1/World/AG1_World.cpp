/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "Akropolix\Display Device\Windows Console\ConsoleDefines.hpp"

#include "AsciiGame_1\World\AG1_World.hpp"


World::World(aki::object::wincon::ConsoleObjectManager* objectManager)
{
    this->objectManager = objectManager;
}

World::~World()
{
}

void World::AddRoom(Room* room, bool active)
{
    rooms.push_back(room);

    if (active)
    {
        activeRoom = room;
        room->Load(*objectManager);
    }
}