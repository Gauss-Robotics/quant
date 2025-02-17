#include <quant/framed_units/acceleration.h>
#include <quant/geometry/Circa.h>
#include <quant/units/acceleration.h>

#include <doctest/doctest.h>

#include <iostream>

using namespace quant;  // NOLINT

TEST_SUITE("testing framed acceleration domain")
{
    TEST_CASE("testing framed linear accelerations")
    {
        SUBCASE("construction")
        {
            FramedLinearAcceleration const a1{
                LinearAcceleration::meters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedLinearAcceleration const a2 = FramedLinearAcceleration::zero({"::", "::"});
            FramedLinearAcceleration const a3{a1};

            CHECK(a1.get_name() == "TCP");
            CHECK(a1.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(a1.get_framed_object() ==
                  Circa(LinearAcceleration::meters_per_second_squared({.x = 1, .y = 2, .z = 3})));

            CHECK(a2.get_name() == "::");
            CHECK(a2.get_base_frame() == "::");
            CHECK(a2.get_framed_object() == Circa(LinearAcceleration::zero()));

            CHECK(a3.get_name() == "TCP");
            CHECK(a3.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(a3.get_framed_object() ==
                  Circa(LinearAcceleration::meters_per_second_squared({.x = 1, .y = 2, .z = 3})));
        }

        SUBCASE("subtraction")
        {
            FramedLinearAcceleration const a1{
                LinearAcceleration::meters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedLinearAcceleration const a2{
                LinearAcceleration::meters_per_second_squared({.x = 4, .y = 5, .z = 6}),
                {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};

            auto const diff = a2 - a1;

            CHECK(diff.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(diff.get_framed_object() ==
                  Circa(LinearAccelerationDifference::meters_per_second_squared(
                      {.x = 3, .y = 3, .z = 3})));
        }

        SUBCASE("base change - translation")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedLinearAcceleration const a1{
                LinearAcceleration::meters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                {.name = name, .base_frame = from_frame}};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0}))};

            auto a2 = bc * a1;

            CHECK(a2.get_name() == name);
            CHECK(a2.get_base_frame() == to_frame);
            CHECK(a2.get_framed_object() ==
                  Circa(LinearAcceleration::meters_per_second_squared({.x = 1, .y = 2, .z = 3})));
        }

        SUBCASE("base change - rotation")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedLinearAcceleration const a1{
                LinearAcceleration::meters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                {.name = name, .base_frame = from_frame}};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 0, .y = 0, .z = 0}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};

            auto a2 = bc * a1;

            CHECK(a2.get_name() == name);
            CHECK(a2.get_base_frame() == to_frame);
            CHECK(a2.get_framed_object() ==
                  Circa(LinearAcceleration::meters_per_second_squared({.x = 1, .y = 3, .z = -2})));
        }

        SUBCASE("base change - transform")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedLinearAcceleration const a1{
                LinearAcceleration::meters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                {.name = name, .base_frame = from_frame}};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};

            auto a2 = bc * a1;

            CHECK(a2.get_name() == name);
            CHECK(a2.get_base_frame() == to_frame);
            CHECK(a2.get_framed_object() ==
                  Circa(LinearAcceleration::meters_per_second_squared({.x = 1, .y = 3, .z = -2})));
        }
    }

    //     TEST_CASE("testing framed linear displacement")
    //     {
    //         SUBCASE("construction")
    //         {
    //             FramedLinearDisplacement const f1{
    //                 LinearDisplacement::millimeters({.x = 1, .y = 2, .z = 3}),
    //                 "ARMAR-6::RobotRoot"};
    //             FramedLinearDisplacement const f2{};
    //             FramedLinearDisplacement const f3{f1};
    //
    //             CHECK(f1.get_base_frame() == "ARMAR-6::RobotRoot");
    //             CHECK(f1.get_framed_object() ==
    //                   Circa(LinearDisplacement::millimeters({.x = 1, .y = 2, .z = 3})));
    //
    //             CHECK(f2.get_base_frame() == "::");
    //             CHECK(f2.get_framed_object() == Circa(LinearDisplacement::zero()));
    //
    //             CHECK(f3.get_base_frame() == "ARMAR-6::RobotRoot");
    //             CHECK(f3.get_framed_object() ==
    //                   Circa(LinearDisplacement::millimeters({.x = 1, .y = 2, .z = 3})));
    //         }
    //
    //         SUBCASE("addition from right to state")
    //         {
    //             FramedPosition const position{Position::millimeters({.x = 1, .y = 2, .z = 3}),
    //                                           {.name = "TCP", .base_frame =
    //                                           "ARMAR-6::RobotRoot"}};
    //             FramedLinearDisplacement const ld{
    //                 LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
    //                 "ARMAR-6::RobotRoot"};
    //             FramedLinearDisplacement const ld_wrong_frame{
    //                 LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
    //                 "ARMAR-6::PlatformBase"};
    //
    //             auto const new_position = position + ld;
    //             CHECK(new_position.get_name() == "TCP");
    //             CHECK(new_position.get_base_frame() == "ARMAR-6::RobotRoot");
    //             CHECK(new_position.get_framed_object() ==
    //                   Circa(Position::millimeters({.x = 4, .y = 4, .z = 4})));
    //
    //             std::string const exception_message =
    //                 "Frame mismatch: ARMAR-6::RobotRoot vs ARMAR-6::PlatformBase";
    //             CHECK_THROWS_WITH(position + ld_wrong_frame, exception_message.c_str());
    //         }
    //
    //         SUBCASE("base change - translation")
    //         {
    //             std::string const from_frame = "ARMAR-6::RobotRoot";
    //             std::string const to_frame = "ARMAR-6::TCP_R";
    //             std::string const name = "TCP";
    //             FramedLinearDisplacement const f1{
    //                 LinearDisplacement::millimeters({.x = 1, .y = 2, .z = 3}), from_frame};
    //
    //             BaseChange const bc{
    //                 .from_frame = from_frame,
    //                 .to_frame = to_frame,
    //                 .transformation = SpatialDisplacement(
    //                     LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
    //                     AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle =
    //                     0}))};
    //             auto new_displacement = bc * f1;
    //
    //             CHECK(new_displacement.get_base_frame() == to_frame);
    //             CHECK(new_displacement.get_framed_object() ==
    //                   Circa(LinearDisplacement::millimeters({.x = 1, .y = 2, .z = 3})));
    //         }
    //
    //         SUBCASE("base change - angular")
    //         {
    //             std::string const from_frame = "ARMAR-6::RobotRoot";
    //             std::string const to_frame = "ARMAR-6::TCP_R";
    //             std::string const name = "TCP";
    //             FramedLinearDisplacement const f1{
    //                 LinearDisplacement::millimeters({.x = 1, .y = 2, .z = 3}), from_frame};
    //
    //             BaseChange const bc{
    //                 .from_frame = from_frame,
    //                 .to_frame = to_frame,
    //                 .transformation = SpatialDisplacement(
    //                     LinearDisplacement::millimeters({.x = 0, .y = 0, .z = 0}),
    //                     AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle =
    //                     90}))};
    //             auto new_displacement = bc * f1;
    //
    //             CHECK(new_displacement.get_base_frame() == to_frame);
    //             CHECK(new_displacement.get_framed_object() ==
    //                   Circa(LinearDisplacement::millimeters({.x = 1, .y = 3, .z = -2})));
    //         }
    //
    //         SUBCASE("base change - transform")
    //         {
    //             std::string const from_frame = "ARMAR-6::RobotRoot";
    //             std::string const to_frame = "ARMAR-6::TCP_R";
    //             std::string const name = "TCP";
    //             FramedLinearDisplacement const f1{
    //                 LinearDisplacement::millimeters({.x = 1, .y = 2, .z = 3}), from_frame};
    //
    //             BaseChange const bc{
    //                 .from_frame = from_frame,
    //                 .to_frame = to_frame,
    //                 .transformation = SpatialDisplacement(
    //                     LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
    //                     AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle =
    //                     90}))};
    //             auto new_displacement = bc * f1;
    //
    //             CHECK(new_displacement.get_base_frame() == to_frame);
    //             CHECK(new_displacement.get_framed_object() ==
    //                   Circa(LinearDisplacement::millimeters({.x = 1, .y = 3, .z = -2})));
    //         }
    //
    //         SUBCASE("base change - wrong frame")
    //         {
    //             std::string const from_frame = "ARMAR-6::RobotRoot";
    //             std::string const to_frame = "ARMAR-6::TCP_R";
    //             std::string const name = "TCP";
    //             FramedLinearDisplacement const f1{
    //                 LinearDisplacement::millimeters({.x = 1, .y = 2, .z = 3}), from_frame};
    //
    //             BaseChange const bc{
    //                 .from_frame = "something else",
    //                 .to_frame = to_frame,
    //                 .transformation = SpatialDisplacement(
    //                     LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
    //                     AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle =
    //                     0}))};
    //
    //             std::string const exception_message =
    //                 "Frame mismatch: something else vs " + std::string(from_frame);
    //             CHECK_THROWS_WITH(bc * f1, exception_message.c_str());
    //         }
    //
    //         SUBCASE("base change - difference of changed states is changed difference")
    //         {
    //             std::string const from_frame = "ARMAR-6::RobotRoot";
    //             std::string const to_frame = "ARMAR-6::TCP_R";
    //             std::string const name = "TCP";
    //             FramedPosition const p1{Position::millimeters({.x = 1, .y = 2, .z = 3}),
    //                                     {.name = name, .base_frame = from_frame}};
    //             FramedPosition const p2{Position::millimeters({.x = 10, .y = 9, .z = 8}),
    //                                     {.name = name, .base_frame = from_frame}};
    //             FramedLinearDisplacement const ld = p2 - p1;
    //
    //             BaseChange const bc{
    //                 .from_frame = from_frame,
    //                 .to_frame = to_frame,
    //                 .transformation = SpatialDisplacement(
    //                     LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
    //                     AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle =
    //                     90}))};
    //
    //             auto const p1_new = bc * p1;
    //             auto const p2_new = bc * p2;
    //             auto const ld_new = p2_new - p1_new;
    //             CHECK(bc * ld == Circa(ld_new));
    //         }
    //     }

    TEST_CASE("testing framed angular accelerations")
    {
        SUBCASE("construction")
        {
            FramedAngularAcceleration const f1{AngularAcceleration::degrees_per_second_squared(
                                                   {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                                               {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedAngularAcceleration const f2 = FramedAngularAcceleration::zero({"::", "::"});
            FramedAngularAcceleration const f3{f1};

            CHECK(f1.get_name() == "TCP");
            CHECK(f1.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(f1.get_framed_object() == Circa(AngularAcceleration::degrees_per_second_squared(
                                                {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})));

            CHECK(f2.get_name() == "::");
            CHECK(f2.get_base_frame() == "::");
            CHECK(f2.get_framed_object() == Circa(AngularAcceleration::zero()));

            CHECK(f3.get_name() == "TCP");
            CHECK(f3.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(f3.get_framed_object() == Circa(AngularAcceleration::degrees_per_second_squared(
                                                {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})));
        }

        SUBCASE("subtraction")
        {
            FramedAngularAcceleration const f1{AngularAcceleration::degrees_per_second_squared(
                                                   {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                                               {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedAngularAcceleration const f2{AngularAcceleration::degrees_per_second_squared(
                                                   {.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}),
                                               {.name = "CoM", .base_frame = "ARMAR-6::RobotRoot"}};

            auto const diff = f2 - f1;

            CHECK(diff.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(diff.get_framed_object() ==
                  Circa(AngularAccelerationDifference::degrees_per_second_squared(
                      {.axis = {.x = -1 / sqrt(2), .y = 1 / sqrt(2), .z = 0},
                       .angle = sqrt(2)*90})));
        }

        SUBCASE("base change - rotation")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedAngularAcceleration const f1{AngularAcceleration::degrees_per_second_squared(
                                                   {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                                               {.name = name, .base_frame = from_frame}};

            BaseChange const bc{.from_frame = from_frame,
                                .to_frame = to_frame,
                                .transformation = SpatialDisplacement(
                                    LinearDisplacement::zero(),
                                    AngularDisplacement::degrees(
                                        {.axis = {.x = 0, .y = 1, .z = 0}, .angle = 270}))};
            auto f2 = bc * f1;

            CHECK(f2.get_name() == name);
            CHECK(f2.get_base_frame() == to_frame);
            CHECK(f2.get_framed_object() == Circa(AngularAcceleration::degrees_per_second_squared(
                                                {.axis = {.x = 0, .y = 0, .z = -1}, .angle = 90})));
        }
    }

    //     TEST_CASE("testing framed angular displacement")
    //     {
    //         SUBCASE("construction")
    //         {
    //             FramedAngularDisplacement const f1{
    //                 AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle =
    //                 90}), "ARMAR-6::RobotRoot"};
    //             FramedAngularDisplacement const f2{};
    //             FramedAngularDisplacement const f3{f1};
    //
    //             CHECK(f1.get_base_frame() == "ARMAR-6::RobotRoot");
    //             CHECK(f1.get_framed_object() == Circa(AngularDisplacement::degrees(
    //                                                 {.axis = {.x = 1, .y = 0, .z = 0}, .angle =
    //                                                 90})));
    //
    //             CHECK(f2.get_base_frame() == "::");
    //             CHECK(f2.get_framed_object() == Circa(AngularDisplacement::zero()));
    //
    //             CHECK(f3.get_base_frame() == "ARMAR-6::RobotRoot");
    //             CHECK(f3.get_framed_object() == Circa(AngularDisplacement::degrees(
    //                                                 {.axis = {.x = 1, .y = 0, .z = 0}, .angle =
    //                                                 90})));
    //         }
    //
    //         SUBCASE("addition from right to state")
    //         {
    //             FramedOrientation const orientation{
    //                 Orientation::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
    //                 {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
    //             FramedAngularDisplacement const ad{
    //                 AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle =
    //                 90}), "ARMAR-6::RobotRoot"};
    //             FramedAngularDisplacement const ad_wrong_frame{
    //                 AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle =
    //                 90}), "ARMAR-6::PlatformBase"};
    //
    //             auto const new_orientation = orientation + ad;
    //             CHECK(new_orientation.get_name() == "TCP");
    //             CHECK(new_orientation.get_base_frame() == "ARMAR-6::RobotRoot");
    //             CHECK(new_orientation.get_framed_object() ==
    //                   Circa(Orientation::degrees(
    //                       {.axis = {.x = 1 / sqrt(3), .y = 1 / sqrt(3), .z = 1 / sqrt(3)},
    //                        .angle = 120})));
    //
    //             std::string const exception_message =
    //                 "Frame mismatch: ARMAR-6::RobotRoot vs ARMAR-6::PlatformBase";
    //             CHECK_THROWS_WITH(orientation + ad_wrong_frame, exception_message.c_str());
    //         }
    //
    //         SUBCASE("base change - translation")
    //         {
    //             std::string const from_frame = "ARMAR-6::RobotRoot";
    //             std::string const to_frame = "ARMAR-6::TCP_R";
    //             FramedAngularDisplacement const f1{
    //                 AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle =
    //                 90}), from_frame};
    //
    //             BaseChange const bc{
    //                 .from_frame = from_frame,
    //                 .to_frame = to_frame,
    //                 .transformation = SpatialDisplacement(
    //                     LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
    //                     AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle =
    //                     0}))};
    //             auto new_displacement = bc * f1;
    //
    //             CHECK(new_displacement.get_base_frame() == to_frame);
    //             CHECK(new_displacement.get_framed_object() ==
    //                   Circa(AngularDisplacement::degrees(
    //                       {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})));
    //         }
    //
    //         SUBCASE("base change - angular")
    //         {
    //             std::string const from_frame = "ARMAR-6::RobotRoot";
    //             std::string const to_frame = "ARMAR-6::TCP_R";
    //             FramedAngularDisplacement const f1{
    //                 AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle =
    //                 90}), from_frame};
    //
    //             BaseChange const bc{
    //                 .from_frame = from_frame,
    //                 .to_frame = to_frame,
    //                 .transformation = SpatialDisplacement(
    //                     LinearDisplacement::zero(),
    //                     AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle =
    //                     90}))};
    //             auto new_displacement = bc * f1;
    //
    //             CHECK(new_displacement.get_base_frame() == to_frame);
    //             CHECK(new_displacement.get_framed_object() ==
    //                   Circa(AngularDisplacement::degrees(
    //                       {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})));
    //         }
    //
    //         SUBCASE("base change - transform")
    //         {
    //             std::string const from_frame = "ARMAR-6::RobotRoot";
    //             std::string const to_frame = "ARMAR-6::TCP_R";
    //             FramedAngularDisplacement const f1{
    //                 AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle =
    //                 90}), from_frame};
    //
    //             BaseChange const bc{
    //                 .from_frame = from_frame,
    //                 .to_frame = to_frame,
    //                 .transformation = SpatialDisplacement(
    //                     LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
    //                     AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle =
    //                     90}))};
    //             auto new_displacement = bc * f1;
    //
    //             CHECK(new_displacement.get_base_frame() == to_frame);
    //             CHECK(new_displacement.get_framed_object() ==
    //                   Circa(AngularDisplacement::degrees(
    //                       {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})));
    //         }
    //
    //         SUBCASE("base change - wrong frame")
    //         {
    //             std::string const from_frame = "ARMAR-6::RobotRoot";
    //             std::string const to_frame = "ARMAR-6::TCP_R";
    //             FramedAngularDisplacement const f1{
    //                 AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle =
    //                 90}), from_frame};
    //
    //             BaseChange const bc{
    //                 .from_frame = "something else",
    //                 .to_frame = to_frame,
    //                 .transformation = SpatialDisplacement(
    //                     LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
    //                     AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle =
    //                     0}))};
    //
    //             std::string const exception_message =
    //                 "Frame mismatch: something else vs " + std::string(from_frame);
    //             CHECK_THROWS_WITH(bc * f1, exception_message.c_str());
    //         }
    //
    //         SUBCASE("base change - difference of changed states is changed difference")
    //         {
    //             std::string const from_frame = "ARMAR-6::RobotRoot";
    //             std::string const to_frame = "ARMAR-6::TCP_R";
    //             std::string const name = "TCP";
    //             FramedOrientation const o1{
    //                 Orientation::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0}),
    //                 {.name = name, .base_frame = from_frame}};
    //             FramedOrientation const o2{
    //                 Orientation::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 0}),
    //                 {.name = name, .base_frame = from_frame}};
    //             FramedAngularDisplacement const ad = o2 - o1;
    //
    //             BaseChange const bc{
    //                 .from_frame = from_frame,
    //                 .to_frame = to_frame,
    //                 .transformation = SpatialDisplacement(
    //                     LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
    //                     AngularDisplacement::degrees({.axis = {.x = 0, .y = 0, .z = 1}, .angle =
    //                     90}))};
    //             auto const o1_new = bc * o1;
    //             auto const o2_new = bc * o2;
    //             auto const ad_new = o2_new - o1_new;
    //             INFO("o1: ", o1, " o2: ", o2, " ad: ", ad);
    //             INFO("o1': ", o1_new, " o2': ", o2_new, " ad': ", ad_new);
    //             CHECK((bc * ad) == Circa(ad_new));
    //             CHECK(o1_new + (bc * ad) == Circa(o2_new));
    //         }
    //     }
    //
    TEST_CASE("testing framed spatial accelerations")
    {
        SUBCASE("construction")
        {
            FramedSpatialAcceleration const a1{
                SpatialAcceleration(
                    LinearAcceleration::millimeters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                    AngularAcceleration::degrees_per_second_squared(
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedSpatialAcceleration const a2 = FramedSpatialAcceleration::zero({"::", "::"});
            FramedSpatialAcceleration const a3{a1};

            CHECK(a1.get_name() == "TCP");
            CHECK(a1.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(a1.get_framed_object() ==
                  Circa(SpatialAcceleration(
                      LinearAcceleration::millimeters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                      AngularAcceleration::degrees_per_second_squared(
                          {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))));

            CHECK(a2.get_name() == "::");
            CHECK(a2.get_base_frame() == "::");
            CHECK(a2.get_framed_object() == Circa(SpatialAcceleration::zero()));

            CHECK(a3.get_name() == "TCP");
            CHECK(a3.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(a3.get_framed_object() ==
                  Circa(SpatialAcceleration(
                      LinearAcceleration::millimeters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                      AngularAcceleration::degrees_per_second_squared(
                          {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))));
        }

        SUBCASE("subtraction")
        {
            // TODO: implement subtraction
            // FramedSpatialAcceleration const a1{
            //     SpatialAcceleration(LinearAcceleration::millimeters_per_second_squared({.x = 1,
            //     .y = 2, .z = 3}),
            //                         AngularAcceleration::degrees_per_second_squared({.axis = {.x
            //                         = 1, .y = 0, .z = 0}, .angle = 90})),
            //     {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            // FramedSpatialAcceleration const a2{
            //     SpatialAcceleration(LinearAcceleration::millimeters_per_second_squared({.x = 4,
            //     .y = 5, .z = 6}),
            //                         AngularAcceleration::degrees_per_second_squared({.axis = {.x
            //                         = 0, .y = 1, .z = 0}, .angle = 90})),
            //     {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            //
            // auto const diff = a2 - a1;
            //
            // CHECK(diff.get_base_frame() == "ARMAR-6::RobotRoot");
            // CHECK(diff.get_framed_object() ==
            //       Circa(SpatialAccelerationDifference(
            //           LinearAccelerationDifference::millimeters_per_second_squared({.x = 3, .y =
            //           3, .z = -3}), AngularAccelerationDifference::degrees_per_second_squared(
            //               {.axis = {.x = -1 / sqrt(3), .y = 1 / sqrt(3), .z = -1 / sqrt(3)},
            //                .angle = 120}))));
        }

        SUBCASE("base change - translation")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedSpatialAcceleration const a1{
                SpatialAcceleration(
                    LinearAcceleration::millimeters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                    AngularAcceleration::degrees_per_second_squared(
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                {.name = name, .base_frame = from_frame}};

            BaseChange const bc{.from_frame = from_frame,
                                .to_frame = to_frame,
                                .transformation = SpatialDisplacement(
                                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                                    AngularDisplacement::zero())};

            auto a2 = bc * a1;

            CHECK(a2.get_name() == name);
            CHECK(a2.get_base_frame() == to_frame);
            CHECK(a2.get_framed_object() ==
                  Circa(SpatialAcceleration(
                      LinearAcceleration::millimeters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                      AngularAcceleration::degrees_per_second_squared(
                          {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))));
        }

        SUBCASE("base change - rotation")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedSpatialAcceleration const a1{
                SpatialAcceleration(
                    LinearAcceleration::millimeters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                    AngularAcceleration::degrees_per_second_squared(
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                {.name = name, .base_frame = from_frame}};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 0, .y = 0, .z = 0}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};

            auto a2 = bc * a1;

            CHECK(a2.get_name() == name);
            CHECK(a2.get_base_frame() == to_frame);
            CHECK(a2.get_framed_object() ==
                  Circa(SpatialAcceleration(
                      LinearAcceleration::millimeters_per_second_squared({.x = 1, .y = 3, .z = -2}),
                      AngularAcceleration::degrees_per_second_squared(
                          {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))));
        }

        SUBCASE("base change - transform")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedSpatialAcceleration const a1{
                SpatialAcceleration(
                    LinearAcceleration::millimeters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                    AngularAcceleration::degrees_per_second_squared(
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                {.name = name, .base_frame = from_frame}};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};

            auto a2 = bc * a1;

            CHECK(a2.get_name() == name);
            CHECK(a2.get_base_frame() == to_frame);
            CHECK(a2.get_framed_object() ==
                  Circa(SpatialAcceleration(
                      LinearAcceleration::millimeters_per_second_squared({.x = 1, .y = 3, .z = -2}),
                      AngularAcceleration::degrees_per_second_squared(
                          {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))));
        }
    }

    //     TEST_CASE("testing framed spatial displacement")
    //     {
    //         SUBCASE("construction")
    //         {
    //             FramedSpatialDisplacement const f1{
    //                 SpatialDisplacement(
    //                     LinearDisplacement::millimeters({.x = 1, .y = 2, .z = 3}),
    //                     AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle =
    //                     90})),
    //                 "ARMAR-6::RobotRoot"};
    //             FramedSpatialDisplacement const f2{};
    //             FramedSpatialDisplacement const f3{f1};
    //
    //             CHECK(f1.get_base_frame() == "ARMAR-6::RobotRoot");
    //             CHECK(
    //                 f1.get_framed_object() ==
    //                 Circa(SpatialDisplacement(LinearDisplacement::millimeters({.x = 1, .y = 2, .z
    //                 = 3}),
    //                                           AngularDisplacement::degrees(
    //                                               {.axis = {.x = 1, .y = 0, .z = 0}, .angle =
    //                                               90}))));
    //
    //             CHECK(f2.get_base_frame() == "::");
    //             CHECK(f2.get_framed_object() == Circa(SpatialDisplacement::zero()));
    //
    //             CHECK(f3.get_base_frame() == "ARMAR-6::RobotRoot");
    //             CHECK(
    //                 f3.get_framed_object() ==
    //                 Circa(SpatialDisplacement(LinearDisplacement::millimeters({.x = 1, .y = 2, .z
    //                 = 3}),
    //                                           AngularDisplacement::degrees(
    //                                               {.axis = {.x = 1, .y = 0, .z = 0}, .angle =
    //                                               90}))));
    //         }
    //
    //         SUBCASE("base change - translation")
    //         {
    //             std::string const from_frame = "ARMAR-6::RobotRoot";
    //             std::string const to_frame = "ARMAR-6::TCP_R";
    //             FramedSpatialDisplacement const f1{
    //                 SpatialDisplacement(
    //                     LinearDisplacement::millimeters({.x = 1, .y = 2, .z = 3}),
    //                     AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle =
    //                     90})),
    //                 from_frame};
    //
    //             BaseChange const bc{.from_frame = from_frame,
    //                                 .to_frame = to_frame,
    //                                 .transformation = SpatialDisplacement(
    //                                     LinearDisplacement::millimeters({.x = 3, .y = 2, .z =
    //                                     1}), AngularDisplacement::zero())};
    //             auto new_displacement = bc * f1;
    //
    //             CHECK(new_displacement.get_base_frame() == to_frame);
    //             CHECK(
    //                 new_displacement.get_framed_object() ==
    //                 Circa(SpatialDisplacement(LinearDisplacement::millimeters({.x = 1, .y = 2, .z
    //                 = 3}),
    //                                           AngularDisplacement::degrees(
    //                                               {.axis = {.x = 1, .y = 0, .z = 0}, .angle =
    //                                               90}))));
    //         }
    //
    //         SUBCASE("base change - angular")
    //         {
    //             std::string const from_frame = "ARMAR-6::RobotRoot";
    //             std::string const to_frame = "ARMAR-6::TCP_R";
    //             FramedSpatialDisplacement const f1{
    //                 SpatialDisplacement(
    //                     LinearDisplacement::millimeters({.x = 1, .y = 2, .z = 3}),
    //                     AngularDisplacement::degrees({.axis = {.x = 0, .y = 0, .z = 1}, .angle =
    //                     90})),
    //                 from_frame};
    //
    //             BaseChange const bc{
    //                 .from_frame = from_frame,
    //                 .to_frame = to_frame,
    //                 .transformation = SpatialDisplacement(
    //                     LinearDisplacement::zero(),
    //                     AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle =
    //                     90}))};
    //             auto new_displacement = bc * f1;
    //
    //             CHECK(new_displacement.get_base_frame() == to_frame);
    //             CHECK(
    //                 new_displacement.get_framed_object() ==
    //                 Circa(SpatialDisplacement(LinearDisplacement::millimeters({.x = 1, .y = 2, .z
    //                 = 3}),
    //                                           AngularDisplacement::degrees(
    //                                               {.axis = {.x = 0, .y = 0, .z = 1}, .angle =
    //                                               90}))));
    //         }
    //
    //         SUBCASE("base change - transform")
    //         {
    //             std::string const from_frame = "ARMAR-6::RobotRoot";
    //             std::string const to_frame = "ARMAR-6::TCP_R";
    //             FramedSpatialDisplacement const f1{
    //                 SpatialDisplacement(
    //                     LinearDisplacement::millimeters({.x = 1, .y = 2, .z = 3}),
    //                     AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle =
    //                     90})),
    //                 from_frame};
    //
    //             BaseChange const bc{
    //                 .from_frame = from_frame,
    //                 .to_frame = to_frame,
    //                 .transformation = SpatialDisplacement(
    //                     LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
    //                     AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle =
    //                     90}))};
    //             auto new_displacement = bc * f1;
    //
    //             CHECK(new_displacement.get_base_frame() == to_frame);
    //             CHECK(
    //                 new_displacement.get_framed_object() ==
    //                 Circa(SpatialDisplacement(LinearDisplacement::millimeters({.x = 1, .y = 2, .z
    //                 = 3}),
    //                                           AngularDisplacement::degrees(
    //                                               {.axis = {.x = 1, .y = 0, .z = 0}, .angle =
    //                                               90}))));
    //         }
    //
    //         SUBCASE("base change - wrong frame")
    //         {
    //             std::string const from_frame = "ARMAR-6::RobotRoot";
    //             std::string const to_frame = "ARMAR-6::TCP_R";
    //             FramedSpatialDisplacement const f1{
    //                 SpatialDisplacement(
    //                     LinearDisplacement::millimeters({.x = 1, .y = 2, .z = 3}),
    //                     AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle =
    //                     90})),
    //                 from_frame};
    //
    //             BaseChange const bc{
    //                 .from_frame = "something else",
    //                 .to_frame = to_frame,
    //                 .transformation = SpatialDisplacement(
    //                     LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
    //                     AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle =
    //                     0}))};
    //
    //             std::string const exception_message =
    //                 "Frame mismatch: something else vs " + std::string(from_frame);
    //             CHECK_THROWS_WITH(bc * f1, exception_message.c_str());
    //         }
    //
    //         SUBCASE("base change - difference of changed states is changed difference")
    //         {
    //             std::string const from_frame = "ARMAR-6::RobotRoot";
    //             std::string const to_frame = "ARMAR-6::TCP_R";
    //             std::string const name = "TCP";
    //             FramedPose const p1{
    //                 Pose(Position::millimeters({.x = 1, .y = 2, .z = 3}),
    //                      Orientation::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0})),
    //                 {.name = name, .base_frame = from_frame}};
    //             FramedPose const p2{
    //                 Pose(Position::millimeters({.x = 10, .y = 9, .z = 8}),
    //                      Orientation::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 0})),
    //                 {.name = name, .base_frame = from_frame}};
    //             FramedSpatialDisplacement const sd = p2 - p1;
    //
    //             BaseChange const bc{
    //                 .from_frame = from_frame,
    //                 .to_frame = to_frame,
    //                 .transformation = SpatialDisplacement(
    //                     LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
    //                     AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle =
    //                     90}))};
    //             auto const p1_new = bc * p1;
    //             auto const p2_new = bc * p2;
    //             auto const sd_new = p2_new - p1_new;
    //             CHECK(bc * sd == Circa(sd_new));
    //         }
    //     }
    // }
    //
}