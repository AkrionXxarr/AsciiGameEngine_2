/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <vector>

#include "Akropolix\Object\Windows Console\ConsoleObjectManager.hpp"

#include "AsciiGame_1\UI\AG1_UI.hpp"
#include "AsciiGame_1\World\AG1_Room.hpp"

class World
{
public:
    World(aki::object::wincon::ConsoleObjectManager* objectManager, UI* ui);
    ~World();

    void LoadRoom(Room* room);
    //void AddRoom(Room* room, bool active);

private:
    //std::vector<Room*> rooms;
    Room* activeRoom;
    aki::object::wincon::ConsoleObjectManager* const objectManager;
    UI* const ui;
};