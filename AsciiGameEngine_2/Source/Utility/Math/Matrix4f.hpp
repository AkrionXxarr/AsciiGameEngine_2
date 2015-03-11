/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

class Vector3f;
class Vector4f;

//////////////////////
// 4 by 4 float-based matrix
//
class Matrix4f
{
public:
    /* Construct & Destruct */
    Matrix4f();
    Matrix4f(
        float xx, float xy, float xz, float xw,
        float yx, float yy, float yz, float yw,
        float zx, float zy, float zz, float zw,
        float wx, float wy, float wz, float ww);
    Matrix4f(const Matrix4f& m);

    ~Matrix4f();

    /* Matrix operations */

    /* Accessors */
    void Set(
        float xx, float xy, float xz, float xw,
        float yx, float yy, float yz, float yw,
        float zx, float zy, float zz, float zw,
        float wx, float wy, float wz, float ww);

public:
    /* Operators */
    void operator= (const Matrix4f& other);

    Vector3f operator* (const Vector3f& v) const;
    Vector4f operator* (const Vector4f& v) const;

    Matrix4f operator* (const Matrix4f& other) const;

public:
    /* Variables */
    std::vector<std::vector<float>> m;

    const static Matrix4f identity;
    const static Matrix4f zero;
};