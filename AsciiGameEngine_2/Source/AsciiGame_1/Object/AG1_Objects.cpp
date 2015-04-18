/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/


#include <math.h>
#include <sstream>

#include "Akropolix\Input\Windows Console\ConsoleInputExt.hpp"
#include "Akropolix\Utility\Logging\Log.hpp"

#include "AsciiGame_1\Object\AG1_Objects.hpp"
#include "AsciiGame_1\Display\AG1_Camera.hpp"

using namespace aki::render::I;
using namespace aki::input::wincon;
using namespace aki::object::wincon;
using namespace aki::math;

std::default_random_engine generator;

/////////////////////////////
// Player
//
Player::Player(
    float speed,
    CHAR_INFO ci,
    POINT pos,
    int depth,
    Camera* camera,
    UI* const ui,
    Room* room,
    ConsoleObjectManager* objectManager
    ) : GameObject(camera, "player"), ui(ui), room(room), objectManager(objectManager)
{ 
    aki::log::ClearLogFile("MousePosData.txt");

    camera->SetPlayer(this);

    this->isVisible = true;
    this->ci = ci;
    this->depth = depth;
    this->speed = speed;
    up = false; left = false; down = false; right = false;
    this->pos = Vector2f(pos.x, pos.y);

    mouseClick = false;
    mousePos = { 0, 0 };

    isInWater = false;

    curPoint = GetPosAsPoint();
}

void Player::Update(float deltaTime)
{
    if (ui->GetFocusedElement() == UI_ELEMENT::UI_SCREEN)
    {
        if (mouseClick)
        {
            COORD viewPort = camera->viewport->viewBufferSize;

            // With the way things are implemented, I have to take into 
            // account the viewport offset here unfortunately.
            mousePos.X--;
            mousePos.Y--;

            if (mousePos.X >= 0 && mousePos.Y >= 0 && mousePos.X <= viewPort.X && mousePos.Y <= viewPort.Y)
            {
                std::stringstream sstream;

                // Only mouse clicks within the viewport are accepted
                int halfWidth = viewPort.X / 2;
                int halfHeight = viewPort.Y / 2;

                POINT t = { mousePos.X - halfWidth, mousePos.Y - halfHeight };

                sstream << "(" << t.x << ", " << t.y << ")";
                aki::log::LogMessage(sstream.str(), "MousePosData.txt");

                objectManager->RemoveObject(ui->ID); // This is gross and I should feel bad about it...
                objectManager->AddObject(new Bullet(curPoint, { curPoint.x + t.x, curPoint.y + t.y }, 50.0f, depth - 1, camera, true, objectManager, room));
                objectManager->AddObject(ui); // ...but right now the UI must be the very last in the update/draw call chain
            }

            mouseClick = false;
        }

        if (up)
        {
            if ((deltaTime * speed) >= 1.0f)
                return; // Prevent movements of more than 1 tile

            switch (Collision({ curPoint.x, curPoint.y - 1 }))
            {
            case WALL:
                break;

            case PORTAL:
                break;

            case WATER:
                isInWater = true;

                pos.y -= (speed / 3.0f) * deltaTime;
                curPoint = GetPosAsPoint();
                break;

            default:
                isInWater = false;

                pos.y -= speed * deltaTime;
                curPoint = GetPosAsPoint();
            }
        }
        if (left)
        {
            if ((deltaTime * speed) >= 1.0f)
                return; // Prevent movements of more than 1 tile

            switch (Collision({ curPoint.x - 1, curPoint.y }))
            {
            case WALL:
                break;

            case PORTAL:
                break;

            case WATER:
                isInWater = true;

                pos.x -= (speed / 3.0f) * deltaTime;
                curPoint = GetPosAsPoint();
                break;

            default:
                isInWater = false;

                pos.x -= speed * deltaTime;
                curPoint = GetPosAsPoint();
            }
        }
        if (down)
        {
            if ((deltaTime * speed) >= 1.0f)
                return; // Prevent movements of more than 1 tile

            switch (Collision({ curPoint.x, curPoint.y + 1}))
            {
            case WALL:
                break;

            case PORTAL:
                break;

            case WATER:
                isInWater = true;

                pos.y += (speed / 3.0f) * deltaTime;
                curPoint = GetPosAsPoint();
                break;

            default:
                isInWater = false;

                pos.y += speed * deltaTime;
                curPoint = GetPosAsPoint();
            }
        }
        if (right)
        {
            if ((deltaTime * speed) >= 1.0f)
                return; // Prevent movements of more than 1 tile

            switch (Collision({ curPoint.x + 1, curPoint.y }))
            {
            case WALL:
                break;

            case PORTAL:
                break;

            case WATER:
                isInWater = true;

                pos.x += (speed / 3.0f) * deltaTime;
                curPoint = GetPosAsPoint();
                break;

            default:
                isInWater = false;

                pos.x += speed * deltaTime;
                curPoint = GetPosAsPoint();
            }
        }
    }
}

