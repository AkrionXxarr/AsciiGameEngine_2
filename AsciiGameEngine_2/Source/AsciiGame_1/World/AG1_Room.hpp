/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <vector>

#include "Akropolix\Object\Windows Console\ConsoleObjectManager.hpp"

#include "AsciiGame_1\Object\AG1_GameObject.hpp"

class Camera;

class Room
{
public:
    Room(Camera* const camera);
    virtual ~Room();

    void Load(aki::object::wincon::ConsoleObjectManager& objectManager);
    void Unload(aki::object::wincon::ConsoleObjectManager& objectManager);

public:
    std::vector<GameObject*> objects;
    Camera* const camera;
};