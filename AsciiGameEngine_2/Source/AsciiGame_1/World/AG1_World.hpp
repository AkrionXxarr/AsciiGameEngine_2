/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include <vector>

#include "Akropolix\Object\Windows Console\ConsoleObjectManager.hpp"

#include "AsciiGame_1\World\AG1_Room.hpp"

class World
{
public:
    World(aki::object::wincon::ConsoleObjectManager* objectManager);
    ~World();

    void AddRoom(Room* room, bool active);

private:
    std::vector<Room*> rooms;
    Room* activeRoom;
    aki::object::wincon::ConsoleObjectManager* objectManager;
};