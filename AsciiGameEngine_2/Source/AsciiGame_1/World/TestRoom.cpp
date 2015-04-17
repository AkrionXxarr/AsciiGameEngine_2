/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "Akropolix\Display Device\Windows Console\ConsoleDefines.hpp"

#include "AsciiGame_1\World\TestRoom.hpp"
#include "AsciiGame_1\Object\AG1_Objects.hpp"

TestRoom::TestRoom(Camera* const camera) : Room(camera)
{
    CHAR_INFO ci;

    ci.Attributes = f_lightGray;
    ci.Char.UnicodeChar = 0xB2;

    int x = 0, y = 0;

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

    for (int row = 1; row < 35; row++)
    {
        for (int col = 1; col < 40; col++)
        {
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
                    ci.Attributes = f_fullBlue;
                    ci.Char.UnicodeChar = 247;
                }
            }

            objects.push_back(new Floor(ci, { col, row }, 0, camera, true));
        }
    }

    ci.Attributes = f_darkGray;
    ci.Char.UnicodeChar = 0xB2;

    for (int row = 21; row < 35; row++)
    {
        objects.push_back(new Floor(ci, { 40, row }, 0, camera, true));
    }

    ci.Attributes = f_halfRed;
    ci.Char.UnicodeChar = 0xDB;

    for (int row = 21; row < 35; row++)
    {
        for (int col = 41; col < 60; col++)
        {
            objects.push_back(new Floor(ci, { col, row }, 0, camera, true));
        }
    }
}

TestRoom::~TestRoom()
{

}