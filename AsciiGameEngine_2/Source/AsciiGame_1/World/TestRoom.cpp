/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include <random>

#include "Akropolix\Display Device\Windows Console\ConsoleDefines.hpp"

#include "AsciiGame_1\World\TestRoom.hpp"
#include "AsciiGame_1\Object\AG1_Objects.hpp"

TestRoom1::TestRoom1(Camera* const camera, World* world) : Room(camera), world(world)
{
    CHAR_INFO ci;
    CHAR_INFO ciAlt;

    ci.Attributes = f_lightGray;
    ci.Char.UnicodeChar = 0xB2;

    int x = 0, y = 0;

    /////////////////////
    // Outer border 
    //
    for (int i = 0; i < 40; i++)
    {
        objects.push_back(new Wall(ci, { x, y }, 1, camera, true));
        x++;
    }

    for (int i = 0; i < 20; i++)
    {
        objects.push_back(new Wall(ci, { x, y }, 1, camera, true));
        y++;
    }

    for (int i = 0; i < 20; i++)
    {
        objects.push_back(new Wall(ci, { x, y }, 1, camera, true));
        x++;
    }

    for (int i = 0; i < 15; i++)
    {
        objects.push_back(new Wall(ci, { x, y }, 1, camera, true));
        y++;
    }

    for (int i = 0; i < 60; i++)
    {
        objects.push_back(new Wall(ci, { x, y }, 1, camera, true));
        x--;
    }

    for (int i = 0; i < 35; i++)
    {
        objects.push_back(new Wall(ci, { x, y }, 1, camera, true));
        y--;
    }


    /////////////////////
    // Floor, main room
    //
    ciAlt.Attributes = f_halfBlue;
    ciAlt.Char.UnicodeChar = '~';
    bool isFloor = true;

    for (int row = 1; row < 35; row++)
    {
        for (int col = 1; col < 40; col++)
        {
            isFloor = true;

            if (row < 8 || col < 8 || row > 27 || col > 32)
            {
                ci.Attributes = f_halfYellow;
                ci.Char.UnicodeChar = 0xB0;
            }
            else
            {
                if (row == 8 && col == 8)
                {
                    // Top left
                    ci.Attributes = f_fullYellow;
                    ci.Char.UnicodeChar= 0xC9;
                }
                else if (row == 8 && col == 32)
                {
                    // Top right
                    ci.Attributes = f_fullYellow;
                    ci.Char.UnicodeChar = 0xBB;
                }
                else if (row == 27 && col == 8)
                {
                    // Bottom left
                    ci.Attributes = f_fullYellow;
                    ci.Char.UnicodeChar = 0xC8;
                }
                else if (row == 27 && col == 32)
                {
                    // Bottom right
                    ci.Attributes = f_fullYellow;
                    ci.Char.UnicodeChar = 0xBC;
                }
                else if (row == 8 || row == 27)
                {
                    // Top & Bottom
                    ci.Attributes = f_fullYellow;
                    ci.Char.UnicodeChar = 0xCD;
                }
                else if (col == 8 || col == 32)
                {
                    // Left & Right
                    ci.Attributes = f_fullYellow;
                    ci.Char.UnicodeChar = 0xBA;
                }
                else
                {
                    isFloor = false;
                    ci.Attributes = f_fullBlue;
                    ci.Char.UnicodeChar = 247;
                }
            }

            if (isFloor)
                objects.push_back(new Floor(ci, { col, row }, 0, camera, true));
            else
                objects.push_back(new Water(ci, ciAlt, { col, row }, 0, camera, true));
        }
    }

    /////////////////////
    // Room divider
    //
    ci.Attributes = f_darkGray;
    ci.Char.UnicodeChar = 0xB2;

    for (int row = 21; row < 35; row++)
    {
        objects.push_back(new Floor(ci, { 40, row }, 0, camera, true));
    }

    /////////////////////
    // Secondary room
    //
    ci.Attributes = f_halfRed;
    ci.Char.UnicodeChar = 0xDB;

    for (int row = 21; row < 35; row++)
    {
        for (int col = 41; col < 60; col++)
        {
            objects.push_back(new Floor(ci, { col, row }, 0, camera, true));
        }
    }

    /////////////////////
    // Portal
    //
    ci.Attributes = f_lightGray;
    ci.Char.UnicodeChar = 0xB2;
    
    objects.push_back(new Wall(ci, { 59, 26 }, 1, camera, true));
    objects.push_back(new Wall(ci, { 59, 29 }, 1, camera, true));
}

