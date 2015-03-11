/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

class Vector3f;
class Vector4f;
class Matrix4f;

class Quaternion
{
public:
    /* Construct & Destruct */
    Quaternion();
    Quaternion(float x, float y, float z, float w);
    Quaternion(Vector4f& v);
    Quaternion(Vector3f& axis, float angle);
    Quaternion(Matrix4f& rot);
    Quaternion(const Quaternion& other);

    ~Quaternion() { }

    /* Quaternion operations */
    float Length();
    Quaternion Normalized();
    Quaternion Conjugate();

    float Dot(Quaternion& q);

    Quaternion NLerp(Quaternion& dest, float lerpFactor, bool shortest);

    Matrix4f ToRotationMatrix();

public:
    /* Operators */
    bool operator== (Quaternion& q) { return (x == q.x) && (y == q.y) && (z == q.z) && (w == q.w); }

    Quaternion operator- (const Quaternion& q) const { return Quaternion(x - q.x, y - q.y, z - q.z, w - q.w); }
    Quaternion operator+ (const Quaternion& q) const { return Quaternion(x + q.x, y + q.y, z + q.z, w + q.w); }

    Quaternion operator* (float f) const { return Quaternion(x * f, y * f, z * f, w * f); }
    Quaternion operator/ (float f) const { return Quaternion(x / f, y / f, z / f, w / f); }

    Quaternion operator* (const Quaternion& q) const;
    Quaternion operator* (const Vector3f& v) const;

public:
    float x, y, z, w;
};