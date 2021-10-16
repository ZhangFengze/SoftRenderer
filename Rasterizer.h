#pragma once
#include "Math.h"

namespace render
{
    template<typename Func>
    void Line0(const Vector2& a, const Vector2& b, Func func)
    {
        float xSpan = b.x - a.x;
        float ySpan = b.y - a.y;
        float length = std::abs(std::max(std::abs(xSpan), std::abs(ySpan)));
        if (AlmostZero(length))
            return;

        float xStep = xSpan / length;
        float yStep = ySpan / length;
        float tStep = 1.f / length;

        float x = a.x;
        float y = a.y;
        float t = 0.f;

        for (float step = 0;step < length;++step)
        {
            func(Vector2{ x,y }, t);
            x += xStep;
            y += yStep;
            t += tStep;
        }
    }

    template<typename Func>
    void TriangleWireframe0(const Vector2& a, const Vector2& b, const Vector2& c, Func func)
    {
        Line0(a, b, [&](auto pos, float t) {func(pos, Vector3{ 1 - t,t,0 });});
        Line0(b, c, [&](auto pos, float t) {func(pos, Vector3{ 0,1 - t,t });});
        Line0(c, a, [&](auto pos, float t) {func(pos, Vector3{ t,0,1 - t });});
    }

    template<typename Func>
    void Triangle0(const Vector2& a, const Vector2& b, const Vector2& c, Func func)
    {
        float xMin = std::min({ a.x,b.x,c.x });
        float xMax = std::max({ a.x,b.x,c.x });
        float yMin = std::min({ a.y,b.y,c.y });
        float yMax = std::max({ a.y,b.y,c.y });

        for (float x = std::floor(xMin) + 0.5f;x < xMax + 0.5;++x)
        {
            for (float y = std::floor(yMin) + 0.5f;y < yMax + 0.5;++y)
            {
                float a_bc = (a - b).Cross(b - c);
                float b_ac = (b - a).Cross(a - c);
                if (AlmostZero(a_bc) || AlmostZero(b_ac))
                    continue;
                Vector2 p{ x,y };
                float barycentricA = (p - b).Cross(b - c) / a_bc;
                if (barycentricA < 0 || barycentricA>1)
                    continue;
                float barycentricB = (p - a).Cross(a - c) / b_ac;
                if (barycentricB < 0 || barycentricB>1)
                    continue;
                float barycentricC = 1 - barycentricA - barycentricB;
                if (barycentricC < 0 || barycentricC>1)
                    continue;
				func({ x,y }, { barycentricA,barycentricB,barycentricC });
            }
        }
    }
}