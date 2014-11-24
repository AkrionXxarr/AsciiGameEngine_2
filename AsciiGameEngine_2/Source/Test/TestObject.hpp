#pragma once

#include "Core\Object\Object.hpp"

class TestObject : public Object
{
public:
    TestObject(int depth, unsigned short color, float xFactor, float yFactor)
    { 
        this->depth = depth;
        this->color = color;
        this->xFactor = xFactor;
        this->yFactor = yFactor;
        buffer = new CHAR_INFO[15 * 10];

        for (int y = 0; y < 10; y++)
        {
            for (int x = 0; x < 15; x++)
            {
                int index = (y * 15) + x;

                if (y == 0 || y == 9 || x == 0 || x == 14)
                    buffer[index].Char.UnicodeChar = '#';
                else
                    buffer[index].Char.UnicodeChar = '.';

                buffer[index].Attributes = color;       
            }
        }
    }
    virtual ~TestObject() 
    { 
        if (buffer != nullptr)
            delete[] buffer;
    }

    void Update(float deltaTime);
    void Draw(Renderer* renderer);

private:
    CHAR_INFO* buffer;
    unsigned short color;
    float xFactor, yFactor;
};