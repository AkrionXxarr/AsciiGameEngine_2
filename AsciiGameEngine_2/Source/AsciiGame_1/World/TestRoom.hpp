/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include "AsciiGame_1\World\AG1_Room.hpp"

class Camera;

class TestRoom : public Room
{
public:
    TestRoom(Camera* const camera);
    ~TestRoom();

    void Load(aki::object::wincon::ConsoleObjectManager& objectManager);
    void Unload(aki::object::wincon::ConsoleObjectManager& objectManager);
};