/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include "AsciiGame_1\World\AG1_Room.hpp"

class Camera;
class World;

class TestRoom1 : public Room
{
public:
    TestRoom1(Camera* const camera, World* world);
    ~TestRoom1();

    void AddRightRoom(Room* room);

private:
    World* const world;
};

class TestRoom2 : public Room
{
public:
    TestRoom2(Camera* const camera, World* world);
    ~TestRoom2();

    void AddLeftRoom(Room* room);

private:
    World* const world;
};