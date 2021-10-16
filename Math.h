#pragma once
#include <functional>

namespace render
{
    template<int N>
    struct Vector
    {
        float data[N];
        float& operator[](std::size_t idx) { return data[idx]; }
        float operator[](std::size_t idx) const { return data[idx]; }
        bool operator==(const Vector<N>&) const = default;
    };

    template<int N, typename BinaryOperation>
    Vector<N> ElementwiseOP(const Vector<N>& left, const Vector<N>& right, BinaryOperation op)
    {
        Vector<N> result;
        for (int i = 0;i < N;++i)
            result[i] = op(left[i], right[i]);
        return result;
    }

    template<int N>
    Vector<N> operator+(const Vector<N>& left, const Vector<N>& right)
    {
        return ElementwiseOP(left, right, std::plus{});
    }

    template<int N>
    Vector<N> operator-(const Vector<N>& left, const Vector<N>& right)
    {
        return ElementwiseOP(left, right, std::minus{});
    }

    template<int N>
    Vector<N> operator*(const Vector<N>& left, const Vector<N>& right)
    {
        return ElementwiseOP(left, right, std::multiplies{});
    }

    template<int N>
    Vector<N> operator/(const Vector<N>& left, const Vector<N>& right)
    {
        return ElementwiseOP(left, right, std::divides{});
    }

    using Vector3 = Vector<3>;
}