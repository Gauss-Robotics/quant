#pragma once
#include <quant/framed_units.h>
#include <quant/framed_units/position/FramedPosition.h>
#include <quant/geometry/Circa.h>

#include <doctest/doctest.h>

#include <iostream>

using namespace quant;  // NOLINT

TEST_SUITE("testing framed position domain")
{
    TEST_CASE("testing framed positions")
    {
        SUBCASE("construction")
        {
            quant::FramedPosition const f1{Position::millimeters({.x = 1, .y = 2, .z = 3}),
                                           {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            quant::FramedPosition const f2{};
            quant::FramedPosition const f3{f1};

            CHECK(f1.get_name() == "TCP");
            CHECK(f1.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(f1.get_framed_object() == Circa(Position::millimeters({.x = 1, .y = 2, .z = 3})));

            CHECK(f2.get_name() == "::");
            CHECK(f2.get_base_frame() == "::");
            CHECK(f2.get_framed_object() == Circa(Position::zero()));

            CHECK(f3.get_name() == "TCP");
            CHECK(f3.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(f3.get_framed_object() == Circa(Position::millimeters({.x = 1, .y = 2, .z = 3})));
        }

        SUBCASE("subtraction")
        {
            quant::FramedPosition const f1{Position::millimeters({.x = 1, .y = 2, .z = 3}),
                                           {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            quant::FramedPosition const f2{Position::millimeters({.x = 4, .y = 5, .z = 6}),
                                           {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};

            auto const diff = f2 - f1;

            CHECK(diff.get_name() == "TCP");
            CHECK(diff.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(diff.get_framed_object() ==
                  Circa(LinearDisplacement::millimeters({.x = 3, .y = 3, .z = 3})));
        }

        SUBCASE("base change - wrong frames")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            quant::FramedPosition const f1{Position::millimeters({.x = 1, .y = 2, .z = 3}),
                                           {.name = name, .base_frame = from_frame}};

            framed_geometry::BaseChange const bc{
                .from_frame = "something else",
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0}))};
            std::string const exception_message =
                "Frame mismatch: something else vs " + std::string(from_frame);
            CHECK_THROWS_WITH(bc * f1, exception_message.c_str());
        }

        SUBCASE("base change - linear")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            quant::FramedPosition const f1{Position::millimeters({.x = 1, .y = 2, .z = 3}),
                                           {.name = name, .base_frame = from_frame}};

            framed_geometry::BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0}))};

            auto f2 = bc * f1;

            CHECK(f2.get_name() == name);
            CHECK(f2.get_base_frame() == to_frame);
            CHECK(f2.get_framed_object() == Circa(Position::millimeters({.x = 4, .y = 4, .z = 4})));
        }

        SUBCASE("base change - rotation")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            quant::FramedPosition const f1{Position::millimeters({.x = 1, .y = 2, .z = 3}),
                                           {.name = name, .base_frame = from_frame}};

            framed_geometry::BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 0, .y = 0, .z = 0}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};

            auto f2 = bc * f1;

            CHECK(f2.get_name() == name);
            CHECK(f2.get_base_frame() == to_frame);
            CHECK(f2.get_framed_object() ==
                  Circa(Position::millimeters({.x = 1, .y = -3, .z = 2})));
        }

        SUBCASE("base change - transform")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            quant::FramedPosition const f1{Position::millimeters({.x = 1, .y = 2, .z = 3}),
                                           {.name = name, .base_frame = from_frame}};

            framed_geometry::BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};

            auto f2 = bc * f1;

            CHECK(f2.get_name() == name);
            CHECK(f2.get_base_frame() == to_frame);
            CHECK(f2.get_framed_object() ==
                  Circa(Position::millimeters({.x = 4, .y = -1, .z = 3})));
        }
    }
}
