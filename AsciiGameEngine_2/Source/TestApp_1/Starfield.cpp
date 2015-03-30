/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/
#include <random>

#include "Starfield.hpp"

// !!! Pack these includes into ConsoleObject.hpp !!! //
#include "Akropolix\render\Windows Console\ConsoleRenderContext.hpp"
#include "Akropolix\input\Windows Console\ConsoleInputExt.hpp"

using namespace aki::render::wincon;

std::default_random_engine generator;
std::uniform_real_distribution<float> distribution(0.0, 1.0);

Starfield::Starfield(unsigned int width, unsigned int height, unsigned int starCount, float spread, float speed, CHAR_INFO& ci)
{
    stars = new aki::math::Vector3f[starCount];
    this->width = width;
    this->height = height;
    this->starCount = starCount;
    this->spread = spread;
    this->speed = speed;
    this->ci = ci;

    for (int i = 0; i < starCount; i++)
        InitializeStar(i);
}

Starfield::~Starfield()
{
    if (stars)
        delete[] stars;
}

void Starfield::Update(float deltaTime)
{
    for (int i = 0; i < starCount; i++)
    {
        stars[i].z -= deltaTime * speed;

        if (stars[i].z <= 0)
            InitializeStar(i);
    }
}

void Starfield::Draw(aki::render::I::IRenderContext& renderContext)
{
    ConsoleRenderContext& crc = (ConsoleRenderContext&)renderContext;

    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;
    POINT p;

    for (int i = 0; i < starCount; i++)
    {
        p.x = int((stars[i].x / stars[i].z) * halfWidth + halfWidth);
        p.y = int((stars[i].y / stars[i].z) * halfHeight + halfHeight);

        if (p.x < 0 || p.x >= width || p.y < 0 || p.y >= height)
        {
            InitializeStar(i);
        }
        else
        {
            crc.DrawPoint(p, ci);
        }
    }
}

void Starfield::InitializeStar(int i)
{
    if (stars)
    {
        stars[i].x = 2 * (distribution(generator) - 0.5f) * spread;
        stars[i].y = 2 * (distribution(generator) - 0.5f) * spread;
        stars[i].z = (distribution(generator) - 0.00001f) * spread;
    }
}