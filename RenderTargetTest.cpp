#include <catch.hpp>
#include "RenderTarget.h"

using namespace render;

TEST_CASE("[RenderTarget]misc", "[RenderTarget]")
{
    RenderTarget r = RenderTarget::Create(800, 600);
    REQUIRE(r.width == 800);
    REQUIRE(r.height == 600);

    r.rgb(100, 200) = { 1,1,1 };
    REQUIRE(r.rgb(100, 200) == Vector3{ 1, 1, 1 });

    r.rgb(0, 0) = { 1,1,1 };
    r.rgb(799, 599) = { 1,1,1 };

    // illegal
    // r.rgb(800, 600) = { 1,1,1 };
    // r.rgb(-1, -1) = { 1,1,1 };
}