TestRoom1::~TestRoom1()
{
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i])
        {
            delete objects[i];
            objects[i] = nullptr;
        }
    }
}

void TestRoom1::AddRightRoom(Room* room)
{
    CHAR_INFO ci;

    ci.Attributes = f_white;
    ci.Char.UnicodeChar = 0x1D;

    objects.push_back(new Portal(ci, { 59, 27 }, { 2, 27 }, 1, camera, true, room, world));
    objects.push_back(new Portal(ci, { 59, 28 }, { 2, 28 }, 1, camera, true, room, world));
}




TestRoom2::TestRoom2(Camera* const camera, World* world) : Room(camera), world(world)
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 50);

    CHAR_INFO ci;

    ci.Attributes = f_lightGray;
    ci.Char.UnicodeChar = 0xB2;

    int x = 0, y = 0;

    /////////////////////
    // Outer border 
    //
    for (int i = 0; i < 50; i++)
    {
        objects.push_back(new Wall(ci, { x, y }, 1, camera, true));
        x++;
    }

    for (int i = 0; i < 50; i++)
    {
        objects.push_back(new Wall(ci, { x, y }, 1, camera, true));
        y++;
    }

    for (int i = 0; i < 50; i++)
    {
        objects.push_back(new Wall(ci, { x, y }, 1, camera, true));
        x--;
    }

    for (int i = 0; i < 50; i++)
    {
        objects.push_back(new Wall(ci, { x, y }, 1, camera, true));
        y--;
    }

    /////////////////////
    // Floor, main room
    //
    ci.Attributes = f_halfGreen;
    ci.Char.UnicodeChar = 0xB0;

    for (int row = 1; row < 50; row++)
    {
        for (int col = 1; col < 50; col++)
        {
            int t = distribution(generator);

            switch (t)
            {
            case 1:
            case 2:
            case 3:
                ci.Attributes = f_halfYellow;
                ci.Char.UnicodeChar = 0xB0;
                break;

            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
                ci.Attributes = f_fullGreen;
                ci.Char.UnicodeChar = 0xB0;
                break;

            default:
                ci.Attributes = f_halfGreen;
                ci.Char.UnicodeChar = 0xB0;
            }

            objects.push_back(new Floor(ci, { col, row }, 0, camera, true));
        }
    }

    /////////////////////
    // Portal
    //
    ci.Attributes = f_lightGray;
    ci.Char.UnicodeChar = 0xB2;

    objects.push_back(new Wall(ci, { 1, 26 }, 1, camera, true));
    objects.push_back(new Wall(ci, { 1, 29 }, 1, camera, true));

    /////////////////////
    // Rain
    //
    CHAR_INFO ciAlt;

    ci.Attributes = f_fullBlue;
    ci.Char.UnicodeChar = 0x07;

    ciAlt.Attributes = f_fullBlue;
    ciAlt.Char.UnicodeChar = 0xB2;

    objects.push_back(new Rain(ci, ciAlt, 0.5f, 0.5f, 30.0f, 1, camera, true, this));
}

TestRoom2::~TestRoom2()
{

}

void TestRoom2::AddLeftRoom(Room* room)
{
    CHAR_INFO ci;

    ci.Attributes = f_white;
    ci.Char.UnicodeChar = 0x1D;

    objects.push_back(new Portal(ci, { 1, 27 }, { 58, 27 }, 1, camera, true, room, world));
    objects.push_back(new Portal(ci, { 1, 28 }, { 58, 28 }, 1, camera, true, room, world));
}