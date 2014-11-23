#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

class Vector2f
{
public:
    Vector2f()
    {
        this->x = 0; this->y = 0;
    }
    Vector2f(float x, float y)
    {
        this->x = x; this->y = y;
    }
    Vector2f(const Vector2f& other)
    {
        this->x = other.x; this->y = other.y;
    }

    ~Vector2f() { }

    float Length() { return sqrt(x * x + y * y); }

    float Dot(Vector2f v) { return x * v.x + y * v.y; }
    float Cross(Vector2f v) { return (x * v.y) - (y * v.x); }

    Vector2f Rotate(float angle)
    {
        float rad = angle * float(M_PI / 180.0);
        float cosine = cos(rad);
        float sine = sin(rad);

        return Vector2f((x * cosine - y * sine), (x * sine + y * cosine));
    }

    Vector2f Lerp(Vector2f dest, float factor)
    {
        return (((dest - *this) * factor) + *this);
    }

    Vector2f Normalized()
    {
        float length = Length();

        return Vector2f(x / length, y / length);
    }

    float Max()
    {
        return fmax(x, y);
    }

    float Min()
    {
        return fmin(x, y);
    }

    Vector2f Abs()
    {
        return Vector2f(fabs(x), fabs(y));
    }

    Vector2f AsInt()
    {
        return Vector2f(float(int(x)), float(int(y)));
    }

    void operator = (const Vector2f& v) { this->x = v.x; this->y = v.y; }

    bool operator == (Vector2f& v) { return (x == v.x) && (y == v.y); }
    Vector2f operator - () { return Vector2f(-x, -y); }

    Vector2f operator - (Vector2f& v) { return Vector2f(x - v.x, y - v.y); }
    Vector2f operator + (Vector2f& v) { return Vector2f(x + v.x, y + v.y); }

    Vector2f operator * (Vector2f& v) { return Vector2f(x * v.x, y * v.y); }
    Vector2f operator / (Vector2f& v) { return Vector2f(x / v.x, y / v.y); }

    Vector2f operator * (float f) { return Vector2f(x * f, y * f); }
    Vector2f operator / (float f) { return Vector2f(x / f, y / f); }

public:
    float x, y;
};