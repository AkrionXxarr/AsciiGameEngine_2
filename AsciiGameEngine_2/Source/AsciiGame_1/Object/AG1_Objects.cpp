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
                objectManager->AddObject(new Bullet(curPoint, { curPoint.x + t.x, curPoint.y + t.y }, 10.0f, camera, true, objectManager));
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


//////////////////////////
// Bullet
//
Bullet::Bullet(
    POINT start,
    POINT end,
    float speed,
    Camera* camera,
    bool visible,
    ConsoleObjectManager* objectManager) : GameObject(camera, "bullet"), objectManager(objectManager)
{
    this->start = start;
    this->end = end;
    this->speed = speed;

    depth = 10;
    
    pos = Vector2f(float(start.x), float(start.y));
    dir = (Vector2f(float(end.x), float(end.y)) - pos);

    dist = dir.Length();
    dir = dir.Normalized();

    distTraveled = 0;

    curPos = GetPosAsPoint();

    ci.Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
    ci.Char.UnicodeChar = 0xFE;
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

        camera->Draw(curPos, ci, depth);
    }
}

POINT Bullet::GetPosAsPoint()
{
    return{ LONG(floor(pos.x + 0.5f)), LONG(floor(pos.y + 0.5f)) };
}