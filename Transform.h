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
}