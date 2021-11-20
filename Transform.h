#pragma once
#include "Math.h"

namespace render
{
    inline Matrix44 Translate(const Vector3& t)
    {
        return
        {
            1,0,0,t.x,
            0,1,0,t.y,
            0,0,1,t.z,
            0,0,0,1
        };
    }

    inline Matrix44 Scale(const Vector3& t)
    {
        return
        {
            t.x,0,0,0,
            0,t.y,0,0,
            0,0,t.z,0,
            0,0,0,1
        };
    }

    inline Matrix44 Rotate(const Vector3& axis, float radian)
    {
        float sin = std::sin(radian);
        float cos = std::cos(radian);
        return
        {
            axis.x * axis.x * (1 - cos) + cos, axis.x * axis.y * (1 - cos) - axis.z * sin, axis.x * axis.z * (1 - cos) + axis.y * sin,0,
            axis.x * axis.y * (1 - cos) + axis.z * sin,axis.y * axis.y * (1 - cos) + cos,axis.y * axis.z * (1 - cos) - axis.x * sin,0,
            axis.x * axis.z * (1 - cos) - axis.y * sin,axis.y * axis.z * (1 - cos) + axis.x * sin,axis.z * axis.z * (1 - cos) + cos,0,
            0,0,0,1
        };
    }

    inline Matrix44 LookAt(const Vector3& center, const Vector3& forward, const Vector3& up = Vector3{ 0, 1, 0 })
    {
        Vector3 w = forward.Normalized();
        Vector3 u = up.Cross(w).Normalized();
        Vector3 v = w.Cross(u).Normalized();

        return
            Matrix44
        {
            u.x, v.x, w.x, 0,
            u.y, v.y, w.y, 0,
            u.z, v.z, w.z, 0,
            0,   0,   0, 1,
        }*Translate(-center);
    }
}