/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

class Vector2f;
class Quaternion;

//////////////////////////////////////////
// 3 Dimensional float-based vector
//
class Vector3f
{
public:
    /* Construct & Destruct */
    Vector3f();
    Vector3f(float x, float y, float z);
    Vector3f(const Vector2f& v, float z);
    Vector3f(const Vector3f& v);

    ~Vector3f() { }

    /* Vector operations */
    float Length();
    Vector3f Normalized();

    float Dot(Vector3f& v);
    Vector3f Cross(Vector3f& v);

    Vector3f Rotate(Vector3f& axis, float angle);
    Vector3f Rotate(Quaternion& rotation);

    Vector3f Lerp(Vector3f& dest, float factor);

    /* Getters */
    float GetMax() { return fmax(x, fmax(y, z)); }
    float GetMin() { return fmin(x, fmin(y, z)); }
    Vector3f GetsAbs() { return Vector3f(fabs(x), fabs(y), fabs(z)); }

    /* Swizzlers */
    Vector2f XY(); // (a,b,-)
    Vector2f YX(); // (b,a,-)

    Vector2f XZ(); // (a,-,b)
    Vector2f ZX(); // (b,-,a)

    Vector2f YZ(); // (-,a,b)
    Vector2f ZY(); // (-,b,a)

    Vector3f XYZ(); // (a,b,c)
    Vector3f XZY(); // (a,c,b)
    Vector3f YXZ(); // (b,a,c)
    Vector3f YZX(); // (b,c,a)
    Vector3f ZXY(); // (c,a,b)
    Vector3f ZYX(); // (c,b,a)

public:
    /* Operators */
    void operator= (const Vector3f& v) { x = v.x; y = v.y; z = v.z; }

    bool operator== (const Vector3f& v) const { return (x == v.x) && (y == v.y) && (z == v.z); }
    Vector3f operator- () const { return Vector3f(-x, -y, -z); }

    Vector3f operator- (const Vector3f& v) const { return Vector3f(x - v.x, y - v.y, z - v.z); }
    Vector3f operator+ (const Vector3f& v) const { return Vector3f(x + v.x, y + v.y, z + v.z); }

    Vector3f operator* (const Vector3f& v) const { return Vector3f(x * v.x, y * v.y, z * v.z); }
    Vector3f operator/ (const Vector3f& v) const { return Vector3f(x / v.x, y / v.y, z / v.z); }

    Vector3f operator* (float f) const { return Vector3f(x * f, y * f, z * f); }
    Vector3f operator/ (float f) const { return Vector3f(x / f, y / f, z / f); }

public:
    /* Variables */
    float x, y, z;

    const static Vector3f zero;
};