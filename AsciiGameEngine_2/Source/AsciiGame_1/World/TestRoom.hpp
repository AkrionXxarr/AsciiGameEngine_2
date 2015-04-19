/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include "Akropolix\Object\Windows Console\ConsoleObjectManager.hpp"

#include "AsciiGame_1\World\AG1_Room.hpp"

class Camera;
class World;
class UI;

class TestRoom1 : public Room
{
public:
    TestRoom1(Camera* const camera, World* world, UI* ui, aki::object::wincon::ConsoleObjectManager* objectManager);
    ~TestRoom1();

    void AddRightRoom(Room* room);

private:
    World* const world;
};

class TestRoom2 : public Room
{
public:
    TestRoom2(Camera* const camera, World* world, UI* ui, aki::object::wincon::ConsoleObjectManager* objectManager);
    ~TestRoom2();

    void AddLeftRoom(Room* room);

private:
    World* const world;
};