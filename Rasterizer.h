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
        float a_bc = (a - b).Cross(b - c);
        float b_ac = (b - a).Cross(a - c);
        if (AlmostZero(a_bc) || AlmostZero(b_ac))
            return;

        float xMin = std::min({ a.x,b.x,c.x });
        float xMax = std::max({ a.x,b.x,c.x });
        float yMin = std::min({ a.y,b.y,c.y });
        float yMax = std::max({ a.y,b.y,c.y });

        for (float x = std::floor(xMin) + 0.5f;x < xMax + 0.5;++x)
        {
            for (float y = std::floor(yMin) + 0.5f;y < yMax + 0.5;++y)
            {
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
                func(p, { barycentricA,barycentricB,barycentricC });
            }
        }
    }

    struct _Point
    {
        Vector2 pos;
        Vector3 barycentric;
    };

    template<typename Func>
    void _Triangle1(_Point a, _Point b, _Point c, Func func)
    {
        float a_bc = (a.pos - b.pos).Cross(b.pos - c.pos);
        float b_ac = (b.pos - a.pos).Cross(a.pos - c.pos);
        if (AlmostZero(a_bc) || AlmostZero(b_ac))
            return;

        float steps = std::abs(a.pos.y - b.pos.y);
        float y = a.pos.y;
        float x0 = a.pos.x;
        float x1 = a.pos.x;

        float yStep = (b.pos.y - a.pos.y) / steps;
        float x0Step = (b.pos.x - a.pos.x) / steps;
        float x1Step = (c.pos.x - a.pos.x) / std::abs(c.pos.y - a.pos.y);

        for (float step = 0;step < steps;++step)
        {
            for (float x = std::min(x0, x1);x < std::max(x0, x1);++x)
            {
                Vector2 p{ std::floor(x) + 0.5f, std::floor(y) + 0.5f };
                float barycentricA = (p - b.pos).Cross(b.pos - c.pos) / a_bc;
                if (barycentricA < 0 || barycentricA>1)
                    continue;
                float barycentricB = (p - a.pos).Cross(a.pos - c.pos) / b_ac;
                if (barycentricB < 0 || barycentricB>1)
                    continue;
                float barycentricC = 1 - barycentricA - barycentricB;
                if (barycentricC < 0 || barycentricC>1)
                    continue;
                auto ba = barycentricA * a.barycentric + barycentricB * b.barycentric + barycentricC * c.barycentric;
				func(p, ba);
            }

            y += yStep;
            x0 += x0Step;
            x1 += x1Step;
        }
    }

    template<typename Func>
    void Triangle1(Vector2 aRaw, Vector2 bRaw, Vector2 cRaw, Func func)
    {
        _Point points[3]
        {
            {aRaw,{1,0,0}},
            {bRaw,{0,1,0}},
            {cRaw,{0,0,1}},
        };
        std::sort(std::begin(points), std::end(points),
            [](const auto& left, const auto& right) {return left.pos.y < right.pos.y;});

        _Triangle1(points[0], points[1], points[2], func);
        _Triangle1(points[2], points[1], points[0], func);
    }
}