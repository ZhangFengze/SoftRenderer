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