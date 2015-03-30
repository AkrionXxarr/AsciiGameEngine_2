/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "Akropolix\Utility\Math\Vector2f.hpp"
#include "Akropolix\Utility\Math\Vector3f.hpp"
#include "Akropolix\Utility\Math\Quaternion.hpp"

namespace aki
{
    namespace math
    {
        /////////////////////////////
        // Constructors
        //

        Vector3f::Vector3f()
        {
            x = 0; y = 0; z = 0;
        }

        Vector3f::Vector3f(float x, float y, float z)
        {
            this->x = x; this->y = y; this->z = z;
        }

        Vector3f::Vector3f(const Vector2f& v, float z)
        {
            x = v.x; y = v.y; this->z = z;
        }

        Vector3f::Vector3f(const Vector3f& v)
        {
            x = v.x; y = v.y; z = v.z;
        }


        ////////////////////////////
        // Vector operations
        //

        float Vector3f::Length()
        {
            return sqrt(x * x + y * y + z * z);
        }

        Vector3f Vector3f::Normalized()
        {
            float l = Length();
            return Vector3f(x / l, y / l, z / l);
        }

        float Vector3f::Dot(Vector3f& v)
        {
            return (x * v.x) + (y * v.y) + (z * v.z);
        }

        Vector3f Vector3f::Cross(Vector3f& v)
        {
            float i = (y * v.z) - (z * v.y);
            float j = (z * v.x) - (x * v.z);
            float k = (x * v.y) - (y * v.x);

            return Vector3f(i, j, k);
        }

        Vector3f Vector3f::Rotate(Vector3f& axis, float angle)
        {
            return Rotate(Quaternion(axis, angle));
        }

        Vector3f Vector3f::Rotate(Quaternion& rotation)
        {
            Quaternion conjugate = rotation.Conjugate();
            Quaternion w = rotation * (*this) * conjugate;

            return Vector3f(w.x, w.y, w.z);
        }

        Vector3f Vector3f::Lerp(Vector3f& dest, float factor)
        {
            return (((dest - *this) * factor) + *this);
        }


        ////////////////////////////
        // Swizzlers
        //

        Vector2f Vector3f::XY() { return Vector2f(x, y); }
        Vector2f Vector3f::YX() { return Vector2f(y, x); }

        Vector2f Vector3f::XZ() { return Vector2f(x, z); }
        Vector2f Vector3f::ZX() { return Vector2f(z, x); }

        Vector2f Vector3f::YZ() { return Vector2f(y, z); }
        Vector2f Vector3f::ZY() { return Vector2f(z, y); }

        Vector3f Vector3f::XYZ() { return Vector3f(x, y, z); }
        Vector3f Vector3f::XZY() { return Vector3f(x, z, y); }
        Vector3f Vector3f::YXZ() { return Vector3f(y, x, z); }
        Vector3f Vector3f::YZX() { return Vector3f(y, z, x); }
        Vector3f Vector3f::ZXY() { return Vector3f(z, x, y); }
        Vector3f Vector3f::ZYX() { return Vector3f(z, y, x); }


        //////////////////////////
        // Static variables
        //

        const Vector3f Vector3f::zero(0, 0, 0);
    }; // Namespace math
};