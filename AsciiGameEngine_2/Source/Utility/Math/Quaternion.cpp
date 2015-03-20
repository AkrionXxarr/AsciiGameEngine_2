/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "Utility\Math\Vector3f.hpp"
#include "Utility\Math\Vector4f.hpp"
#include "Utility\Math\Matrix4f.hpp"
#include "Utility\Math\Quaternion.hpp"


namespace Math
{
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

    // From Ken Shoemake's "Quaternion Calculus and Fast Animation" article
    Quaternion::Quaternion(Matrix4f& rot)
    {
        float trace = rot.m[0][0] + rot.m[1][1] + rot.m[2][2];

        if (trace > 0)
        {
            float s = 0.5f / sqrt(trace + 1.0f);
            w = 0.25f / s;
            x = (rot.m[1][2] - rot.m[2][1]) * s;
            y = (rot.m[2][0] - rot.m[0][2]) * s;
            z = (rot.m[0][1] - rot.m[1][0]) * s;
        }
        else
        {
            if ((rot.m[0][0] > rot.m[1][1]) && (rot.m[0][0] > rot.m[2][2]))
            {
                float s = 2.0f * sqrt(1.0f + rot.m[0][0] - rot.m[1][1] - rot.m[2][2]);
                w = (rot.m[1][2] - rot.m[2][1]) / s;
                x = 0.25f * s;
                y = (rot.m[1][0] + rot.m[0][1]) / s;
                z = (rot.m[2][0] + rot.m[0][2]) / s;
            }
            else if (rot.m[1][1] > rot.m[2][2])
            {
                float s = 2.0f * sqrt(1.0f + rot.m[1][1] - rot.m[0][0] - rot.m[2][2]);
                w = (rot.m[2][0] - rot.m[0][2]) / s;
                x = (rot.m[1][0] + rot.m[0][1]) / s;
                y = 0.25f * s;
                z = (rot.m[2][1] + rot.m[1][2]) / s;
            }
            else
            {
                float s = 2.0f * sqrt(1.0f + rot.m[2][2] - rot.m[0][0] - rot.m[1][1]);
                w = (rot.m[0][1] - rot.m[1][0]) / s;
                x = (rot.m[2][0] + rot.m[0][2]) / s;
                y = (rot.m[1][2] + rot.m[2][1]) / s;
                z = 0.25f * s;
            }
        }

        *this = Normalized();
    }

    Quaternion::Quaternion(const Quaternion& other)
    {
        x = other.x; y = other.y; z = other.z; w = other.w;
    }


    /////////////////////////////////
    // Quaternion operations
    //

    float Quaternion::Length()
    {
        return sqrt(x * x + y * y + z * z + w * w);
    }

    Quaternion Quaternion::Normalized()
    {
        float l = Length();
        return Quaternion(x / l, y / l, z / l, w / l);
    }

    Quaternion Quaternion::Conjugate()
    {
        return Quaternion(-x, -y, -z, w);
    }

    float Quaternion::Dot(Quaternion& q)
    {
        return (x * q.x) + (y * q.y) + (z * q.z) + (w * q.w);
    }


    ///////////////////
    // Operators
    //

    Quaternion Quaternion::operator* (const Quaternion& q) const
    {
        float i = x * q.w + w * q.x + y * q.z - z * q.y;
        float j = y * q.w + w * q.y + z * q.x - x * q.z;
        float k = z * q.w + w * q.z + x * q.y - y * q.x;
        float h = w * q.w - x * q.x - y * q.y - z * q.z;

        return Quaternion(i, j, k, h);
    }

    Quaternion Quaternion::operator* (const Vector3f& v) const
    {
        float i = w * v.x + y * v.z + z * v.y;
        float j = w * v.y + z * v.x - x * v.z;
        float k = w * v.z + x * v.y - y * v.x;
        float h = -x * v.x - y * v.y - z * v.z;

        return Quaternion(i, j, k, h);
    }
}; // Namespace Math