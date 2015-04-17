/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include <math.h>

#include "Akropolix\Input\Windows Console\ConsoleInputExt.hpp"

#include "AsciiGame_1\Object\AG1_Objects.hpp"
#include "AsciiGame_1\Display\AG1_Camera.hpp"

using namespace aki::render::I;
using namespace aki::input::wincon;

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
    Room* room
    ) : GameObject(camera, "player"), ui(ui), room(room)
{ 
    this->isVisible = true;
    this->ci = ci;
    this->depth = depth;
    this->speed = speed;
    up = false; left = false; down = false; right = false;
    this->pos = aki::math::Vector2f(pos.x, pos.y);

    isInWater = false;

    curPoint = GetPosAsPoint();
    lastPoint = curPoint;
}

void Player::Update(float deltaTime)
{
    if (ui->GetFocusedElement() == UI_ELEMENT::UI_SCREEN)
    {
        if (up)
        {
            if ((deltaTime * speed) >= 1.0f)
                return; // Prevent movements of more than 1 tile

            switch (Collision({ curPoint.x, curPoint.y - 1 }))
            {
            case WALL:
                break;

            case WATER:
                isInWater = true;

                pos.y -= (speed / 3) * deltaTime;
                lastPoint = curPoint;
                curPoint = GetPosAsPoint();
                break;

            default:
                isInWater = false;

                pos.y -= speed * deltaTime;
                lastPoint = curPoint;
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

            case WATER:
                isInWater = true;

                pos.x -= (speed / 3) * deltaTime;
                lastPoint = curPoint;
                curPoint = GetPosAsPoint();
                break;

            default:
                isInWater = false;

                pos.x -= speed * deltaTime;
                lastPoint = curPoint;
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

            case WATER:
                isInWater = true;

                pos.y += (speed / 3) * deltaTime;
                lastPoint = curPoint;
                curPoint = GetPosAsPoint();
                break;

            default:
                isInWater = false;

                pos.y += speed * deltaTime;
                lastPoint = curPoint;
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

            case WATER:
                isInWater = true;

                pos.x += (speed / 3) * deltaTime;
                lastPoint = curPoint;
                curPoint = GetPosAsPoint();
                break;

            default:
                isInWater = false;

                pos.x += speed * deltaTime;
                lastPoint = curPoint;
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
            }
        }
        else if (obj->GetName() == "water")
        {
            Water* water = (Water*)obj;
            const POINT waterPos = water->GetPos();

            if (p.x == waterPos.x && p.y == waterPos.y)
            {
                collide = WATER;
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