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
#include "AsciiGame_1\World\AG1_World.hpp"

extern bool killGame;

/////////////////////////////
// Player
//
class Player : public GameObject
{
    enum COLLIDE
    {
        NONE,
        WALL,
        PORTAL,
        WATER
    };
public:
    Player(
        float speed, 
        CHAR_INFO ci, 
        POINT pos, 
        int depth, 
        int maxHealth,
        Camera* camera, 
        UI* ui,
        Room* room,
        World* world,
        aki::object::wincon::ConsoleObjectManager* objectManager);
    ~Player() { }

    virtual void Update(float deltaTime);
    virtual void Draw(aki::render::I::IRenderContext& renderContext);
   
    virtual void Input(aki::input::wincon::ConsoleInputExt& input);

    void Hit(int damage) { health -= damage; }

    COLLIDE Collision(POINT p);

    POINT GetPosAsPoint();

private:
    UI* const ui;
    World* const world;
    Room* room;
    aki::object::wincon::ConsoleObjectManager* const objectManager;

    CHAR_INFO ci;
    aki::math::Vector2f pos;
    POINT curPoint;
    int depth;

    bool mouseClick;
    COORD mousePos;

    bool isInWater;

    int maxHealth;
    int health;

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

    const POINT& GetPos() { return pos; }

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
// Portal
//
class Portal : public GameObject
{
public:
    Portal(CHAR_INFO ci, POINT pos, POINT playerPos, int depth, Camera* camera, bool visible, Room* next, World* world);
    ~Portal() { }

    virtual void Draw(aki::render::I::IRenderContext& renderContext);

    void Trigger();

    const POINT& GetPos() { return pos; }
    const POINT& GetPlayerPos() { return playerPos; }
    Room* const GetRoom() { return room; }

private:
    Room* const room;
    World* const world;

    POINT pos, playerPos;
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
    enum COLLIDE
    {
        NONE,
        WALL,
        PORTAL,
        PLAYER,
        ENEMY
    };

public:
    Bullet(
        int attributes,
        POINT start, 
        POINT end, 
        float speed, 
        int damage,
        int depth, 
        Camera* camera, 
        bool visible, 
        bool isPlayer,
        aki::object::wincon::ConsoleObjectManager* objectManager,
        Room* room,
        World* world);
    ~Bullet() { }

    virtual void Update(float deltaTime);
    virtual void Draw(aki::render::I::IRenderContext& renderContext);

    COLLIDE Collision(POINT p);

    POINT GetPosAsPoint();

private:
    aki::object::wincon::ConsoleObjectManager* const objectManager;
    Room* const room;
    World* const world;

    aki::math::Vector2f pos, dir;
    POINT start, end, curPos;
    CHAR_INFO ci;
    int depth;

    bool isPlayer;

    float speed;
    int damage;
    float dist, distTraveled;
};

/////////////////////////////
// Rain
//
class Rain : public GameObject
{
    struct RainHitData
    {
        POINT pos;
        float drawTime;
    };

public:
    Rain(CHAR_INFO ci1, CHAR_INFO ci2, float rainDrawTime, float rainMin, float rainMax, int depth, Camera* camera, bool visible, Room* const room);
    ~Rain();

    virtual void Update(float deltaTime);
    virtual void Draw(aki::render::I::IRenderContext& renderContext);

private:
    CHAR_INFO ci1, ci2;
    int depth;

    std::uniform_real_distribution<float> rainHitTimeDist;

    std::vector<Floor*> floorTiles;
    std::vector<RainHitData> rainToDraw;
    float* rainHitTimes;
    float rainDrawTime;
};

/////////////////////////////
// Enemy
//
class Enemy : public GameObject
{
    enum COLLIDE
    {
        NONE,
        WALL,
        PORTAL,
        WATER
    };
public:
    Enemy(
        CHAR_INFO ci,
        POINT pos,
        float rof,
        float speed,
        int maxHealth,
        int depth,
        Camera* camera,
        UI* ui,
        Room* room,
        World* world,
        aki::object::wincon::ConsoleObjectManager* objectManager);
    ~Enemy() { }

    virtual void Update(float deltaTime);
    virtual void Draw(aki::render::I::IRenderContext& renderContext);

    virtual void Input(aki::input::wincon::ConsoleInputExt& input);

    void Hit(int damage) { health -= damage; }

    COLLIDE Collision(POINT p);

    POINT GetPosAsPoint();

private:
    UI* const ui;
    Room* room;
    World* const world;
    aki::object::wincon::ConsoleObjectManager* const objectManager;

    CHAR_INFO ci;
    aki::math::Vector2f pos;
    POINT curPoint;
    int depth;

    bool mouseClick;
    COORD mousePos;

    bool isActive;

    int health;
    int maxHealth;

    float speed;
    float rof;
    float elapsedTime;
};;