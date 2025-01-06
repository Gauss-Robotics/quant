#pragma once

#include <quant/units/position.h>

#include <doctest/doctest.h>

using namespace quant;

TEST_SUITE("concrete instantiation using position")
{
    TEST_CASE("geometric objects are copy-assignable")
    {
        Position p1 = Position::millimeters({.x = 1, .y = 2, .z = 3});
        Position p2 = Position::millimeters({.x = 42, .y = 42, .z = 42});

        SUBCASE("states are copy-assignable")
        {
            CHECK(p1 == Position::millimeters({.x = 1, .y = 2, .z = 3}));
            CHECK(p2 == Position::millimeters({.x = 42, .y = 42, .z = 42}));

            p1 = p2;

            CHECK(p1 == Position::millimeters({.x = 42, .y = 42, .z = 42}));
            CHECK(p2 == Position::millimeters({.x = 42, .y = 42, .z = 42}));

            p1 = Position::millimeters({.x = 2});

            CHECK(p1 == Position::millimeters({.x = 2, .y = 0, .z = 0}));
            CHECK(p2 == Position::millimeters({.x = 42, .y = 42, .z = 42}));
        }

        LinearDisplacement ld1{p1};
        LinearDisplacement ld2{p2};

        SUBCASE("differences are copy-assignable")
        {
            CHECK(ld1 == LinearDisplacement::millimeters({.x = 1, .y = 2, .z = 3}));
            CHECK(ld2 == LinearDisplacement::millimeters({.x = 42, .y = 42, .z = 42}));

            ld1 = ld2;

            CHECK(ld1 == LinearDisplacement::millimeters({.x = 42, .y = 42, .z = 42}));
            CHECK(ld2 == LinearDisplacement::millimeters({.x = 42, .y = 42, .z = 42}));

            ld1 = LinearDisplacement::millimeters({.x = 2});

            CHECK(ld1 == LinearDisplacement::millimeters({.x = 2, .y = 0, .z = 0}));
            CHECK(ld2 == LinearDisplacement::millimeters({.x = 42, .y = 42, .z = 42}));
        }
    }
}
