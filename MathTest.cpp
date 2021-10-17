#include <catch.hpp>
#include "Math.h"

using namespace render;

TEST_CASE("misc", "[math]")
{
    REQUIRE(AlmostZero(0));
    REQUIRE_FALSE(AlmostZero(0.1f));

    REQUIRE(Clamp(2.3f, 0.f, 2.f) == 2.f);
    REQUIRE(Clamp(-3.f, 0.f, 2.f) == 0.f);
}

TEST_CASE("vector2", "[math]")
{
    REQUIRE(Vector2{ 1,2 } == Vector2{ 1,2 });
    REQUIRE(Vector2{ 1,1 } != Vector2{ 1,2 });

    REQUIRE(Vector2{ 2,3 } [0] == 2);
    REQUIRE(Vector2{ 2,3 } [1] == 3);

    REQUIRE(Vector2{ 4,-3 } + Vector2{ 6,6 } == Vector2{ 10,3 });
    REQUIRE(Vector2{ 2,-7 } - Vector2{ 1,1 } == Vector2{ 1,-8 });
    REQUIRE(Vector2{ 3,1 } *Vector2{ 2,3 } == Vector2{ 6,3 });
    REQUIRE(Vector2{ 6,3 } / Vector2{ 2,3 } == Vector2{ 3,1 });

    REQUIRE(Vector2{ 1,3 } *2 == Vector2{ 2,6 });
    REQUIRE(2 * Vector2{ 1,3 } == Vector2{ 2,6 });
    REQUIRE(Vector2{ 2,6 } / 2 == Vector2{ 1,3 });

    REQUIRE(Vector2{ 0,1 }.Cross(Vector2{ 1,0 }) == -1);
    REQUIRE(Vector2{ 1,0 }.Cross(Vector2{ 1,0 }) == 0);
    REQUIRE(Vector2{ 1,0 }.Cross(Vector2{ 0,1 }) == 1);

    REQUIRE(Vector2{ 0,2 }.Dot(Vector2{ 0,3 }) == 6);
    REQUIRE(Vector2{ 1,0 }.Dot(Vector2{ 0,1 }) == 0);
    REQUIRE(Vector2{ 3,7 }.Dot(Vector2{ 2,4 }) == 34);
}

TEST_CASE("vector3", "[math]")
{
    REQUIRE(Vector3{ 1,2,3 } == Vector3{ 1,2,3 });
    REQUIRE(Vector3{ 1,2,4 } != Vector3{ 1,2,5 });

    REQUIRE(Vector3{ 1,2,3 } [0] == 1);
    REQUIRE(Vector3{ 1,2,3 } [1] == 2);
    REQUIRE(Vector3{ 1,2,3 } [2] == 3);

    REQUIRE(Vector3{ 1,1,1 } + Vector3{ 2,2,3 } == Vector3{ 3,3,4 });
    REQUIRE(Vector3{ 3,-2,10.6f } - Vector3{ 1,1,1 } == Vector3{ 2,-3,9.6f });
    REQUIRE(Vector3{ 3,-2,10.6f } *Vector3{ 3,4,2 } == Vector3{ 9,-8,21.2f });
    REQUIRE(Vector3{ 12,12,12 } / Vector3{ 3,4,2 } == Vector3{ 4,3,6 });

    REQUIRE(Vector3{ 1,2,3 } *3 == Vector3{ 3,6,9 });
    REQUIRE(3 * Vector3{ 1,2,3 } == Vector3{ 3,6,9 });
    REQUIRE(Vector3{ 3,6,9 } / 3 == Vector3{ 1,2,3 });

    REQUIRE(Vector3{ 0,0,1 }.Cross(Vector3{ 0,0,1 }) == Vector3{ 0,0,0 });
    REQUIRE(Vector3{ 0,0,1 }.Cross(Vector3{ 1,0,0 }) == Vector3{ 0,1,0 });
    REQUIRE(Vector3{ 0,1,0 }.Cross(Vector3{ 0,0,1 }) == Vector3{ 1,0,0 });

    REQUIRE(Vector3{ 1,0,0 }.Dot(Vector3{ 1,0,0 }) == 1);
    REQUIRE(Vector3{ 0,0,3 }.Dot(Vector3{ 1,0,0 }) == 0);
    REQUIRE(Vector3{ 1,2,3 }.Dot(Vector3{ 1,2,3 }) == 14);
}

