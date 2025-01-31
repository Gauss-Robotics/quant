#pragma once
#include <quant/framed_units/velocity.h>
#include <quant/framed_units/velocity/forward_declarations.h>
#include <quant/geometry/Circa.h>
#include <quant/units/velocity.h>

#include <doctest/doctest.h>

#include <iostream>

using namespace quant;  // NOLINT

TEST_SUITE("testing framed velocity domain")
{
    TEST_CASE("testing framed linear velocities")
    {
        SUBCASE("construction")
        {
            FramedLinearVelocity const v1{
                LinearVelocity::meters_per_second({.x = 1, .y = 2, .z = 3}),
                {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedLinearVelocity const v2{};
            FramedLinearVelocity const v3{v1};

            CHECK(v1.get_name() == "TCP");
            CHECK(v1.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(v1.get_framed_object() ==
                  Circa(LinearVelocity::meters_per_second({.x = 1, .y = 2, .z = 3})));

            CHECK(v2.get_name() == "::");
            CHECK(v2.get_base_frame() == "::");
            CHECK(v2.get_framed_object() == Circa(LinearVelocity::zero()));

            CHECK(v3.get_name() == "TCP");
            CHECK(v3.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(v3.get_framed_object() ==
                  Circa(LinearVelocity::meters_per_second({.x = 1, .y = 2, .z = 3})));
        }

        SUBCASE("subtraction")
        {
            FramedLinearVelocity const v1{
                LinearVelocity::meters_per_second({.x = 1, .y = 2, .z = 3}),
                {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedLinearVelocity const v2{
                LinearVelocity::meters_per_second({.x = 4, .y = 5, .z = 6}),
                {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};

            auto const diff = v2 - v1;

            CHECK(diff.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(diff.get_framed_object() ==
                  Circa(LinearVelocityDifference::meters_per_second({.x = 3, .y = 3, .z = 3})));
        }

        SUBCASE("base change - translation")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedLinearVelocity const v1{
                LinearVelocity::meters_per_second({.x = 1, .y = 2, .z = 3}),
                {.name = name, .base_frame = from_frame}};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0}))};

            auto v2 = bc * v1;

            CHECK(v2.get_name() == name);
            CHECK(v2.get_base_frame() == to_frame);
            CHECK(v2.get_framed_object() ==
                  Circa(LinearVelocity::meters_per_second({.x = 1, .y = 2, .z = 3})));
        }

        SUBCASE("base change - rotation")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedLinearVelocity const v1{
                LinearVelocity::meters_per_second({.x = 1, .y = 2, .z = 3}),
                {.name = name, .base_frame = from_frame}};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 0, .y = 0, .z = 0}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};

            auto v2 = bc * v1;

            CHECK(v2.get_name() == name);
            CHECK(v2.get_base_frame() == to_frame);
            CHECK(v2.get_framed_object() ==
                  Circa(LinearVelocity::meters_per_second({.x = 1, .y = 3, .z = -2})));
        }

        SUBCASE("base change - transform")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedLinearVelocity const v1{
                LinearVelocity::meters_per_second({.x = 1, .y = 2, .z = 3}),
                {.name = name, .base_frame = from_frame}};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};

            auto v2 = bc * v1;

            CHECK(v2.get_name() == name);
            CHECK(v2.get_base_frame() == to_frame);
            CHECK(v2.get_framed_object() ==
                  Circa(LinearVelocity::meters_per_second({.x = 1, .y = 3, .z = -2})));
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

    TEST_CASE("testing framed angular velocities")
    {
        SUBCASE("construction")
        {
            FramedAngularVelocity const f1{AngularVelocity::degrees_per_second(
                                               {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                                           {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedAngularVelocity const f2{};
            FramedAngularVelocity const f3{f1};

            CHECK(f1.get_name() == "TCP");
            CHECK(f1.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(f1.get_framed_object() == Circa(AngularVelocity::degrees_per_second(
                                                {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})));

            CHECK(f2.get_name() == "::");
            CHECK(f2.get_base_frame() == "::");
            CHECK(f2.get_framed_object() == Circa(AngularVelocity::zero()));

            CHECK(f3.get_name() == "TCP");
            CHECK(f3.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(f3.get_framed_object() == Circa(AngularVelocity::degrees_per_second(
                                                {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})));
        }

        SUBCASE("subtraction")
        {
            FramedAngularVelocity const f1{AngularVelocity::degrees_per_second(
                                               {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                                           {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedAngularVelocity const f2{AngularVelocity::degrees_per_second(
                                               {.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}),
                                           {.name = "CoM", .base_frame = "ARMAR-6::RobotRoot"}};

            auto const diff = f2 - f1;

            CHECK(diff.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(diff.get_framed_object() ==
                  Circa(AngularVelocityDifference::degrees_per_second(
                      {.axis = {.x = -1 / sqrt(3), .y = 1 / sqrt(3), .z = -1 / sqrt(3)},
                       .angle = 120})));
        }

        SUBCASE("base change - rotation")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedAngularVelocity const f1{AngularVelocity::degrees_per_second(
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
            CHECK(f2.get_framed_object() == Circa(AngularVelocity::degrees_per_second(
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
    TEST_CASE("testing framed poses")
    {
        SUBCASE("construction")
        {
            FramedTwist const t1{
                Twist(LinearVelocity::millimeters_per_second({.x = 1, .y = 2, .z = 3}),
                      AngularVelocity::degrees_per_second(
                          {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedTwist const t2{};
            FramedTwist const t3{t1};

            CHECK(t1.get_name() == "TCP");
            CHECK(t1.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(t1.get_framed_object() ==
                  Circa(Twist(LinearVelocity::millimeters_per_second({.x = 1, .y = 2, .z = 3}),
                              AngularVelocity::degrees_per_second(
                                  {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))));

            CHECK(t2.get_name() == "::");
            CHECK(t2.get_base_frame() == "::");
            CHECK(t2.get_framed_object() == Circa(Twist::zero()));

            CHECK(t3.get_name() == "TCP");
            CHECK(t3.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(t3.get_framed_object() ==
                  Circa(Twist(LinearVelocity::millimeters_per_second({.x = 1, .y = 2, .z = 3}),
                              AngularVelocity::degrees_per_second(
                                  {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))));
        }

        SUBCASE("subtraction")
        {
            // TODO: implement subtraction
            // FramedTwist const t1{
            //     Twist(LinearVelocity::millimeters_per_second({.x = 1, .y = 2, .z = 3}),
            //           AngularVelocity::degrees_per_second({.axis = {.x = 1, .y = 0, .z = 0},
            //           .angle = 90})),
            //     {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            // FramedTwist const t2{
            //     Twist(LinearVelocity::millimeters_per_second({.x = 4, .y = 5, .z = 6}),
            //           AngularVelocity::degrees_per_second({.axis = {.x = 0, .y = 1, .z = 0},
            //           .angle = 90})),
            //     {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            //
            // auto const diff = t2 - t1;
            //
            // CHECK(diff.get_base_frame() == "ARMAR-6::RobotRoot");
            // CHECK(diff.get_framed_object() ==
            //       Circa(TwistDifference(
            //           LinearVelocityDifference::millimeters_per_second({.x = 3, .y = 3, .z =
            //           -3}), AngularVelocityDifference::degrees_per_second(
            //               {.axis = {.x = -1 / sqrt(3), .y = 1 / sqrt(3), .z = -1 / sqrt(3)},
            //                .angle = 120}))));
        }

        SUBCASE("base change - translation")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedTwist const t1{
                Twist(LinearVelocity::millimeters_per_second({.x = 1, .y = 2, .z = 3}),
                      AngularVelocity::degrees_per_second(
                          {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                {.name = name, .base_frame = from_frame}};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::zero())};

            auto t2 = bc * t1;

            CHECK(t2.get_name() == name);
            CHECK(t2.get_base_frame() == to_frame);
            CHECK(t2.get_framed_object() ==
                  Circa(Twist(LinearVelocity::millimeters_per_second({.x = 1, .y = 2, .z = 3}),
                              AngularVelocity::degrees_per_second(
                                  {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))));
        }

        SUBCASE("base change - rotation")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedTwist const t1{
                Twist(LinearVelocity::millimeters_per_second({.x = 1, .y = 2, .z = 3}),
                      AngularVelocity::degrees_per_second(
                          {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                {.name = name, .base_frame = from_frame}};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 0, .y = 0, .z = 0}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};

            auto t2 = bc * t1;

            CHECK(t2.get_name() == name);
            CHECK(t2.get_base_frame() == to_frame);
            CHECK(t2.get_framed_object() ==
                  Circa(Twist(LinearVelocity::millimeters_per_second({.x = 1, .y = 3, .z = -2}),
                              AngularVelocity::degrees_per_second(
                                  {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))));
        }

        SUBCASE("base change - transform")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedTwist const t1{
                Twist(LinearVelocity::millimeters_per_second({.x = 1, .y = 2, .z = 3}),
                      AngularVelocity::degrees_per_second(
                          {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                {.name = name, .base_frame = from_frame}};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};

            auto t2 = bc * t1;

            CHECK(t2.get_name() == name);
            CHECK(t2.get_base_frame() == to_frame);
            CHECK(t2.get_framed_object() ==
                  Circa(Twist(LinearVelocity::millimeters_per_second({.x = 1, .y = 3, .z = -2}),
                              AngularVelocity::degrees_per_second(
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
    // TEST_SUITE("end to end test (see coordinate system visualization)")
    // {
    //     using PoseAccessor = geometry::detail::StateAccessor<Pose>;
    //     auto const origin =
    //         FramedPose(Pose(Position::zero(), Orientation::zero()), {"global", "global"});
    //     auto const F1 = FramedPose(
    //         PoseAccessor::make(Eigen::Isometry3d(
    //             (Eigen::Matrix4d() << 0, 0, -1, 3, 0, 1, 0, 3, 1, 0, 0, 0, 0, 0, 0,
    //             1).finished())),
    //         {"F1", "global"});
    //     auto const F2 = FramedPose(
    //         PoseAccessor::make(Eigen::Isometry3d(
    //             (Eigen::Matrix4d() << 0, -1, 0, 13, 1, 0, 0, 3, 0, 0, 1, 0, 0, 0, 0,
    //             1).finished())),
    //         {"F2", "global"});
    //     auto const O1 = FramedPose(
    //         PoseAccessor::make(Eigen::Isometry3d(
    //             (Eigen::Matrix4d() << 1, 0, 0, 5, 0, 1, 0, 5, 0, 0, 1, 0, 0, 0, 0,
    //             1).finished())),
    //         {"O1", "global"});
    //     auto const O2 = FramedPose(
    //         PoseAccessor::make(Eigen::Isometry3d(
    //             (Eigen::Matrix4d() << 0, 0, -1, 9, -1, 0, 0, 6, 0, 1, 0, 0, 0, 0, 0,
    //             1).finished())),
    //         {"O2", "global"});
    //
    //     auto const O1_in_F1 = FramedPose(
    //         PoseAccessor::make(Eigen::Isometry3d(
    //             (Eigen::Matrix4d() << 0, 0, 1, 0, 0, 1, 0, 2, -1, 0, 0, -2, 0, 0, 0,
    //             1).finished())),
    //         {"O1_in_F1", "F1"});
    //     auto const O2_in_F1 = FramedPose(
    //         PoseAccessor::make(Eigen::Isometry3d(
    //             (Eigen::Matrix4d() << 0, 1, 0, 0, -1, 0, 0, 3, 0, 0, 1, -6, 0, 0, 0,
    //             1).finished())),
    //         {"O2_in_F1", "F1"});
    //     auto const O1_in_F2 = FramedPose(
    //         PoseAccessor::make(Eigen::Isometry3d(
    //             (Eigen::Matrix4d() << 0, 1, 0, 2, -1, 0, 0, 8, 0, 0, 1, 0, 0, 0, 0,
    //             1).finished())),
    //         {"O1_in_F2", "F2"});
    //     auto const O2_in_F2 = FramedPose(
    //         PoseAccessor::make(Eigen::Isometry3d(
    //             (Eigen::Matrix4d() << -1, 0, 0, 3, 0, 0, 1, 4, 0, 1, 0, 0, 0, 0, 0,
    //             1).finished())),
    //         {"O2_in_F2", "F2"});
    //
    //     auto const F1_to_F2 = SpatialDisplacement(PoseAccessor::make(Eigen::Isometry3d(
    //         (Eigen::Matrix4d() << 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, -10, 0, 0, 0,
    //         1).finished())));
    //     auto const base_change = BaseChange("F1", "F2", F1_to_F2);
    //
    //     auto const p1 = FramedPosition(Position::millimeters({4, 4, 0}), {"p1", "global"});
    //     auto const p2 = FramedPosition(Position::millimeters({5, 4, 0}), {"p2", "global"});
    //     auto const p1_in_F1 = FramedPosition(Position::millimeters({0, 1, -1}), {"p1", "F1"});
    //     auto const p2_in_F1 = FramedPosition(Position::millimeters({0, 1, -2}), {"p2", "F1"});
    //     auto const p1_in_F2 = FramedPosition(Position::millimeters({1, 9, 0}), {"p1", "F2"});
    //     auto const p2_in_F2 = FramedPosition(Position::millimeters({1, 8, 0}), {"p2", "F2"});
    //
    //     TEST_CASE("difference of F1 and F2 is F1_to_F2")
    //     {
    //         CHECK(F1_to_F2 == Circa((F2 - F1).get_framed_object()));
    //     }
    //
    //     TEST_CASE("poses and positions transform correctly")
    //     {
    //         auto make_base_change = [](FramedPose const& from, FramedPose const& to)
    //         { return BaseChange(from.get_name(), to.get_name(), (to - from).get_framed_object());
    //         }; auto const origin_to_F1 = make_base_change(origin, F1); auto const origin_to_F2 =
    //         make_base_change(origin, F2); CHECK(base_change * O1_in_F1 == Circa(O1_in_F2));
    //         CHECK(base_change * O2_in_F1 == Circa(O2_in_F2));
    //         CHECK(origin_to_F1 * O1 == Circa(O1_in_F1));
    //         CHECK(origin_to_F1 * O2 == Circa(O2_in_F1));
    //         CHECK(origin_to_F2 * O1 == Circa(O1_in_F2));
    //         CHECK(origin_to_F2 * O2 == Circa(O2_in_F2));
    //         CHECK(origin_to_F1 * p1 == Circa(p1_in_F1));
    //         CHECK(origin_to_F1 * p2 == Circa(p2_in_F1));
    //         CHECK(origin_to_F2 * p1 == Circa(p1_in_F2));
    //         CHECK(origin_to_F2 * p2 == Circa(p2_in_F2));
    //     }
    //
    //     TEST_CASE("differences of O1 and O2 do not change under base change")
    //     {
    //         auto temp_pose = PoseAccessor::make(Eigen::Isometry3d(
    //             (Eigen::Matrix4d() << 0., 0., -1., 4., -1., 0., 0., 1., 0., 1., 0., 0., 0., 0.,
    //             0., 1.)
    //                 .finished()));
    //         auto const delta_o12_in_F1 =
    //             FramedSpatialDisplacement(SpatialDisplacement(temp_pose), "F1");
    //         temp_pose = PoseAccessor::make(Eigen::Isometry3d(
    //             (Eigen::Matrix4d() << 0., 0., -1., 4., -1., 0., 0., 1., 0., 1., 0., 0., 0., 0.,
    //             0., 1.)
    //                 .finished()));
    //         auto const delta_o12_in_F2 =
    //             FramedSpatialDisplacement(SpatialDisplacement(temp_pose), "F2");
    //         CHECK((O2_in_F1 - O1_in_F1).get_framed_object() ==
    //               Circa((base_change * (O2_in_F1 - O1_in_F1)).get_framed_object()));
    //         CHECK((O2_in_F1 - O1_in_F1).get_framed_object() ==
    //               Circa((O2_in_F2 - O1_in_F2).get_framed_object()));
    //         CHECK(delta_o12_in_F1 == Circa((O2_in_F1 - O1_in_F1)));
    //         CHECK(delta_o12_in_F2 == Circa(O2_in_F2 - O1_in_F2));
    //     }
    //
    //     TEST_CASE("positions do not behave as poses/orientations")
    //     {
    //         auto const delta_p12_in_F1 = p2_in_F1 - p1_in_F1;
    //         auto const delta_p12_in_F2 = p2_in_F2 - p1_in_F2;
    //         CHECK(delta_p12_in_F1 != Circa(delta_p12_in_F2));
    //     }
}