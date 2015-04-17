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
}

void Player::Update(float deltaTime)
{
    if (ui->GetFocusedElement() == UI_ELEMENT::UI_SCREEN)
    {
        if (up)
        {
            if ((deltaTime * speed) >= 1.0f)
                return; // Prevent movements of more than 1 tile

            pos.y -= speed * deltaTime;
            if (CollidesWithWall())
                pos.y += speed * deltaTime;
        }
        if (left)
        {
            if ((deltaTime * speed) >= 1.0f)
                return; // Prevent movements of more than 1 tile

            pos.x -= speed * deltaTime;
            if (CollidesWithWall())
                pos.x += speed * deltaTime;
        }
        if (down)
        {
            if ((deltaTime * speed) >= 1.0f)
                return; // Prevent movements of more than 1 tile

            pos.y += speed * deltaTime;
            if (CollidesWithWall())
                pos.y -= speed * deltaTime;
        }
        if (right)
        {
            if ((deltaTime * speed) >= 1.0f)
                return; // Prevent movements of more than 1 tile

            pos.x += speed * deltaTime;
            if (CollidesWithWall())
                pos.x -= speed * deltaTime;
        }
    }
}

void Player::Draw(IRenderContext& renderContext)
{
    if (isVisible)
        camera->Draw({ LONG(floor(pos.x)), LONG(floor(pos.y)) }, ci, depth);
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

bool Player::CollidesWithWall()
{
    for (int i = 0; i < room->objects.size(); i++)
    {
        if (room->objects[i]->GetName() == "wall")
        {
            Wall* wall = (Wall*)room->objects[i];
            const POINT wallPos = wall->GetPos();
            const POINT p = GetPosAsPoint();

            if (p.x == wallPos.x && p.y == wallPos.y)
            {
                return true;
            }
        }
    }

    return false;
}

POINT Player::GetPosAsPoint()
{
    return { LONG(floor(pos.x)), LONG(floor(pos.y)) };
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