#pragma once
#include <limits>
#include <functional>

namespace render
{
    inline bool AlmostZero(float f)
    {
        return std::abs(f) < std::numeric_limits<float>::epsilon();
    }

    inline bool AlmostEqual(float left, float right)
    {
        return AlmostZero(left - right);
    }

    template<typename T>
    T Clamp(T v, T min, T max)
    {
        return std::max(min, std::min(v, max));
    }

    template<size_t N>
    struct Vector;

    using Vector2 = Vector<2>;
    using Vector3 = Vector<3>;
    using Vector4 = Vector<4>;

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
    bool AlmostEqual(const Vector<N>& left, const Vector<N>& right)
    {
        for (size_t i = 0;i < N;++i)
            if (!AlmostEqual(left.data[i], right.data[i]))
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
    Vector<N> operator*(float f, Vector<N> v)
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

    template<size_t N>
    float Dot(const Vector<N>& left, const Vector<N>& right)
    {
        float sum = 0.f;
        for (int i = 0;i < N;++i)
            sum += left[i] * right[i];
        return sum;
    }

    template<size_t N>
    std::ostream& operator << (std::ostream& os, const Vector<N>& v)
    {
        os << "{";
        for (size_t i = 0;i < N;++i)
            os << ((i == 0) ? "" : ",") << v[i];
        os << "}";
        return os;
    }

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
        float Dot(const Vector2& other) const { return render::Dot(*this, other); }

        float Cross(const Vector2& other) const
        {
            return x * other.y - y * other.x;
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
        float Dot(const Vector3& other) const { return render::Dot(*this, other); }

        Vector<3> Cross(const Vector3& other) const
        {
            return { y * other.z - z * other.y, z * other.x - x * other.z,x * other.y - y * other.x };
        }
    };

    template<>
    struct Vector<4>
    {
        union
        {
            float data[4];
            struct { float x, y, z, w; };
            struct { float r, g, b, a; };
        };

        float& operator[](std::size_t idx) { return data[idx]; }
        float operator[](std::size_t idx) const { return data[idx]; }
        float Dot(const Vector4& other) const { return render::Dot(*this, other); }
    };

    template<size_t N>
    struct Matrix
    {
        float data[N][N];

        Vector<N> Row(size_t row) const
        {
            Vector<N> result;
            for (size_t col = 0;col < N;++col)
                result[col] = data[row][col];
            return result;
        }

        Vector<N> Col(size_t col) const
        {
            Vector<N> result;
            for (size_t row = 0;row < N;++row)
                result[row] = data[row][col];
            return result;
        }

        static Matrix<N> Identity()
        {
            Matrix<N> m;
            for (size_t row = 0;row < N;++row)
                for (size_t col = 0;col < N;++col)
                    m.data[row][col] = (row == col ? 1 : 0);
            return m;
        }
    };

    using Matrix44 = Matrix<4>;
    using Matrix33 = Matrix<3>;
    using Matrix22 = Matrix<3>;

    template<size_t N>
    bool operator== (const Matrix<N>& left, const Matrix<N>& right)
    {
        for (size_t row = 0;row < N;++row)
            for (size_t col = 0;col < N;++col)
                if (left.data[row][col] != right.data[row][col])
                    return false;
        return true;
    }

    template<size_t N>
    bool operator!= (const Matrix<N>& left, const Matrix<N>& right)
    {
        return !(left == right);
    }

    template<size_t N>
    Matrix<N> operator- (const Matrix<N>& m)
    {
        Matrix<N> result;
        for (size_t row = 0;row < N;++row)
            for (size_t col = 0;col < N;++col)
                result.data[row][col] = -m.data[row][col];
        return result;
    }

    template<size_t N>
    Matrix<N> operator+ (const Matrix<N>& left, const Matrix<N>& right)
    {
        Matrix<N> result;
        for (size_t row = 0;row < N;++row)
            for (size_t col = 0;col < N;++col)
                result.data[row][col] = left.data[row][col] + right.data[row][col];
        return result;
    }

    template<size_t N>
    Matrix<N> operator- (const Matrix<N>& left, const Matrix<N>& right)
    {
        return left + (-right);
    }

    template<size_t N>
    Matrix<N> operator* (const Matrix<N>& m, float f)
    {
        Matrix<N> result;
        for (size_t row = 0;row < N;++row)
            for (size_t col = 0;col < N;++col)
                result.data[row][col] = m.data[row][col] * f;
        return result;
    }

    template<size_t N>
    Matrix<N> operator* (float f, const Matrix<N>& m)
    {
        return m * f;
    }

    template<size_t N>
    Matrix<N> operator/ (const Matrix<N>& m, float f)
    {
        assert(!AlmostZero(f));
        return m * (1.f / f);
    }

    template<size_t N>
    Matrix<N> operator* (const Matrix<N>& left, const Matrix<N>& right)
    {
        Matrix<N> result;
        for (size_t row = 0;row < N;++row)
            for (size_t col = 0;col < N;++col)
                result.data[row][col] = left.Row(row).Dot(right.Col(col));
        return result;
    }

    template<size_t N>
    Vector<N> operator* (const Matrix<N>& m, const Vector<N>& v)
    {
        Vector<N> result;
        for (size_t row = 0;row < N;++row)
            result[row] = m.Row(row).Dot(v);
        return result;
    }
}