void Player::Draw(IRenderContext& renderContext)
{
    if (isVisible)
    {
        CHAR_INFO t = ci;

        if (isInWater)
            t.Attributes = FOREGROUND_GREEN | FOREGROUND_BLUE;

        camera->Draw(curPoint, t, depth);
    }
}

void Player::Input(ConsoleInputExt& input)
{
    if (ui->GetFocusedElement() == UI_ELEMENT::UI_SCREEN)
    {
        up = input.GetKeyDown(KEYBOARD::W);
        left = input.GetKeyDown(KEYBOARD::A);
        down = input.GetKeyDown(KEYBOARD::S);
        right = input.GetKeyDown(KEYBOARD::D);

        if (input.GetMouseUp(MOUSE_BUTTON::CLICK_LEFT))
        {
            mouseClick = true;
            mousePos = input.GetMousePosition();
        }
    }
}

Player::COLLIDE Player::Collision(POINT p)
{
    COLLIDE collide = NONE;

    for (int i = 0; i < room->objects.size(); i++)
    {
        GameObject* obj = room->objects[i];
        if (obj->GetName() == "wall")
        {
            Wall* wall = (Wall*)obj;
            const POINT wallPos = wall->GetPos();

            if (p.x == wallPos.x && p.y == wallPos.y)
            {
                collide = WALL;
                break;
            }
        }
        else if (obj->GetName() == "portal")
        {
            Portal* portal = (Portal*)obj;
            const POINT portalPos = portal->GetPos();

            if (p.x == portalPos.x && p.y == portalPos.y)
            {
                collide = PORTAL;

                pos = Vector2f(float(portal->GetPlayerPos().x), float(portal->GetPlayerPos().y));
                curPoint = GetPosAsPoint();

                room = portal->GetRoom();

                portal->Trigger();

                break;
            }
        }
        else if (obj->GetName() == "water")
        {
            Water* water = (Water*)obj;
            const POINT waterPos = water->GetPos();

            if (p.x == waterPos.x && p.y == waterPos.y)
            {
                collide = WATER;

                break;
            }
        }
    }

    return collide;
}

POINT Player::GetPosAsPoint()
{
    return { LONG(floor(pos.x + 0.5f)), LONG(floor(pos.y + 0.5f)) };
}

/////////////////////////////
// Floor
//
Floor::Floor(CHAR_INFO ci, POINT pos, int depth, Camera* camera, bool visible) : GameObject(camera, "floor")
{
    this->ci = ci;
    this->pos = pos;
    this->depth = depth;
    this->isVisible = visible;
}

void Floor::Draw(IRenderContext& renderContext)
{
    if (isVisible)
        camera->Draw(pos, ci, depth);
}


/////////////////////////////
// Wall
//
Wall::Wall(CHAR_INFO ci, POINT pos, int depth, Camera* camera, bool visible) : GameObject(camera, "wall")
{
    this->ci = ci;
    this->pos = pos;
    this->depth = depth;
    this->isVisible = visible;
}

void Wall::Draw(IRenderContext& renderContext)
{
    if (isVisible)
        camera->Draw(pos, ci, depth);
}

/////////////////////////////
// Portal
//
Portal::Portal(
    CHAR_INFO ci, 
    POINT pos, 
    POINT playerPos, 
    int depth, 
    Camera* camera, 
    bool visible, 
    Room* room, 
    World* world) : GameObject(camera, "portal"), room(room), world(world)
{
    this->ci = ci;
    this->pos = pos;
    this->playerPos = playerPos;
    this->depth = depth;
    this->isVisible = visible;
}

void Portal::Draw(IRenderContext& renderContext)
{
    if (isVisible)
        camera->Draw(pos, ci, depth);
}

void Portal::Trigger()
{
    world->LoadRoom(room);
}

/////////////////////////////
// Water
//
Water::Water(CHAR_INFO ci1, CHAR_INFO ci2, POINT pos, int depth, Camera* camera, bool visible) : GameObject(camera, "water")
{
    this->ci1 = ci1;
    this->ci2 = ci2;
    this->pos = pos;
    this->depth = depth;
    this->isVisible = visible;
    
    is1 = ((std::uniform_int_distribution<int>(0, 1))(generator) == 0);

    distribution = std::uniform_real_distribution<float>(0.5f, 2.5f);

    changeTime = distribution(generator);
    elapsedTime = 0;
}

void Water::Update(float deltaTime)
{
    if (elapsedTime >= changeTime)
    {
        changeTime = distribution(generator);
        is1 = !is1;
        elapsedTime = 0;
    }
    else
    {
        elapsedTime += deltaTime;
    }
}

