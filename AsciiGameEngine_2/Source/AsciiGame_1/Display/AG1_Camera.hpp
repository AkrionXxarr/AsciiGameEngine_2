/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <Windows.h>

#include "Akropolix\Utility\Math\Vector2f.hpp"

class Viewport;
class World;
class Player;

class Camera
{
    friend class Player; // For now, I guess, I dunno. :B

public:
    Camera(Viewport* const viewport, World* const world);
    ~Camera();

    void Move(float x, float y) { pos.x += x; pos.y += y; }

    void Clear();
    void Draw(POINT objPos, CHAR_INFO& ci, int depth);

    void SetPlayer(Player* player) { this->player = player; }

private:
    Viewport* const viewport;
    World* const world;

    Player* player;

    aki::math::Vector2f pos;
};