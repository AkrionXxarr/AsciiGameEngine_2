/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "Utility\Math\Vector3f.hpp"
#include "Utility\Math\Vector4f.hpp"
#include "Utility\Math\Matrix4f.hpp"
#include "Utility\Math\Quaternion.hpp"

///////////////////////////////
// Constructors
//
Quaternion::Quaternion()
{
    x = 0; y = 0; z = 0; w = 0;
}

Quaternion::Quaternion(float x, float y, float z, float w)
{
    this->x = x; this->y = y; this->z = z; this->w = w;
}

Quaternion::Quaternion(Vector4f& v)
{
    x = v.x; y = v.y; z = v.z; w = v.z;
}

Quaternion::Quaternion(Vector3f& axis, float angle)
{
    float sinHalfAngle = sinf(angle / 2.0f);
    float cosHalfAngle = cosf(angle / 2.0f);

    x = axis.x * sinHalfAngle;
    y = axis.y * sinHalfAngle;
    z = axis.z * sinHalfAngle;
    w = cosHalfAngle;
}

Quaternion::Quaternion(Matrix4f& rot)
{

}

Quaternion::Quaternion(const Quaternion& other)
{
    x = other.x; y = other.y; z = other.z; w = other.w;
}