void Water::Draw(IRenderContext& renderContext)
{
    if (isVisible)
    {
        if (is1)
        {
            camera->Draw(pos, ci1, depth);
        }
        else
        {
            camera->Draw(pos, ci2, depth);
        }
    }
}


//////////////////////////
// Bullet
//
Bullet::Bullet(
    POINT start,
    POINT end,
    float speed,
    int depth,
    Camera* camera,
    bool visible,
    ConsoleObjectManager* objectManager,
    Room* room) : GameObject(camera, "bullet"), objectManager(objectManager), room(room)
{
    this->start = start;
    this->end = end;
    this->speed = speed;
    this->depth = depth;
    
    pos = Vector2f(float(start.x), float(start.y));
    dir = (Vector2f(float(end.x), float(end.y)) - pos);

    dist = dir.Length();
    dir = dir.Normalized();

    distTraveled = 0;

    curPos = GetPosAsPoint();

    ci.Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
    
    if (abs(dir.x) > 0.92388)
        ci.Char.UnicodeChar = '-';
    else if (abs(dir.x) < 0.38268)
        ci.Char.UnicodeChar = '|';
    else if (dir.x > 0.38268 && dir.y > 0)
        ci.Char.UnicodeChar = '\\';
    else if (dir.x > 0.38268 && dir.y < 0)
        ci.Char.UnicodeChar = '/';
    else if (dir.x < -0.38268 && dir.y > 0)
        ci.Char.UnicodeChar = '/';
    else
        ci.Char.UnicodeChar = '\\';
}

void Bullet::Update(float deltaTime)
{
    float moveAmt = speed * deltaTime;

    pos = pos + (dir * moveAmt);
    distTraveled += moveAmt;
    curPos = GetPosAsPoint();

    if (distTraveled > dist)
    {
        objectManager->RemoveObject(this->ID);
        delete this;
    }
}

void Bullet::Draw(IRenderContext& renderContext)
{
    if (isVisible)
    {
        camera->Draw(curPos, ci, depth);
    }
}

POINT Bullet::GetPosAsPoint()
{
    return{ LONG(floor(pos.x + 0.5f)), LONG(floor(pos.y + 0.5f)) };
}

/////////////////////////////
// Rain
//
Rain::Rain(
    CHAR_INFO ci1, 
    CHAR_INFO ci2, 
    float rainDrawTime, 
    float rainMin, 
    float rainMax, 
    int depth, 
    Camera* camera, 
    bool visible, 
    Room* const room) : GameObject(camera, "rain")
{
    this->ci1 = ci1;
    this->ci2 = ci2;
    this->rainDrawTime = rainDrawTime;
    this->depth = depth;
    this->isVisible = visible;

    for (int i = 0; i < room->objects.size(); i++)
    {
        if (room->objects[i]->GetName() == "floor")
        {
            floorTiles.push_back((Floor*)room->objects[i]);
        }
    }

    // Set the minimum to negative first so that the very first entry of the room
    // will have rain already "in progress" rather than starting with nothing for
    // a brief moment.
    rainHitTimeDist = std::uniform_real_distribution<float>(-0.5f, rainMax);
    rainHitTimes = new float[floorTiles.size()];

    for (int i = 0; i < floorTiles.size(); i++)
    {
        rainHitTimes[i] = rainHitTimeDist(generator);
    }

    rainHitTimeDist = std::uniform_real_distribution<float>(rainMin, rainMax);
}

Rain::~Rain()
{
    if (rainHitTimes)
    {
        delete[] rainHitTimes;
        rainHitTimes = nullptr;
    }
}

void Rain::Update(float deltaTime)
{
    // Update all tiles
    for (int i = 0; i < floorTiles.size(); i++)
    {
        rainHitTimes[i] -= deltaTime;

        if (rainHitTimes[i] <= 0)
        {
            rainHitTimes[i] = rainHitTimeDist(generator);

            RainHitData data;

            data.pos = floorTiles[i]->GetPos();
            data.drawTime = rainDrawTime;

            rainToDraw.push_back(data);
        }
    }

    // Update rain that's being drawn
    for (std::vector<RainHitData>::iterator itr = rainToDraw.begin(); itr != rainToDraw.end(); itr++)
    {
        itr->drawTime -= deltaTime;

        if (itr->drawTime <= 0)
        {
            rainToDraw.erase(itr);
            itr = rainToDraw.begin();
        }
    }
}

void Rain::Draw(IRenderContext& renderContext)
{
    if (isVisible)
    {
        for (int i = 0; i < rainToDraw.size(); i++)
        {
            if (rainToDraw[i].drawTime >= rainDrawTime - (rainDrawTime / 4.0f))
            {
                camera->Draw(rainToDraw[i].pos, ci1, depth);
            }
            else
            {
                camera->Draw(rainToDraw[i].pos, ci2, depth);
            }
        }
    }
}