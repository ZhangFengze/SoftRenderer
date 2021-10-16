#pragma once
#include <limits>
#include <functional>

namespace render
{
    bool AlmostZero(float f)
    {
        return std::abs(f) < std::numeric_limits<float>::epsilon();
    }

    template<int N>
    struct Vector;

    template<>
    struct Vector<3>
    {
        union
        {
            float data[3];
            struct { float x, y, z; };
            struct { float r, g, b; };
        };

        Vector<3>& operator*=(float f)
        {
            for (float& e : data)
                e *= f;
            return *this;
        }

        Vector<3>& operator/=(float f)
        {
            assert(!AlmostZero(f));
            for (float& e : data)
                e /= f;
            return *this;
        }

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

    template<int N>
    bool operator==(const Vector<N>& left, const Vector<N>& right)
    {
        for (int i = 0;i < N;++i)
            if (left[i] != right[i])
                return false;
        return true;
    }

    template<int N>
    bool operator!=(const Vector<N>& left, const Vector<N>& right)
    {
        return !(left == right);
    }

    template<int N, typename BinaryOperation>
    Vector<N> Elementwise(const Vector<N>& left, const Vector<N>& right, BinaryOperation op)
    {
        Vector<N> result;
        for (int i = 0;i < N;++i)
            result[i] = op(left[i], right[i]);
        return result;
    }

    template<int N>
    Vector<N> operator+(const Vector<N>& left, const Vector<N>& right)
    {
        return Elementwise(left, right, std::plus{});
    }

    template<int N>
    Vector<N> operator-(const Vector<N>& left, const Vector<N>& right)
    {
        return Elementwise(left, right, std::minus{});
    }

    template<int N>
    Vector<N> operator*(const Vector<N>& left, const Vector<N>& right)
    {
        return Elementwise(left, right, std::multiplies{});
    }

    template<int N>
    Vector<N> operator/(const Vector<N>& left, const Vector<N>& right)
    {
        return Elementwise(left, right, std::divides{});
    }

    template<int N>
    Vector<N> operator*(Vector<N> v, float f)
    {
        v *= f;
        return v;
    }

    template<int N>
    Vector<N> operator/(Vector<N> v, float f)
    {
        v /= f;
        return v;
    }

    using Vector3 = Vector<3>;
}