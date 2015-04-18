/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <vector>
#include <random>

#include "Akropolix\Utility\Math\Vector2f.hpp"
#include "Akropolix\Object\Windows Console\ConsoleObjectManager.hpp"

#include "AsciiGame_1\Object\AG1_GameObject.hpp"
#include "AsciiGame_1\World\AG1_Room.hpp"
#include "AsciiGame_1\UI\AG1_UI.hpp"

/////////////////////////////
// Player
//
class Player : public GameObject
{
    enum COLLIDE
    {
        NONE,
        WALL,
        WATER
    };
public:
    Player(
        float speed, 
        CHAR_INFO ci, 
        POINT pos, 
        int depth, 
        Camera* camera, 
        UI* ui,
        Room* room,
        aki::object::wincon::ConsoleObjectManager* objectManager);
    ~Player() { }

    virtual void Update(float deltaTime);
    virtual void Draw(aki::render::I::IRenderContext& renderContext);
   
    virtual void Input(aki::input::wincon::ConsoleInputExt& input);

    COLLIDE Collision(POINT p);

    POINT GetPosAsPoint();

private:
    UI* const ui;
    Room* const room;
    aki::object::wincon::ConsoleObjectManager* const objectManager;

    CHAR_INFO ci;
    aki::math::Vector2f pos;
    POINT curPoint;
    int depth;

    bool mouseClick;
    COORD mousePos;

    bool isInWater;

    bool up, left, down, right;
    float speed;
};


/////////////////////////////
// Floor
//
class Floor : public GameObject
{
public:
    Floor(CHAR_INFO ci, POINT pos, int depth, Camera* camera, bool visible);
    ~Floor() { }

    virtual void Draw(aki::render::I::IRenderContext& renderContext);

private:
    POINT pos;
    CHAR_INFO ci;
    int depth;
};


/////////////////////////////
// Wall
//
class Wall : public GameObject
{
public:
    Wall(CHAR_INFO ci, POINT pos, int depth, Camera* camera, bool visible);
    ~Wall() { }

    virtual void Draw(aki::render::I::IRenderContext& renderContext);

    const POINT& GetPos() { return pos; }

private:
    POINT pos;
    CHAR_INFO ci;
    int depth;
};

/////////////////////////////
// Water
//
class Water : public GameObject
{
public:
    Water(CHAR_INFO ci1, CHAR_INFO ci2, POINT pos, int depth, Camera* camera, bool visible);
    ~Water() { }

    virtual void Update(float deltaTime);
    virtual void Draw(aki::render::I::IRenderContext& renderContext);

    const POINT& GetPos() { return pos; }

private:
    POINT pos;
    CHAR_INFO ci1;
    CHAR_INFO ci2;
    int depth;
    bool is1;

    std::uniform_real_distribution<float> distribution;
    float changeTime, elapsedTime;
};

//////////////////////////
// Bullet
//
class Bullet : public GameObject
{
public:
    Bullet(POINT start, POINT end, float speed, Camera* camera, bool visible, aki::object::wincon::ConsoleObjectManager* objectManager);
    ~Bullet() { }

    virtual void Update(float deltaTime);
    virtual void Draw(aki::render::I::IRenderContext& renderContext);

    POINT GetPosAsPoint();

private:
    aki::object::wincon::ConsoleObjectManager* const objectManager;

    aki::math::Vector2f pos, dir;
    POINT start, end, curPos;
    CHAR_INFO ci;
    int depth;

    float speed;
    float dist, distTraveled;
};