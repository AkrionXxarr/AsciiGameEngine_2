/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "Utility\Math\Vector2f.hpp"
#include "Utility\Math\Vector3f.hpp"
#include "Utility\Math\Vector4f.hpp"


namespace Math
{
    ///////////////////////////////
    // Constructors
    //

    Vector4f::Vector4f()
    {
        x = 0; y = 0; z = 0; w = 0;
    }

    Vector4f::Vector4f(float x, float y, float z, float w)
    {
        this->x = x; this->y = y; this->z = z; this->w = w;
    }

    Vector4f::Vector4f(const Vector3f& v, float w)
    {
        x = v.x; y = v.y; z = v.z; this->w = w;
    }

    Vector4f::Vector4f(const Vector4f& v)
    {
        x = v.x; y = v.y; z = v.z; w = v.w;
    }


    ////////////////////////////
    // Variable operations
    //

    float Vector4f::Length()
    {
        return sqrt(x * x + y * y + z * z + w * w);
    }

    Vector4f Vector4f::Normalized()
    {
        float l = Length();
        return Vector4f(x / l, y / l, z / l, w / l);
    }

    Vector4f Vector4f::Lerp(Vector4f& dest, float factor)
    {
        return (((dest - *this) * factor) + *this);
    }


    ////////////////////////////
    // Swizzlers
    //

    Vector2f Vector4f::XY() { return Vector2f(x, y); }
    Vector2f Vector4f::YX() { return Vector2f(y, x); }

    Vector2f Vector4f::XZ() { return Vector2f(x, z); }
    Vector2f Vector4f::ZX() { return Vector2f(z, x); }

    Vector2f Vector4f::XW() { return Vector2f(x, w); }
    Vector2f Vector4f::WX() { return Vector2f(w, x); }

    Vector2f Vector4f::YZ() { return Vector2f(y, z); }
    Vector2f Vector4f::ZY() { return Vector2f(z, y); }

    Vector2f Vector4f::YW() { return Vector2f(y, w); }
    Vector2f Vector4f::WY() { return Vector2f(w, y); }

    Vector2f Vector4f::ZW() { return Vector2f(z, w); }
    Vector2f Vector4f::WZ() { return Vector2f(w, x); }


    Vector3f Vector4f::XYZ() { return Vector3f(x, y, z); }
    Vector3f Vector4f::XZY() { return Vector3f(x, z, y); }
    Vector3f Vector4f::YXZ() { return Vector3f(y, x, z); }
    Vector3f Vector4f::YZX() { return Vector3f(y, z, x); }
    Vector3f Vector4f::ZXY() { return Vector3f(z, x, y); }
    Vector3f Vector4f::ZYX() { return Vector3f(z, y, x); }

    Vector3f Vector4f::XYW() { return Vector3f(x, y, w); }
    Vector3f Vector4f::XWY() { return Vector3f(x, w, y); }
    Vector3f Vector4f::YXW() { return Vector3f(y, x, w); }
    Vector3f Vector4f::YWX() { return Vector3f(y, w, x); }
    Vector3f Vector4f::WXY() { return Vector3f(w, x, y); }
    Vector3f Vector4f::WYX() { return Vector3f(w, y, x); }

    Vector3f Vector4f::XZW() { return Vector3f(x, z, w); }
    Vector3f Vector4f::XWZ() { return Vector3f(x, w, z); }
    Vector3f Vector4f::ZXW() { return Vector3f(z, x, w); }
    Vector3f Vector4f::ZWX() { return Vector3f(z, w, x); }
    Vector3f Vector4f::WXZ() { return Vector3f(w, x, z); }
    Vector3f Vector4f::WZX() { return Vector3f(w, z, x); }

    Vector3f Vector4f::YZW() { return Vector3f(y, z, w); }
    Vector3f Vector4f::YWZ() { return Vector3f(y, w, z); }
    Vector3f Vector4f::ZYW() { return Vector3f(z, y, w); }
    Vector3f Vector4f::ZWY() { return Vector3f(z, w, y); }
    Vector3f Vector4f::WYZ() { return Vector3f(w, y, z); }
    Vector3f Vector4f::WZY() { return Vector3f(w, z, y); }


    /////////////////////////
    // Static variables
    //

    const Vector4f Vector4f::zero(0, 0, 0, 0);
}; // Namespace Math