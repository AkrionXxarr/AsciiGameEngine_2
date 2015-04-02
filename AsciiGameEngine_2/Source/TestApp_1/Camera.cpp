/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/
#include "Camera.hpp"

// !!! Pack these includes into ConsoleObject.hpp !!! //
#include "Akropolix\render\Windows Console\ConsoleRenderContext.hpp"
#include "Akropolix\input\Windows Console\ConsoleInputExt.hpp"
#include "Akropolix\Utility\Math\Vector2f.hpp"
#include "Akropolix\Utility\Math\Vector3f.hpp"

using namespace aki::render::wincon;
using namespace aki::input::wincon;
using namespace aki::math;

#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

void Intersect(Vector2f v1, Vector2f v2, Vector2f v3, Vector2f v4, Vector2f& ret)
{
    float x1 = v1.x, x2 = v2.x, x3 = v3.x, x4 = v4.x;
    float y1 = v1.y, y2 = v2.y, y3 = v3.y, y4 = v4.y;

    ret.x = (((x1 * y2 - y1 * x2)*(x3 - x4)) - ((x1 - x2)*(x3 * y4 - y3 * x4))) /
            (((x1 - x2) * (y3 - y4)) - ((y1 - y2) * (x3 - x4)));

    ret.y = (((x1 * y2 - y1 * x2)*(y3 - y4)) - ((y1 - y2)*(x3 * y4 - y3 * x4))) /
            (((x1 - x2) * (y3 - y4)) - ((y1 - y2) * (x3 - x4)));

    //ret.y = ((v1.x * v2.y) - (v1.y * v2.x)) 

    /*
    ret.x = v1.Cross(v2);
    ret.y = v3.Cross(v4);
    float det = (v1 - v2).Cross(v3 - v4);
    ret.x = Vector2f(ret.x, v1.x - v2.x).Cross(Vector2f(ret.y, v3.x - v4.x)) / det;
    ret.y = Vector2f(ret.x, v1.y - v2.y).Cross(Vector2f(ret.y, v3.y - v4.y)) / det;
    */
}

Camera::Camera(Vector2f pos, Vector2f dir, float speed, Vector2f wallA, Vector2f wallB)
{
    this->pos = pos;
    this->dir = dir.Normalized();
    this->speed = speed;
    this->angle = 3.14159265359f / 2.0f;
    this->wallA = wallA;
    this->wallB = wallB;
}

Camera::~Camera()
{
}

void Camera::Update(float deltaTime)
{
    if (tRight)
    {
        angle += 2 * deltaTime;
        //dir = dir.Rotate(10 * speed * deltaTime);
    }
    if (tLeft)
    {
        angle -= 2 * deltaTime;
        //dir = dir.Rotate(-10 * speed * deltaTime);
    }
    if (sRight)
    {
        pos.x -= std::cos(angle + (3.14159265359f / 2.0f)) * deltaTime * speed;
        pos.y -= std::sin(angle + (3.14159265359f / 2.0f)) * deltaTime * speed;
    }
    if (sLeft)
    {
        pos.x += std::cos(angle + (3.14159265359f / 2.0f)) * deltaTime * speed;
        pos.y += std::sin(angle + (3.14159265359f / 2.0f)) * deltaTime * speed;
    }
    if (forward)
    {
        //pos = pos + (dir * deltaTime * speed);
        pos.x -= std::cos(angle) * deltaTime * speed;
        pos.y -= std::sin(angle) * deltaTime * speed;
    }
    if (backward)
    {
        //pos = pos + (-dir * deltaTime * speed);
        pos.x += std::cos(angle) * deltaTime * speed;
        pos.y += std::sin(angle) * deltaTime * speed;
    }
}

