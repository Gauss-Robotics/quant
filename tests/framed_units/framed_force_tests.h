#pragma once
#include <quant/framed_units/force.h>
#include <quant/geometry/Circa.h>
#include <quant/units/force.h>

#include <doctest/doctest.h>

#include <iostream>

using namespace quant;  // NOLINT

TEST_SUITE("testing framed force domain")
{
    TEST_CASE("testing framed forces")
    {
        SUBCASE("construction")
        {
            FramedForce const f1{Force::newtons({.x = 1, .y = 2, .z = 3}),
                                 {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedForce const f2{};
            FramedForce const f3{f1};

            CHECK(f1.get_name() == "TCP");
            CHECK(f1.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(f1.get_framed_object() == Circa(Force::newtons({.x = 1, .y = 2, .z = 3})));

            CHECK(f2.get_name() == "::");
            CHECK(f2.get_base_frame() == "::");
            CHECK(f2.get_framed_object() == Circa(Force::zero()));

            CHECK(f3.get_name() == "TCP");
            CHECK(f3.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(f3.get_framed_object() == Circa(Force::newtons({.x = 1, .y = 2, .z = 3})));
        }

        SUBCASE("subtraction")
        {
            FramedForce const f1{Force::newtons({.x = 1, .y = 2, .z = 3}),
                                 {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedForce const f2{Force::newtons({.x = 4, .y = 5, .z = 6}),
                                 {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};

            auto const diff = f2 - f1;

            CHECK(diff.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(diff.get_framed_object() ==
                  Circa(ForceDifference::newtons({.x = 3, .y = 3, .z = 3})));
        }

        SUBCASE("base change - translation")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedForce const f1{Force::newtons({.x = 1, .y = 2, .z = 3}),
                                 {.name = name, .base_frame = from_frame}};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0}))};

            auto f2 = bc * f1;

            CHECK(f2.get_name() == name);
            CHECK(f2.get_base_frame() == to_frame);
            CHECK(f2.get_framed_object() == Circa(Force::newtons({.x = 1, .y = 2, .z = 3})));
        }

        SUBCASE("base change - rotation")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedForce const f1{Force::newtons({.x = 1, .y = 2, .z = 3}),
                                 {.name = name, .base_frame = from_frame}};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 0, .y = 0, .z = 0}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};

            auto f2 = bc * f1;

            CHECK(f2.get_name() == name);
            CHECK(f2.get_base_frame() == to_frame);
            CHECK(f2.get_framed_object() == Circa(Force::newtons({.x = 1, .y = 3, .z = -2})));
        }

        SUBCASE("base change - transform")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedForce const f1{Force::newtons({.x = 1, .y = 2, .z = 3}),
                                 {.name = name, .base_frame = from_frame}};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};

            auto f2 = bc * f1;

            CHECK(f2.get_name() == name);
            CHECK(f2.get_base_frame() == to_frame);
            CHECK(f2.get_framed_object() == Circa(Force::newtons({.x = 1, .y = 3, .z = -2})));
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

    TEST_CASE("testing framed torques")
    {
        SUBCASE("construction")
        {
            FramedTorque const t1{
                Torque::newton_meters({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedTorque const t2{};
            FramedTorque const t3{t1};

            CHECK(t1.get_name() == "TCP");
            CHECK(t1.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(t1.get_framed_object() ==
                  Circa(Torque::newton_meters({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})));

            CHECK(t2.get_name() == "::");
            CHECK(t2.get_base_frame() == "::");
            CHECK(t2.get_framed_object() == Circa(Torque::zero()));

            CHECK(t3.get_name() == "TCP");
            CHECK(t3.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(t3.get_framed_object() ==
                  Circa(Torque::newton_meters({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})));
        }

        SUBCASE("subtraction")
        {
            FramedTorque const t1{
                Torque::newton_meters({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedTorque const t2{
                Torque::newton_meters({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}),
                {.name = "CoM", .base_frame = "ARMAR-6::RobotRoot"}};

            auto const diff = t2 - t1;

            CHECK(diff.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(diff.get_framed_object() ==
                  Circa(TorqueDifference::newton_meters(
                      {.axis = {.x = -1 / sqrt(3), .y = 1 / sqrt(3), .z = -1 / sqrt(3)},
                       .angle = 120})));
        }

        SUBCASE("base change - rotation")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedTorque const t1{
                Torque::newton_meters({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                {.name = name, .base_frame = from_frame}};

            BaseChange const bc{.from_frame = from_frame,
                                .to_frame = to_frame,
                                .transformation = SpatialDisplacement(
                                    LinearDisplacement::zero(),
                                    AngularDisplacement::degrees(
                                        {.axis = {.x = 0, .y = 1, .z = 0}, .angle = 270}))};
            auto t2 = bc * t1;

            CHECK(t2.get_name() == name);
            CHECK(t2.get_base_frame() == to_frame);
            CHECK(t2.get_framed_object() ==
                  Circa(Torque::newton_meters({.axis = {.x = 0, .y = 0, .z = -1}, .angle = 90})));
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
    TEST_CASE("testing framed wrenches")
    {
        SUBCASE("construction")
        {
            FramedWrench const w1{
                Wrench(Force::newtons({.x = 1, .y = 2, .z = 3}),
                       Torque::newton_meters({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedWrench const w2{};
            FramedWrench const w3{w1};

            CHECK(w1.get_name() == "TCP");
            CHECK(w1.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(w1.get_framed_object() ==
                  Circa(Wrench(
                      Force::newtons({.x = 1, .y = 2, .z = 3}),
                      Torque::newton_meters({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))));

            CHECK(w2.get_name() == "::");
            CHECK(w2.get_base_frame() == "::");
            CHECK(w2.get_framed_object() == Circa(Wrench::zero()));

            CHECK(w3.get_name() == "TCP");
            CHECK(w3.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(w3.get_framed_object() ==
                  Circa(Wrench(
                      Force::newtons({.x = 1, .y = 2, .z = 3}),
                      Torque::newton_meters({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))));
        }

        SUBCASE("subtraction")
        {
            // TODO: implement subtraction
            // FramedWrench const w1{
            //     Wrench(Force::newtons({.x = 1, .y = 2, .z = 3}),
            //           Torque::newton_meters({.axis = {.x = 1, .y = 0, .z = 0}, .magnitude =
            //           90})),
            //     {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            // FramedWrench const w2{
            //     Wrench(Force::newtons({.x = 4, .y = 5, .z = 6}),
            //           Torque::newton_meters({.axis = {.x = 0, .y = 1, .z = 0}, .magnitude =
            //           90})),
            //     {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            //
            // auto const diff = w2 - w1;
            //
            // CHECK(diff.get_base_frame() == "ARMAR-6::RobotRoot");
            // CHECK(diff.get_framed_object() ==
            //       Circa(WrenchDifference(
            //           ForceDifference::newtons({.x = 3, .y = 3, .z = 3}),
            //           TorqueDifference::newton_meters(
            //               {.axis = {.x = -1 / sqrt(3), .y = 1 / sqrt(3), .z = -1 / sqrt(3)},
            //                .magnitude = 120}))));
        }

        SUBCASE("base change - translation")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedWrench const w1{
                Wrench(Force::newtons({.x = 1, .y = 2, .z = 3}),
                       Torque::newton_meters({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                {.name = name, .base_frame = from_frame}};

            BaseChange const bc{.from_frame = from_frame,
                                .to_frame = to_frame,
                                .transformation = SpatialDisplacement(
                                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                                    AngularDisplacement::zero())};

            auto w2 = bc * w1;

            CHECK(w2.get_name() == name);
            CHECK(w2.get_base_frame() == to_frame);
            CHECK(w2.get_framed_object() ==
                  Circa(Wrench(
                      Force::newtons({.x = 4, .y = 1, .z = 5}),
                      Torque::newton_meters({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))));
        }

        SUBCASE("base change - rotation")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedWrench const w1{
                Wrench(Force::newtons({.x = 1, .y = 2, .z = 3}),
                       Torque::newton_meters({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                {.name = name, .base_frame = from_frame}};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 0, .y = 0, .z = 0}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};

            auto w2 = bc * w1;

            CHECK(w2.get_name() == name);
            CHECK(w2.get_base_frame() == to_frame);
            CHECK(w2.get_framed_object() ==
                  Circa(Wrench(
                      Force::newtons({.x = 1, .y = 3, .z = -2}),
                      Torque::newton_meters({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))));
        }

        SUBCASE("base change - transform")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedWrench const w1{
                Wrench(Force::newtons({.x = 1, .y = 2, .z = 3}),
                       Torque::newton_meters({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                {.name = name, .base_frame = from_frame}};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};

            auto w2 = bc * w1;

            CHECK(w2.get_name() == name);
            CHECK(w2.get_base_frame() == to_frame);
            CHECK(w2.get_framed_object() ==
                  Circa(Wrench(
                      Force::newtons({.x = 4, .y = 5, .z = -1}),
                      Torque::newton_meters({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))));
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

    TEST_CASE("Example 3.28 Modern Robotics")
    {
        FramedWrench const F_h{Wrench(Force::newtons({.x = 0, .y = -5, .z = 0}), Torque::zero()),
                               {.name = "F_h", .base_frame = "H"}};
        FramedWrench const F_a{Wrench(Force::newtons({.x = 0, .y = 0, .z = 1}), Torque::zero()),
                               {.name = "F_a", .base_frame = "A"}};
        SpatialDisplacement const T_hf{LinearDisplacement::meters({-.1, 0, 0}),
                                       AngularDisplacement::zero()};
        SpatialDisplacement const T_af{
            LinearDisplacement::meters({-0.25, 0, .1}),
            AngularDisplacement::degrees({.axis = {1, 0, 0}, .angle = 180})};

        const auto from_H_to_F = BaseChange{"H", "F", T_hf};
        const auto from_A_to_F = BaseChange{"A", "F", T_af};
        const auto diff = FramedWrenchDifference(from_A_to_F * F_a);
        // const auto F_f = from_H_to_F * F_h + diff;
    }
}
