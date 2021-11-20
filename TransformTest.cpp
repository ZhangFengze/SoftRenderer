#include <numbers>
#include <catch.hpp>
#include "Transform.h"

using namespace render;

TEST_CASE("translate", "[transform]")
{
    REQUIRE(Translate(Vector3{ 1,2,3 }) * Vector4 { 1, 2, 3, 1 } == Vector4{ 2, 4, 6, 1 });
}

TEST_CASE("scale", "[transform]")
{
    REQUIRE(Scale(Vector3{ 1,2,3 }) * Vector4 { 1, 2, 3, 1 } == Vector4{ 1, 4, 9, 1 });
}

TEST_CASE("rotate", "[transform]")
{
    REQUIRE(
        AlmostEqual(
            Rotate(Vector3{ 0,1,0 }, std::numbers::pi * 0.5f) * Vector4 { 0, 0, 1, 1 },
            Vector4{ 1, 0, 0, 1 }
        )
    );
}

TEST_CASE("lookat", "[transform]")
{
    REQUIRE(
        AlmostEqual(
            LookAt(Vector3{ 0,10,20 }, Vector3{ 0,0,-1 }, Vector3{ 0,1,0 }) * Vector4 { 1, 0, 0, 1 },
            Vector4{ -1,-10, 20, 1 }
        )
    );
}