void Camera::Draw(aki::render::I::IRenderContext& renderContext)
{
    ConsoleRenderContext& crc = (ConsoleRenderContext&)renderContext;

    Vector3f t1, t2;

    float screenDist = -1;
    Vector2f screenLeft(-5, screenDist);
    Vector2f screenRight(5, screenDist);
    Vector2f viewLeft = Vector2f(screenLeft.x, screenLeft.y).Normalized();
    Vector2f viewRight = Vector2f(screenRight.x, screenRight.y).Normalized();

    t1.x = wallA.x - pos.x;
    t1.y = wallA.y - pos.y;
    t2.x = wallB.x - pos.x;
    t2.y = wallB.y - pos.y;

    t1.z = t1.x * std::cos(angle) + t1.y * std::sin(angle);
    t2.z = t2.x * std::cos(angle) + t2.y * std::sin(angle);

    t1.x = t1.x * std::sin(angle) - t1.y * std::cos(angle);
    t2.x = t2.x * std::sin(angle) - t2.y * std::cos(angle);


    CHAR_INFO eyePoint, eyeView, playerLine, wallLine, wall1, wall2, view;
    POINT eyePos, eyeDir;
    Vector2f v = (Vector2f(80, 45) + (Vector2f(0, -1) * 5));//(pos + (dir * 5));

    eyePoint.Attributes = FOREGROUND_RED;
    eyePoint.Char.UnicodeChar = 'O';

    eyeView.Attributes = FOREGROUND_INTENSITY;
    eyeView.Char.UnicodeChar = 0x07;

    playerLine.Attributes = FOREGROUND_RED;
    playerLine.Char.UnicodeChar = '-';

    wallLine.Attributes = FOREGROUND_INTENSITY;
    wallLine.Char.UnicodeChar = '-';

    wall1.Attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    wall1.Char.UnicodeChar = '#';

    wall2.Attributes = FOREGROUND_INTENSITY;
    wall2.Char.UnicodeChar = 0xFE;

    view.Attributes = FOREGROUND_BLUE;
    view.Char.UnicodeChar = '=';

    eyePos.x = 80;
    eyePos.y = 45;

    eyeDir.x = int(v.x);
    eyeDir.y = int(v.y);

    crc.DrawLine({ t1.x + eyePos.x, t1.z + eyePos.y }, { t1.x + eyePos.x - 200, t1.z + eyePos.y }, wallLine);
    crc.DrawLine({ t2.x + eyePos.x, t2.z + eyePos.y }, { t2.x + eyePos.x + 200, t2.z + eyePos.y }, wallLine);
    crc.DrawLine({ t1.x + eyePos.x, t1.z + eyePos.y }, { t2.x + eyePos.x, t2.z + eyePos.y }, wall2);

    crc.DrawLine(eyePos, eyeDir, eyeView);
    crc.DrawPoint(eyePos, eyePoint);

    POINT p1 = { eyePos.x + screenLeft.x, eyePos.y + screenLeft.y };
    POINT p2 = { eyePos.x + screenRight.x, eyePos.y + screenRight.y };
    {
        Vector2f v1 = (Vector2f(p1.x, p1.y) * viewLeft) * 50;
        Vector2f v2 = (Vector2f(p2.x, p2.y) * viewRight) * 50;

        crc.DrawLine(p1, p2, view); // Screen
        //crc.DrawLine(p1, { v1.x, v1.y }, view);
        //crc.DrawLine(p2, { v2.x, v2.y }, view);
    }

    crc.DrawLine(p2, { p2.x + 200, p2.y }, playerLine);
    crc.DrawLine(p1, { p1.x - 200, p1.y }, playerLine);

    // Draw if at least one point is in front of the screen
    if (t1.z < screenDist || t2.z < screenDist)
    {
        bool drawSideA = true;
        bool drawSideB = true;

        if (t1.z >= screenDist || t2.z >= screenDist)
        {
            Vector2f iPoint; // The point where a--b intersects c--d
            Vector2f iA(t1.x, t1.z); // First wall point
            Vector2f iB(t2.x, t2.z); // Second wall point
            Vector2f iC(-1, screenDist); // First screen clip point
            Vector2f iD(1, screenDist); // Second screen clip point

            Intersect(iA, iB, iC, iD, iPoint);

            if (t1.z >= screenDist)
            {
                t1.x = iPoint.x;
                t1.z = screenDist;
                drawSideA = false;
            }
            else if (t2.z >= screenDist)
            {
                t2.x = iPoint.x;
                t2.z = screenDist;
                drawSideB = false;
            }
        }

        /*
        Vector2f i1, i2;
        
        Intersect(
            Vector2f(t1.x, t1.z),
            Vector2f(t2.x, t2.z),
            Vector2f(-0.0001, 0.0001),
            Vector2f(-20, 0.0001),
            i1
            );
        
        Intersect(
            Vector2f(t1.x, t1.z),
            Vector2f(t2.x, t2.z),
            Vector2f(0.0001, 0.0001),
            Vector2f(20, 0.0001),
            i2
            );
            

        if (t1.z >= 0)
        {
            if (i1.y < 0)
            {
                t1.x = i1.x;
                t1.z = i1.y;
            }
            else
            {
                t1.x = i2.x;
                t1.z = i2.y;
            }
        }
        if (t2.z >= 0)
        {
            if (i1.y < 0)
            {
                t2.x = i1.x;
                t2.z = i1.y;
            }
            else
            {
                t2.x = i2.x;
                t2.z = i2.y;
            }
        }
        */

        float x1 = -t1.x * 16 / t1.z;
        float y1a = -50.0f / t1.z;
        float y1b = 50.0f / t1.z;
        float x2 = -t2.x * 16 / t2.z;
        float y2a = -50.0f / t2.z;
        float y2b = 50.0f / t2.z;

        crc.DrawLine({ x1 + eyePos.x, y1a + eyePos.y }, { x2 + eyePos.x, y2a + eyePos.y }, wall1); // top
        crc.DrawLine({ x1 + eyePos.x, y1b + eyePos.y }, { x2 + eyePos.x, y2b + eyePos.y }, wall1); // bottom
        if (drawSideA)
            crc.DrawLine({ x1 + eyePos.x, y1a + eyePos.y }, { x1 + eyePos.x, y1b + eyePos.y }, wall1); // left
        if (drawSideB)
            crc.DrawLine({ x2 + eyePos.x, y2a + eyePos.y }, { x2 + eyePos.x, y2b + eyePos.y }, wall1); // right
    }
}

void Camera::Input(aki::input::wincon::ConsoleInputExt& input)
{
    tRight = input.GetKeyDown(KEYBOARD::E);
    tLeft = input.GetKeyDown(KEYBOARD::Q);
    sRight = input.GetKeyDown(KEYBOARD::D);
    sLeft = input.GetKeyDown(KEYBOARD::A);
    forward = input.GetKeyDown(KEYBOARD::W);
    backward = input.GetKeyDown(KEYBOARD::S);
}