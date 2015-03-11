#include "Utility\Math\Vector3f.hpp"
#include "Utility\Math\Vector4f.hpp"
#include "Matrix4f.hpp"

////////////////////////////////
// Construct & Destruct
//
Matrix4f::Matrix4f() : m(4, std::vector<float>(4))
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            m[row][col] = 0;
        }
    }
}

Matrix4f::Matrix4f(
    float xx, float xy, float xz, float xw,
    float yx, float yy, float yz, float yw,
    float zx, float zy, float zz, float zw,
    float wx, float wy, float wz, float ww) : m(4, std::vector<float>(4))
{
    m[0][0] = xx; m[0][1] = xy; m[0][2] = xz; m[0][3] = xw;
    m[1][0] = yx; m[1][1] = yy; m[1][2] = yz; m[1][3] = yw;
    m[2][0] = zx; m[2][1] = zy; m[2][2] = zz; m[2][3] = zw;
    m[3][0] = wx; m[3][1] = wy; m[3][2] = wz; m[3][3] = ww;
}

Matrix4f::Matrix4f(const Matrix4f& m)
{
}


////////////////////////////
// Accessors
//
float& Matrix4f::M(int row, int col)
{
}

void Matrix4f::Set(
    float xx, float xy, float xz, float xw,
    float yx, float yy, float yz, float yw,
    float zx, float zy, float zz, float zw,
    float wx, float wy, float wz, float ww)
{
    m[0][0] = xx; m[0][1] = xy; m[0][2] = xz; m[0][3] = xw;
    m[1][0] = yx; m[1][1] = yy; m[1][2] = yz; m[1][3] = yw;
    m[2][0] = zx; m[2][1] = zy; m[2][2] = zz; m[2][3] = zw;
    m[3][0] = wx; m[3][1] = wy; m[3][2] = wz; m[3][3] = ww;
}

////////////////////////
// Operators
//
void Matrix4f::operator= (const Matrix4f& other)
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            m[row][col] = other.m[row][col];
        }
    }
}

Vector3f Matrix4f::operator* (const Vector3f& v) const
{
    return Vector3f(
        m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3],
        m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3],
        m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3]
        );
}

Vector4f Matrix4f::operator* (const Vector4f& v) const
{
    return Vector4f(
        m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
        m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
        m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
        m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w
        );
}

Matrix4f Matrix4f::operator* (const Matrix4f& other) const
{
    Matrix4f res;

    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            res.m[row][col] =
                    m[row][0] * other.m[0][col] +
                    m[row][1] * other.m[1][col] +
                    m[row][2] * other.m[2][col] +
                    m[row][3] * other.m[3][col];
        }
    }

    return res;
}