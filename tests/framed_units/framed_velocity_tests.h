#pragma once
#include <quant/framed_geometry/Adjoint.h>
#include <quant/framed_units/velocity.h>
#include <quant/framed_units/velocity/forward_declarations.h>
#include <quant/geometry/Circa.h>
#include <quant/units/velocity.h>

#include <doctest/doctest.h>

#include <math.h>

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
            FramedLinearVelocity const v2 = FramedLinearVelocity::zero({"::", "::"});
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

    TEST_CASE("testing framed linear velocity differences")
    {
        SUBCASE("construction")
        {
            FramedLinearVelocityDifference const v1{
                LinearVelocityDifference::meters_per_second({.x = 1, .y = 2, .z = 3}),
                "ARMAR-6::RobotRoot"};
            FramedLinearVelocityDifference const v2 = FramedLinearVelocityDifference::zero("::");
            FramedLinearVelocityDifference const v3{v1};

            CHECK(v1.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(v1.get_framed_object() ==
                  Circa(LinearVelocityDifference::meters_per_second({.x = 1, .y = 2, .z = 3})));

            CHECK(v2.get_base_frame() == "::");
            CHECK(v2.get_framed_object() == Circa(LinearVelocityDifference::zero()));

            CHECK(v3.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(v3.get_framed_object() ==
                  Circa(LinearVelocityDifference::meters_per_second({.x = 1, .y = 2, .z = 3})));
        }

        SUBCASE("addition from right to state")
        {
            FramedLinearVelocity const velocity{
                LinearVelocity::meters_per_second({.x = 1, .y = 2, .z = 3}),
                {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedLinearVelocityDifference const ld{
                LinearVelocityDifference::meters_per_second({.x = 3, .y = 2, .z = 1}),
                "ARMAR-6::RobotRoot"};
            FramedLinearVelocityDifference const ld_wrong_frame{
                LinearVelocityDifference::meters_per_second({.x = 3, .y = 2, .z = 1}),
                "ARMAR-6::PlatformBase"};

            auto const new_velocity = velocity + ld;
            CHECK(new_velocity.get_name() == "TCP");
            CHECK(new_velocity.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(new_velocity.get_framed_object() ==
                  Circa(LinearVelocity::meters_per_second({.x = 4, .y = 4, .z = 4})));

            std::string const exception_message =
                "Frame mismatch: ARMAR-6::RobotRoot vs ARMAR-6::PlatformBase";
            CHECK_THROWS_WITH(velocity + ld_wrong_frame, exception_message.c_str());
        }

        SUBCASE("base change - translation")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            FramedLinearVelocityDifference const v1{
                LinearVelocityDifference::meters_per_second({.x = 1, .y = 2, .z = 3}), from_frame};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0}))};
            WARN_NOTHROW(bc * v1);
        }

        SUBCASE("base change - angular")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            FramedLinearVelocityDifference const v1{
                LinearVelocityDifference::meters_per_second({.x = 1, .y = 2, .z = 3}), from_frame};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::zero(),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};
            WARN_NOTHROW(bc * v1);
        }

        SUBCASE("base change - transform")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            FramedLinearVelocityDifference const v1{
                LinearVelocityDifference::meters_per_second({.x = 1, .y = 2, .z = 3}), from_frame};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};
            WARN_NOTHROW(bc * v1);
        }
        SUBCASE("base change - difference of changed states is changed difference")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedLinearVelocity const v1{
                LinearVelocity::meters_per_second({.x = 1, .y = 2, .z = 3}),
                {.name = name, .base_frame = from_frame}};
            FramedLinearVelocity const v2{
                LinearVelocity::meters_per_second({.x = 10, .y = 9, .z = 8}),
                {.name = name, .base_frame = from_frame}};
            FramedLinearVelocityDifference const ld = v2 - v1;

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};
            auto const v1_new = bc * v1;
            auto const v2_new = bc * v2;
            auto const ld_new = v2_new - v1_new;
            WARN_NOTHROW(bc * ld == Circa(ld_new));
        }
    }

    TEST_CASE("testing framed angular velocities")
    {
        SUBCASE("construction")
        {
            FramedAngularVelocity const f1{AngularVelocity::degrees_per_second(
                                               {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                                           {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedAngularVelocity const f2 = FramedAngularVelocity::zero({"::", "::"});
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
                      {.axis = {.x = -1 / sqrt(2), .y = 1 / sqrt(2), .z = 0},
                       .angle = sqrt(2) * 90})));
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

    TEST_CASE("testing framed angular velocity differences")
    {
        SUBCASE("construction")
        {
            FramedAngularVelocityDifference const f1{
                AngularVelocityDifference::degrees_per_second(
                    {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                "ARMAR-6::RobotRoot"};
            FramedAngularVelocityDifference const f2 = FramedAngularVelocityDifference::zero("::");
            FramedAngularVelocityDifference const f3{f1};

            CHECK(f1.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(f1.get_framed_object() == Circa(AngularVelocityDifference::degrees_per_second(
                                                {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})));

            CHECK(f2.get_base_frame() == "::");
            CHECK(f2.get_framed_object() == Circa(AngularVelocityDifference::zero()));

            CHECK(f3.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(f3.get_framed_object() == Circa(AngularVelocityDifference::degrees_per_second(
                                                {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})));
        }

        SUBCASE("addition from right to state")
        {
            FramedAngularVelocity const velocity{
                AngularVelocity::degrees_per_second(
                    {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedAngularVelocityDifference const ad{
                AngularVelocityDifference::degrees_per_second(
                    {.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}),
                "ARMAR-6::RobotRoot"};
            FramedAngularVelocityDifference const ad_wrong_frame{
                AngularVelocityDifference::degrees_per_second(
                    {.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}),
                "ARMAR-6::PlatformBase"};

            auto const new_velocity = velocity + ad;
            CHECK(new_velocity.get_name() == "TCP");
            CHECK(new_velocity.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(new_velocity.get_framed_object() ==
                  Circa(AngularVelocity::degrees_per_second(
                      {.axis = {.x = 1 / sqrt(2), .y = 1 / sqrt(2), .z = 0},
                       .angle = sqrt(2) * 90})));

            std::string const exception_message =
                "Frame mismatch: ARMAR-6::RobotRoot vs ARMAR-6::PlatformBase";
            CHECK_THROWS_WITH(velocity + ad_wrong_frame, exception_message.c_str());
        }

        SUBCASE("base change - translation")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            FramedAngularVelocityDifference const f1{
                AngularVelocityDifference::degrees_per_second(
                    {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                from_frame};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0}))};
            WARN_NOTHROW(bc * f1);
        }

        SUBCASE("base change - angular")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            FramedAngularVelocityDifference const f1{
                AngularVelocityDifference::degrees_per_second(
                    {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                from_frame};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::zero(),
                    AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}))};
            WARN_NOTHROW(bc * f1);
        }

        SUBCASE("base change - transform")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            FramedAngularVelocityDifference const f1{
                AngularVelocityDifference::degrees_per_second(
                    {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                from_frame};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}))};
            WARN_NOTHROW(bc * f1);
        }

        SUBCASE("base change - difference of changed states is changed difference")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedAngularVelocity const o1{
                AngularVelocity::degrees_per_second({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0}),
                {.name = name, .base_frame = from_frame}};
            FramedAngularVelocity const o2{
                AngularVelocity::degrees_per_second({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 0}),
                {.name = name, .base_frame = from_frame}};
            FramedAngularVelocityDifference const ad = o2 - o1;

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 0, .y = 0, .z = 1}, .angle = 90}))};
            auto const o1_new = bc * o1;
            auto const o2_new = bc * o2;
            auto const ad_new = o2_new - o1_new;
            WARN_NOTHROW((bc * ad) == Circa(ad_new));
            WARN_NOTHROW(o1_new + (bc * ad) == Circa(o2_new));
        }
    }

    TEST_CASE("testing framed twists")
    {
        SUBCASE("construction")
        {
            FramedTwist const t1{
                Twist(LinearVelocity::millimeters_per_second({.x = 1, .y = 2, .z = 3}),
                      AngularVelocity::degrees_per_second(
                          {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedTwist const t2 = FramedTwist::zero({"::", "::"});
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
            FramedTwist const t1{Twist(LinearVelocity::meters_per_second({.x = 1, .y = 0, .z = 0}),
                                       AngularVelocity::degrees_per_second(
                                           {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                                 {.name = name, .base_frame = from_frame}};

            BaseChange const bc{.from_frame = from_frame,
                                .to_frame = to_frame,
                                .transformation = SpatialDisplacement(
                                    LinearDisplacement::meters({.x = 3, .y = 2, .z = 1}),
                                    AngularDisplacement::zero())};

            auto t2 = bc * t1;

            CHECK(t2.get_name() == name);
            CHECK(t2.get_base_frame() == to_frame);
            CHECK(t2.get_framed_object() ==
                  Circa(Twist(LinearVelocity::meters_per_second({.x = 1, .y = -M_PI_2, .z = M_PI}),
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
                Twist(LinearVelocity::millimeters_per_second({.x = 1, .y = 2, .z = 0}),
                      AngularVelocity::degrees_per_second({.x = 180, .y = 0, .z = 0})),
                {.name = name, .base_frame = from_frame}};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 1, .y = 1, .z = 0}),
                    AngularDisplacement::degrees({.axis = {.x = 0, .y = 0, .z = 1}, .angle = 90}))};

            auto t2 = bc * t1;

            CHECK(t2.get_name() == name);
            CHECK(t2.get_base_frame() == to_frame);
            CHECK(t2.get_framed_object() ==
                  Circa(Twist(LinearVelocity::millimeters_per_second({.x = 2, .y = -1, .z = M_PI}),
                              AngularVelocity::degrees_per_second(
                                  {.axis = {.x = 0, .y = 1, .z = 0}, .angle = -180}))));
        }
    }

    TEST_CASE("testing framed twist differences")
    {
        SUBCASE("construction")
        {
            FramedTwistDifference const f1{
                TwistDifference(
                    LinearVelocityDifference::millimeters_per_second({.x = 1, .y = 2, .z = 3}),
                    AngularVelocityDifference::degrees_per_second(
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                "ARMAR-6::RobotRoot"};
            FramedTwistDifference const f2 = FramedTwistDifference::zero("::");
            FramedTwistDifference const f3{f1};

            CHECK(f1.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(f1.get_framed_object() ==
                  Circa(TwistDifference(
                      LinearVelocityDifference::millimeters_per_second({.x = 1, .y = 2, .z = 3}),
                      AngularVelocityDifference::degrees_per_second(
                          {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))));

            CHECK(f2.get_base_frame() == "::");
            CHECK(f2.get_framed_object() == Circa(TwistDifference::zero()));

            CHECK(f3.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(f3.get_framed_object() ==
                  Circa(TwistDifference(
                      LinearVelocityDifference::millimeters_per_second({.x = 1, .y = 2, .z = 3}),
                      AngularVelocityDifference::degrees_per_second(
                          {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))));
        }

        SUBCASE("base change - translation")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            FramedTwistDifference const f1{
                TwistDifference(
                    LinearVelocityDifference::millimeters_per_second({.x = 1, .y = 2, .z = 3}),
                    AngularVelocityDifference::degrees_per_second(
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                from_frame};

            BaseChange const bc{.from_frame = from_frame,
                                .to_frame = to_frame,
                                .transformation = SpatialDisplacement(
                                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                                    AngularDisplacement::zero())};
            WARN_NOTHROW(bc * f1);
        }

        SUBCASE("base change - angular")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            FramedTwistDifference const f1{
                TwistDifference(
                    LinearVelocityDifference::millimeters_per_second({.x = 1, .y = 2, .z = 3}),
                    AngularVelocityDifference::degrees_per_second(
                        {.axis = {.x = 0, .y = 0, .z = 1}, .angle = 90})),
                from_frame};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::zero(),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};
            WARN_NOTHROW(bc * f1);
        }

        SUBCASE("base change - transform")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            FramedTwistDifference const f1{
                TwistDifference(
                    LinearVelocityDifference::millimeters_per_second({.x = 1, .y = 2, .z = 3}),
                    AngularVelocityDifference::degrees_per_second(
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                from_frame};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}))};
            WARN_NOTHROW(bc * f1);
        }

        SUBCASE("base change - difference of changed states is changed difference")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedTwist const t1{
                Twist(LinearVelocity::millimeters_per_second({.x = 1, .y = 2, .z = 3}),
                      AngularVelocity::degrees_per_second(
                          {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0})),
                {.name = name, .base_frame = from_frame}};
            FramedTwist const t2{
                Twist(LinearVelocity::millimeters_per_second({.x = 10, .y = 9, .z = 8}),
                      AngularVelocity::degrees_per_second(
                          {.axis = {.x = 0, .y = 1, .z = 0}, .angle = 0})),
                {.name = name, .base_frame = from_frame}};
            FramedTwistDifference const td = t2 - t1;

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};
            auto const t1_new = bc * t1;
            auto const t2_new = bc * t2;
            auto const td_new = t2_new - t1_new;
            WARN_NOTHROW(bc * td == Circa(td_new));
        }
    }

    TEST_CASE("end to end test (see coordinate system visualization)")
    {
        using PoseAccessor = geometry::detail::StateAccessor<Pose>;
        auto const origin =
            FramedPose(Pose(Position::zero(), Orientation::zero()), {"global", "global"});
        auto const F1 = FramedPose(
            PoseAccessor::make(Eigen::Isometry3d(
                (Eigen::Matrix4d() << 0, 0, -1, 3, 0, 1, 0, 3, 1, 0, 0, 0, 0, 0, 0, 1).finished())),
            {"F1", "global"});
        auto const F2 =
            FramedPose(PoseAccessor::make(Eigen::Isometry3d(
                           (Eigen::Matrix4d() << 0, -1, 0, 13, 1, 0, 0, 3, 0, 0, 1, 0, 0, 0, 0, 1)
                               .finished())),
                       {"F2", "global"});
        auto const T1 = FramedTwist(
            Twist(LinearVelocity::millimeters_per_second({1, 1, 0}),
                  AngularVelocity::degrees_per_second({.axis = {1, 0, 0}, .angle = 180})),
            {"T1", "global"});
        auto const T2 =
            FramedTwist(Twist(LinearVelocity::millimeters_per_second({-1, 0, 1}),
                              AngularVelocity::degrees_per_second(
                                  {.axis = {0, 1 / sqrt(2), 1 / sqrt(2)}, .angle = 180})),
                        {"T1", "global"});

        // These values are obtained from "intuition", i.e., they do not correspond to the
        // mathematically correct values. For an explanation, see the coordinate system and
        // Modern Robotics, Chapter 3.
        auto const T1_in_F1 = FramedTwist(
            Twist(LinearVelocity::millimeters_per_second({0, 1, -1}),
                  AngularVelocity::degrees_per_second({.axis = {0, 0, -1}, .angle = 180})),
            {"T1", "F1"});
        auto const T2_in_F1 =
            FramedTwist(Twist(LinearVelocity::millimeters_per_second({1, 0, 1}),
                              AngularVelocity::degrees_per_second(
                                  {.axis = {1 / sqrt(2), 1 / sqrt(2), 0}, .angle = 180})),
                        {"T1", "F1"});

        auto const T1_in_F2 = FramedTwist(
            Twist(LinearVelocity::millimeters_per_second({1, -1, 0}),
                  AngularVelocity::degrees_per_second({.axis = {0, -1, 0}, .angle = 180})),
            {"T1", "F2"});
        auto const T2_in_F2 =
            FramedTwist(Twist(LinearVelocity::millimeters_per_second({0, 1, 1}),
                              AngularVelocity::degrees_per_second(
                                  {.axis = {1 / sqrt(2), 0, 1 / sqrt(2)}, .angle = 180})),
                        {"T1", "F2"});

        auto const F1_to_F2 = SpatialDisplacement(PoseAccessor::make(Eigen::Isometry3d(
            (Eigen::Matrix4d() << 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, -10, 0, 0, 0, 1).finished())));
        auto const base_change = BaseChange("F1", "F2", F1_to_F2);

        SUBCASE("poses and positions transform correctly")
        {
            auto make_base_change = [](FramedPose const& from, FramedPose const& to)
            { return BaseChange(from.get_name(), to.get_name(), (to - from).get_framed_object()); };
            auto const origin_to_F1 = make_base_change(origin, F1);
            auto const origin_to_F2 = make_base_change(origin, F2);
            auto test = [](BaseChange const& bc, FramedTwist const& from, FramedTwist const& to)
            {
                auto const from_in_to = bc * from;
                auto const lv_from_in_to = bc * from.linear();
                CHECK(from_in_to.get_framed_object().angular() ==
                      Circa(to.get_framed_object().angular()));
                CHECK(lv_from_in_to.get_framed_object() == Circa(to.get_framed_object().linear()));
            };
            test(origin_to_F1, T1, T1_in_F1);
            test(origin_to_F1, T2, T2_in_F1);
            test(origin_to_F2, T1, T1_in_F2);
            test(origin_to_F2, T2, T2_in_F2);
            test(base_change, T1_in_F1, T1_in_F2);
            test(base_change, T2_in_F1, T2_in_F2);
        }
    }

    TEST_CASE("Modern Robotics Examples and Exercises")
    {
        SUBCASE("Example 3.23 from Modern Robotics.")
        {
            // Transform from frame S to frame B
            SpatialDisplacement const T_sb =
                geometry::detail::DifferenceAccessor<SpatialDisplacement>::make(Eigen::Isometry3d(
                    (Eigen::Matrix4d() << -1, 0, 0, 4, 0, 1, 0, 0.4, 0, 0, -1, 0, 0, 0, 0, 1)
                        .finished()));
            FramedTwist const V_s(Twist(LinearVelocity::meters_per_second({-2, -4, 0}),
                                        AngularVelocity::radians_per_second(Vector{0, 0, 2})),
                                  {"Car", "S"});
            FramedTwist const V_b(Twist(LinearVelocity::meters_per_second({2.8, 4, 0}),
                                        AngularVelocity::radians_per_second(Vector{0, 0, -2})),
                                  {"Car", "B"});
            auto from_B_to_S = BaseChange("B", "S", T_sb.inverse());
            CHECK(V_s == Circa(from_B_to_S * V_b));
        }
        SUBCASE("Exercise 3.16 from Modern Robotics")
        {
            FramedTwist const V_s(Twist(LinearVelocity::meters_per_second({-1, -2, -3}),
                                        AngularVelocity::radians_per_second(Vector{3, 2, 1})),
                                  {"Object", "S"});
            Eigen::Isometry3d T(
                (Eigen::Matrix4d() << 0, 0, 1, 0, -1, 0, 0, 3, 0, -1, 0, 0, 0, 0, 0, 1).finished());
            SpatialDisplacement const T_sa =
                geometry::detail::DifferenceAccessor<SpatialDisplacement>::make(T.inverse());
            FramedTwist const V_a(Twist(LinearVelocity::meters_per_second({-9, 1, -1}),
                                        AngularVelocity::radians_per_second(Vector{1, -3, -2})),
                                  {"Object", "A"});

            Eigen::Matrix4d V =
                (Eigen::Matrix4d() << 0, -1, 2, -1, 1, 0, -3, -2, -2, 3, 0, -3, 0, 0, 0, 0)
                    .finished();
            auto const base_change = BaseChange("S", "A", T_sa);
            CHECK(V_a == Circa(base_change * V_s));
            CAPTURE((T * V * T.inverse()).matrix());
            CHECK((framed_geometry::SkewSymmetric6d(V_a).matrix() - (T * V * T.inverse()).matrix())
                      .isZero());
        }
        SUBCASE("Practice Exercise 3.14")
        {
            // https://hades.mech.northwestern.edu/images/e/ef/MR_practice_exercises.pdf
            FramedPose tree(Pose(Position::zero(), Orientation::zero()), {"Tree", "Tree"});
            auto const quadcopter =
                tree.enframe(Pose(Position::meters({10, 5, 5}),
                                  Orientation::degrees({.axis = {1, 0, 0}, .angle = 90})),
                             "Quadcopter");
            auto const house =
                tree.enframe(Pose(Position::meters({0, 10, 10}), Orientation::zero()), "House");
            auto const tree_to_quadcopter =
                BaseChange("Tree", "Quadcopter", (quadcopter - tree).get_framed_object());
            auto const quadcopter_to_tree =
                BaseChange("Quadcopter", "Tree", (tree - quadcopter).get_framed_object());
            auto const tree_to_house =
                BaseChange("Tree", "House", (house - tree).get_framed_object());
            auto const house_to_tree =
                BaseChange("House", "Tree", (tree - house).get_framed_object());
            auto const quadcopter_to_house =
                BaseChange("Quadcopter", "House", (house - quadcopter).get_framed_object());
            auto const house_to_quadcopter =
                BaseChange("House", "Quadcopter", (quadcopter - house).get_framed_object());
            auto const V_qc_in_qc =
                FramedTwist(Twist(LinearVelocity::meters_per_second({0, 1, 0}),
                                  AngularVelocity::radians_per_second({.x = 0, .y = 1, .z = 0})),
                            {"Quadcopter", "Quadcopter"});
            auto const V_qc_in_t =
                FramedTwist(Twist(LinearVelocity::meters_per_second({5, -10, 1}),
                                  AngularVelocity::radians_per_second({.x = 0, .y = 0, .z = 1})),
                            {"Quadcopter", "Tree"});
            auto const V_qc_in_h =
                FramedTwist(Twist(LinearVelocity::meters_per_second({-5, -10, 1}),
                                  AngularVelocity::radians_per_second({.x = 0, .y = 0, .z = 1})),
                            {"Quadcopter", "House"});
            CHECK(V_qc_in_t == Circa(quadcopter_to_tree * V_qc_in_qc));
            CHECK(V_qc_in_h == Circa(quadcopter_to_house * V_qc_in_qc));
            CHECK(V_qc_in_h == Circa(tree_to_house * V_qc_in_t));
            CHECK(V_qc_in_t == Circa(house_to_tree * V_qc_in_h));
            CHECK(V_qc_in_qc == Circa(house_to_quadcopter * V_qc_in_h));
            CHECK(V_qc_in_qc == Circa(tree_to_quadcopter * V_qc_in_t));
            CHECK(V_qc_in_h == Circa(tree_to_house * (quadcopter_to_tree * V_qc_in_qc)));
            CHECK(V_qc_in_t == Circa(house_to_tree * (quadcopter_to_house * V_qc_in_qc)));
        }
    }
}