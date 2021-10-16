#include <catch.hpp>
#include "Math.h"

using namespace render;

TEST_CASE("test", "[math]") {
    REQUIRE(Vector3{1,2,3}==Vector3{1,2,3});
    REQUIRE(Vector3{1,2,4}!=Vector3{1,2,5});

    REQUIRE(Vector3{ 1,2,3 } [0] == 1);
    REQUIRE(Vector3{ 1,2,3 } [1] == 2);
    REQUIRE(Vector3{ 1,2,3 } [2] == 3);

    REQUIRE(Vector3{ 1,1,1 } + Vector3{ 2,2,3 } == Vector3{ 3,3,4 });
    REQUIRE(Vector3{ 3,-2,10.6f } - Vector3{ 1,1,1 } == Vector3{ 2,-3,9.6f });
    REQUIRE(Vector3{ 3,-2,10.6f } *Vector3{ 3,4,2 } == Vector3{ 9,-8,21.2f });
    REQUIRE(Vector3{ 12,12,12 } / Vector3{ 3,4,2 } == Vector3{ 4,3,6 });

    REQUIRE(Vector3{ 0,0,1 }.Cross(Vector3{ 1,0,0 }) == Vector3{ 0,1,0 });
    REQUIRE(Vector3{ 0,1,0 }.Cross(Vector3{ 0,0,1 }) == Vector3{ 1,0,0 });

    REQUIRE(Vector3{ 1,2,3 }.Dot(Vector3{ 1,2,3 }) == 14);
}