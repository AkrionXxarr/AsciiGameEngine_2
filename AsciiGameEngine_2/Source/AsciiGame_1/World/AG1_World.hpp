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
    void Clean();
    //void AddRoom(Room* room, bool active);

public:
    Room* activeRoom;

private:
    //std::vector<Room*> rooms;
    aki::object::wincon::ConsoleObjectManager* const objectManager;
    UI* const ui;
};