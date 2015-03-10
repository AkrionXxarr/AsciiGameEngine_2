/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

class Vector2f;
class Vector3f;
class Quaternion;

//////////////////////////////////////////
// 4 Dimensional float-based vector
//
class Vector4f
{
public:
    /* Construct & Destruct */
    Vector4f();
    Vector4f(float x, float y, float z, float w);
    Vector4f(const Vector3f& v, float w);
    Vector4f(const Vector4f& other);

    ~Vector4f() { }

    /* Vector operations */
    float Length();
    Vector4f Normalized();

    Vector4f Lerp(Vector4f& dest, float factor);

    /* Getters */
    float GetMax() { return fmax(x, fmax(y, fmax(z, w))); }
    float GetMin() { return fmin(x, fmin(y, fmin(z, w))); }
    Vector4f GetAbs() { return Vector4f(fabs(x), fabs(y), fabs(z), fabs(w)); }

    /* Swizzlers */
    Vector2f XY(); // (a,b,-,-)
    Vector2f YX(); // (b,a,-,-)

    Vector2f XZ(); // (a,-,b,-)
    Vector2f ZX(); // (b,-,a,-)

    Vector2f XW(); // (a,-,-,b)
    Vector2f WX(); // (b,-,-,a)

    Vector2f YZ(); // (-,a,b,-)
    Vector2f ZY(); // (-,b,a,-)

    Vector2f YW(); // (-,a,-,b)
    Vector2f WY(); // (-,b,-,a)

    Vector2f ZW(); // (-,-,a,b)
    Vector2f WZ(); // (-,-,b,a)


    Vector3f XYZ(); // (a,b,c,-)
    Vector3f XZY(); // (a,c,b,-)
    Vector3f YXZ(); // (b,a,c,-)
    Vector3f YZX(); // (b,c,a,-)
    Vector3f ZXY(); // (c,a,b,-)
    Vector3f ZYX(); // (c,b,a,-)

    Vector3f XYW(); // (a,b,-,c)
    Vector3f XWY(); // (a,c,-,b)
    Vector3f YXW(); // (b,a,-,c)
    Vector3f YWX(); // (b,c,-,a)
    Vector3f WXY(); // (c,a,-,b)
    Vector3f WYX(); // (c,b,-,a)

    Vector3f XZW(); // (a,-,b,c)
    Vector3f XWZ(); // (a,-,c,b)
    Vector3f ZXW(); // (b,-,a,c)
    Vector3f ZWX(); // (b,-,c,a)
    Vector3f WXZ(); // (c,-,a,b)
    Vector3f WZX(); // (c,-,b,a)

    Vector3f YZW(); // (-,a,b,c)
    Vector3f YWZ(); // (-,a,c,b)
    Vector3f ZYW(); // (-,b,a,c)
    Vector3f ZWY(); // (-,b,c,a)
    Vector3f WYZ(); // (-,c,a,b)
    Vector3f WZY(); // (-,c,b,a)

public:
    /* Operators */
    bool operator== (const Vector4f& v) { return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w); }
    Vector4f operator- () const { return Vector4f(-x, -y, -z, -w); }

    Vector4f operator- (const Vector4f& v) const { return Vector4f(x - v.x, y - v.y, z - v.z, w - v.w); }
    Vector4f operator+ (const Vector4f& v) const { return Vector4f(x + v.x, y + v.y, z + v.z, w + v.w); }

    Vector4f operator* (const Vector4f& v) const { return Vector4f(x * v.x, y * v.y, z * v.z, w * v.w); }
    Vector4f operator/ (const Vector4f& v) const { return Vector4f(x / v.x, y / v.y, z / v.z, w / v.w); }

    Vector4f operator* (float f) const { return Vector4f(x * f, y * f, z * f, w * f); }
    Vector4f operator/ (float f) const { return Vector4f(x / f, y / f, z / f, w / f); }

public:
    /* Variables */
    float x, y, z, w;
};