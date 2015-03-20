/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "Utility\Math\Vector2f.hpp"


namespace Math
{
    /////////////////////////////
    // Constructors
    //

    Vector2f::Vector2f()
    {
        x = 0; y = 0;
    }

    Vector2f::Vector2f(float x, float y)
    {
        this->x = x; this->y = y;
    }

    Vector2f::Vector2f(const Vector2f& v)
    {
        x = v.x; y = v.y;
    }


    ////////////////////////////
    // Vector operations
    //

    float Vector2f::Length()
    {
        return sqrt(x * x + y * y);
    }

    Vector2f Vector2f::Normalized()
    {
        float l = Length();
        return Vector2f(x / l, y / l);
    }

    float Vector2f::Dot(Vector2f& v)
    {
        return (x * v.x) + (y * v.y);
    }

    float Vector2f::Cross(Vector2f& v)
    {
        return (x * v.y) - (y * v.x);
    }

    Vector2f Vector2f::Rotate(float angle)
    {
        float rad = angle * float(M_PI / 180.0f);
        float cosine = cos(rad);
        float sine = sin(rad);

        return Vector2f((x * cosine - y * sine), (x * sine + y * cosine));
    }

    Vector2f Vector2f::Lerp(Vector2f& dest, float factor)
    {
        return (((dest - *this) * factor) + *this);
    }


    ///////////////////
    // Swizzlers
    //

    Vector2f Vector2f::YX() { return Vector2f(y, x); }


    ////////////////////////
    // Static variables
    //

    const Vector2f Vector2f::zero(0, 0);
}; // Namespace Math