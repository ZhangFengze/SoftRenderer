#pragma once
#include <limits>
#include <functional>

namespace render
{
    bool AlmostZero(float f)
    {
        return std::abs(f) < std::numeric_limits<float>::epsilon();
    }

    template<size_t N>
    struct Vector;

    template<>
    struct Vector<2>
    {
        union
        {
            float data[2];
            struct { float x, y; };
            struct { float u, v; };
        };

        float& operator[](std::size_t idx) { return data[idx]; }
        float operator[](std::size_t idx) const { return data[idx]; }

        float Cross(const Vector<2>& other) const
        {
            return x * other.y - y * other.x;
        }

        float Dot(const Vector<2>& other) const
        {
            return x * other.x + y * other.y;
        }
    };

    template<>
    struct Vector<3>
    {
        union
        {
            float data[3];
            struct { float x, y, z; };
            struct { float r, g, b; };
        };

        float& operator[](std::size_t idx) { return data[idx]; }
        float operator[](std::size_t idx) const { return data[idx]; }

        Vector<3> Cross(const Vector<3>& other) const
        {
            return { y * other.z - z * other.y, z * other.x - x * other.z,x * other.y - y * other.x };
        }

        float Dot(const Vector<3>& other) const
        {
            return x * other.x + y * other.y + z * other.z;
        }
    };

    template<size_t N>
    Vector<N>& operator*=(Vector<N>& v, float f)
    {
        for (float& e : v.data)
            e *= f;
        return v;
    }

    template<size_t N>
    Vector<N>& operator/=(Vector<N>& v, float f)
    {
        assert(!AlmostZero(f));
        return v *= (1.f / f);
    }

    template<size_t N>
    bool operator==(const Vector<N>& left, const Vector<N>& right)
    {
        for (int i = 0;i < N;++i)
            if (left[i] != right[i])
                return false;
        return true;
    }

    template<size_t N>
    bool operator!=(const Vector<N>& left, const Vector<N>& right)
    {
        return !(left == right);
    }

    template<size_t N, typename OP>
    Vector<N> Elementwise(const Vector<N>& left, const Vector<N>& right, OP op)
    {
        Vector<N> result;
        for (int i = 0;i < N;++i)
            result[i] = op(left[i], right[i]);
        return result;
    }

    template<size_t N>
    Vector<N> operator+(const Vector<N>& left, const Vector<N>& right)
    {
        return Elementwise(left, right, std::plus{});
    }

    template<size_t N>
    Vector<N> operator-(const Vector<N>& left, const Vector<N>& right)
    {
        return Elementwise(left, right, std::minus{});
    }

    template<size_t N>
    Vector<N> operator*(const Vector<N>& left, const Vector<N>& right)
    {
        return Elementwise(left, right, std::multiplies{});
    }

    template<size_t N>
    Vector<N> operator/(const Vector<N>& left, const Vector<N>& right)
    {
        return Elementwise(left, right, std::divides{});
    }

    template<size_t N>
    Vector<N> operator*(Vector<N> v, float f)
    {
        v *= f;
        return v;
    }

    template<size_t N>
    Vector<N> operator/(Vector<N> v, float f)
    {
        v /= f;
        return v;
    }

    using Vector2 = Vector<2>;
    using Vector3 = Vector<3>;
}