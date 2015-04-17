/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include <math.h>

#include "AsciiGame_1\Display\AG1_Camera.hpp"
#include "AsciiGame_1\Display\AG1_Viewport.hpp"
#include "AsciiGame_1\World\AG1_World.hpp"
#include "AsciiGame_1\Object\AG1_Objects.hpp"

Camera::Camera(Viewport* const viewport, World* const world) : viewport(viewport), world(world)
{
}

Camera::~Camera()
{
}

void Camera::Clear()
{
    CHAR_INFO ci;

    ci.Attributes = 0;
    ci.Char.UnicodeChar = ' ';

    for (int i = 0; i < viewport->viewBufferSize.X * viewport->viewBufferSize.Y; i++)
    {
        viewport->viewBuffer[i] = { ci, -100 };
    }
}

void Camera::Draw(POINT objPos, CHAR_INFO& ci, int depth)
{
    POINT t;
    POINT p = player->GetPosAsPoint();

    p.x -= (viewport->viewBufferSize.X / 2);
    p.y -= (viewport->viewBufferSize.Y / 2);

    t.x = (objPos.x - p.x);
    t.y = (objPos.y - p.y);

    if (t.x < 0 || t.y < 0 || t.x >= viewport->viewBufferSize.X || t.y >= viewport->viewBufferSize.Y)
        return;

    unsigned int index = (t.y * viewport->viewBufferSize.X) + t.x;

    if (viewport->viewBuffer[index].depth <= depth)
    {
        viewport->viewBuffer[index].ci = ci;
        viewport->viewBuffer[index].depth = depth;
    }
}