#pragma once
#include "Math.h"

namespace render
{
    struct RenderTarget
    {
        const size_t width, height;
        std::vector<Vector3> buffer;

        Vector3& rgb(unsigned int x, unsigned int y) { return buffer[x + y * width]; }
        const Vector3& rgb(unsigned int x, unsigned int y) const { return buffer[x + y * width]; }

        static RenderTarget Create(size_t width, size_t height, const Vector3& color = { 0,0,0 })
        {
            RenderTarget r{ width,height };
            r.buffer.resize(width * height, color);
            return r;
        }
    };
}