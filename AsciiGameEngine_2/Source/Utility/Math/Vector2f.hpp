/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

///////////////////////////////////////////////////
// 2 Dimensional float-based vector
//
class Vector2f
{
public:
    /* Construct & Destruct */
    Vector2f();
    Vector2f(float x, float y);
    Vector2f(const Vector2f& v);

    ~Vector2f() { }

    /* Vector operations */
    float Length();
    Vector2f Normalized();

    float Dot();
    float Cross();

    Vector2f Rotate(float angle);
    Vector2f Lerp(const Vector2f& dest, float factor);

    /* Getters */
    float GetMax() { return fmax(x, y); }
    float GetMin() { return fmin(x, y); }
    Vector2f GetAbs() { return Vector2f(fabs(x), fabs(y)); }

    /* Swizzlers */
    Vector2f YX() { return Vector2f(y, x); }

public:
    /* Operators */
    void operator= (const Vector2f& v) { x = v.x; y = v.y; }

    bool operator== (const Vector2f& v) { return (x == v.x) && (y == v.y); }

    Vector2f operator - (const Vector2f& v) { return Vector2f(x - v.x, y - v.y); }
    Vector2f operator + (const Vector2f& v) { return Vector2f(x + v.x, y + v.y); }

    Vector2f operator * (const Vector2f& v) { return Vector2f(x * v.x, y * v.y); }
    Vector2f operator / (const Vector2f& v) { return Vector2f(x / v.x, y / v.y); }

    Vector2f operator * (float f) { return Vector2f(x * f, y * f); }
    Vector2f operator / (float f) { return Vector2f(x / f, y / f); }

public:
    /* Variables */
    float x, y;
};