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
}