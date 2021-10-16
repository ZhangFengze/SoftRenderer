#pragma once
#include <functional>

namespace render
{
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

        float& operator[](std::size_t idx) { return data[idx]; }
        float operator[](std::size_t idx) const { return data[idx]; }

        Vector<3> Cross(const Vector<3>& other) const
        {
            return { y * other.z - z * other.y, z * other.x - x * other.z,x * other.y - y * other.x };
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

    using Vector3 = Vector<3>;
}