TEST_CASE("vector4", "[math]")
{
    REQUIRE(Vector4{ 1,2,3,4 } == Vector4{ 1,2,3,4 });
    REQUIRE(Vector4{ 2,2,3,4 } != Vector4{ 1,2,3,4 });

    REQUIRE(Vector4{ 2,3,4,5 } [0] == 2);
    REQUIRE(Vector4{ 2,3,4,5 } [1] == 3);
    REQUIRE(Vector4{ 2,3,4,5 } [2] == 4);
    REQUIRE(Vector4{ 2,3,4,5 } [3] == 5);

    REQUIRE(Vector4{ 1,1,1,8 } + Vector4{ 2,2,3,1 } == Vector4{ 3,3,4,9 });
    REQUIRE(Vector4{ 3,-2,10.6f,5 } - Vector4{ 1,1,1,1 } == Vector4{ 2,-3,9.6f,4 });
    REQUIRE(Vector4{ 3,-2,10.6f,5 } *Vector4{ 3,4,2,3 } == Vector4{ 9,-8,21.2f,15 });
    REQUIRE(Vector4{ 12,12,12,12 } / Vector4{ 3,4,2,1 } == Vector4{ 4,3,6,12 });

    REQUIRE(Vector4{ 1,2,3,4 } *3 == Vector4{ 3,6,9,12 });
    REQUIRE(3 * Vector4{ 1,2,3,4 } == Vector4{ 3,6,9,12 });
    REQUIRE(Vector4{ 3,6,9,12 } / 3 == Vector4{ 1,2,3,4 });

    REQUIRE(Vector4{ 1,0,0,0 }.Dot(Vector4{ 1,0,0,0 }) == 1);
    REQUIRE(Vector4{ 0,0,3,0 }.Dot(Vector4{ 1,0,0,0 }) == 0);
    REQUIRE(Vector4{ 1,2,3,4 }.Dot(Vector4{ 1,2,3,4 }) == 30);
}

TEST_CASE("matrix4x4 comparison", "[math]")
{
    REQUIRE(
        Matrix44
        {
            1,2,3,4,
            5,6,7,8,
            9,8,7,6,
            5,4,3,2
        }
        ==
        Matrix44
        {
            1,2,3,4,
            5,6,7,8,
            9,8,7,6,
            5,4,3,2
        });

    REQUIRE(
        Matrix44
        {
            1,2,3,4,
            5,6,7,8,
            9,8,7,6,
            5,4,3,2
        }
        !=
        Matrix44
        {
            2,2,3,4,
            5,6,7,8,
            9,8,7,6,
            5,4,3,2
        });
}

TEST_CASE("- matrix4x4", "[math]")
{
    REQUIRE(
        -Matrix44
        {
            1,2,3,4,
            5,6,7,8,
            9,8,7,6,
            5,4,3,2
        }
        ==
        Matrix44
        {
            -1,-2,-3,-4,
            -5,-6,-7,-8,
            -9,-8,-7,-6,
            -5,-4,-3,-2
        });
}

TEST_CASE("matrix4x4 +- matrix4x4", "[math]")
{
    REQUIRE(
        Matrix44
        {
            1,2,3,4,
            5,6,7,8,
            9,8,7,6,
            5,4,3,2
        }
        +
        Matrix44
        {
            1,2,3,4,
            5,6,7,8,
            9,8,7,6,
            5,4,3,2
        }
        ==
        Matrix44
        {
            2,4,6,8,
            10,12,14,16,
            18,16,14,12,
            10,8,6,4
        });

    REQUIRE(
        Matrix44
        {
            2,4,6,8,
            10,12,14,16,
            18,16,14,12,
            10,8,6,4
        }
        -
        Matrix44
        {
            1,2,3,4,
            5,6,7,8,
            9,8,7,6,
            5,4,3,2
        }
        ==
        Matrix44
        {
            1,2,3,4,
            5,6,7,8,
            9,8,7,6,
            5,4,3,2
        });
}

TEST_CASE("matrix4x4 */ scalar", "[math]")
{
    REQUIRE(
        Matrix44
        {
            1,2,3,4,
            5,6,7,8,
            9,8,7,6,
            5,4,3,2
        }
        *2
        ==
        Matrix44
        {
            2,4,6,8,
            10,12,14,16,
            18,16,14,12,
            10,8,6,4
        });

    REQUIRE(
        2 *
        Matrix44
        {
            1,2,3,4,
            5,6,7,8,
            9,8,7,6,
            5,4,3,2
        }
        ==
        Matrix44
        {
            2,4,6,8,
            10,12,14,16,
            18,16,14,12,
            10,8,6,4
        });

    REQUIRE(
        Matrix44
        {
            2,4,6,8,
            10,12,14,16,
            18,16,14,12,
            10,8,6,4
        } / 2
        ==
        Matrix44
        {
            1,2,3,4,
            5,6,7,8,
            9,8,7,6,
            5,4,3,2
        });
}

TEST_CASE("matrix4x4 * matrix4x4", "[math]")
{
    REQUIRE(
        Matrix44
        {
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 8, 7, 6,
            5, 4, 3, 2
        }*
        Matrix44
        {
            1,2,3,4,
            5,6,7,8,
            9,8,7,6,
            5,4,3,2
        }
        ==
        Matrix44
        {
            58,54,50,46,
            138,134,130,126,
            142,146,150,154,
            62,66,70,74
        }
    );
}