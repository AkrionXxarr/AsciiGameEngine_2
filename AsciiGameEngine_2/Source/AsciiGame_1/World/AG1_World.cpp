/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "Akropolix\Display Device\Windows Console\ConsoleDefines.hpp"

#include "AsciiGame_1\World\AG1_World.hpp"


World::World(aki::object::wincon::ConsoleObjectManager* objectManager, UI* ui) : objectManager(objectManager), ui(ui)
{
    activeRoom = nullptr;
}

World::~World()
{
}

void World::LoadRoom(Room* room)
{
    if (activeRoom)
    {
        activeRoom->Unload(*objectManager);
        activeRoom = nullptr;
    }

    activeRoom = room;

    objectManager->RemoveObject(ui->ID); // TERRIBLE >:F
    room->Load(*objectManager);
    objectManager->AddObject(ui);
}

/*
void World::AddRoom(Room* room, bool active)
{
    rooms.push_back(room);

    if (active)
    {
        activeRoom = room;
        room->Load(*objectManager);
    }
}
*/