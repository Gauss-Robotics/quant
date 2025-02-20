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
            FramedForce const f2 = FramedForce::zero({"::", "::"});
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

    TEST_CASE("testing framed force differences")
    {
        SUBCASE("construction")
        {
            FramedForceDifference const f1{ForceDifference::newtons({.x = 1, .y = 0, .z = 0}),
                                           "ARMAR-6::RobotRoot"};
            FramedForceDifference const f2 = FramedForceDifference::zero("::");
            FramedForceDifference const f3{f1};

            CHECK(f1.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(f1.get_framed_object() ==
                  Circa(ForceDifference::newtons({.x = 1, .y = 0, .z = 0})));

            CHECK(f2.get_base_frame() == "::");
            CHECK(f2.get_framed_object() == Circa(ForceDifference::zero()));

            CHECK(f3.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(f3.get_framed_object() ==
                  Circa(ForceDifference::newtons({.x = 1, .y = 0, .z = 0})));
        }

        SUBCASE("addition from right to state")
        {
            FramedForce const force{Force::newtons({.x = 1, .y = 0, .z = 0}),
                                    {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedForceDifference const fd{ForceDifference::newtons({.x = 0, .y = 1, .z = 0}),
                                           "TCP"};
            FramedForceDifference const fd_wrong_frame{
                ForceDifference::newtons({.x = 0, .y = 1, .z = 0}), "ARMAR-6::PlatformBase"};

            auto const new_force = force + fd;
            CHECK(new_force.get_name() == "TCP");
            CHECK(new_force.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(new_force.get_framed_object() == Circa(Force::newtons({.x = 1, .y = 1, .z = 0})));

            std::string const exception_message =
                "Frame mismatch: TCP vs ARMAR-6::PlatformBase";
            CHECK_THROWS_WITH(force + fd_wrong_frame, exception_message.c_str());
        }

        SUBCASE("base change - translation")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            FramedForceDifference const f1{ForceDifference::newtons({.x = 1, .y = 0, .z = 0}),
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
            FramedForceDifference const f1{ForceDifference::newtons({.x = 1, .y = 0, .z = 0}),
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
            FramedForceDifference const f1{ForceDifference::newtons({.x = 1, .y = 0, .z = 0}),
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
            FramedForce const f1{Force::newtons({.x = 1, .y = 0, .z = 0}),
                                 {.name = name, .base_frame = from_frame}};
            FramedForce const f2{Force::newtons({.x = 0, .y = 1, .z = 0}),
                                 {.name = name, .base_frame = from_frame}};
            FramedForceDifference const fd = f2 - f1;

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 0, .y = 0, .z = 1}, .angle = 90}))};
            auto const f1_new = bc * f1;
            auto const f2_new = bc * f2;
            auto const fd_new = f2_new - f1_new;
            WARN_NOTHROW(bc * fd == Circa(fd_new));
            WARN_NOTHROW(f1_new + (bc * fd) == Circa(f2_new));
        }
    }

    TEST_CASE("testing framed torques")
    {
        SUBCASE("construction")
        {
            FramedTorque const t1{
                Torque::newton_meters({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedTorque const t2 = FramedTorque::zero({"::", "::"});
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
                      {.axis = {.x = -1 / sqrt(2), .y = 1 / sqrt(2), .z = 0},
                       .angle = sqrt(2) * 90})));
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

    TEST_CASE("testing framed torque differences")
    {
        SUBCASE("construction")
        {
            FramedTorqueDifference const t1{
                TorqueDifference::newton_meters({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                "ARMAR-6::RobotRoot"};
            FramedTorqueDifference const t2 = FramedTorqueDifference::zero("::");
            FramedTorqueDifference const t3{t1};

            CHECK(t1.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(t1.get_framed_object() == Circa(TorqueDifference::newton_meters(
                                                {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})));

            CHECK(t2.get_base_frame() == "::");
            CHECK(t2.get_framed_object() == Circa(TorqueDifference::zero()));

            CHECK(t3.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(t3.get_framed_object() == Circa(TorqueDifference::newton_meters(
                                                {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})));
        }

        SUBCASE("addition from right to state")
        {
            FramedTorque const torque{
                Torque::newton_meters({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedTorqueDifference const td{
                TorqueDifference::newton_meters({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}),
                "TCP"};
            FramedTorqueDifference const td_wrong_frame{
                TorqueDifference::newton_meters({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}),
                "ARMAR-6::PlatformBase"};

            auto const new_torque = torque + td;
            CHECK(new_torque.get_name() == "TCP");
            CHECK(new_torque.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(new_torque.get_framed_object() ==
                  Circa(Torque::newton_meters(
                      {.axis = {.x = 1, .y = 1, .z = 0}, .angle = sqrt(2) * 90})));

            std::string const exception_message =
                "Frame mismatch: TCP vs ARMAR-6::PlatformBase";
            CHECK_THROWS_WITH(torque + td_wrong_frame, exception_message.c_str());
        }

        SUBCASE("base change - translation")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            FramedTorqueDifference const t1{
                TorqueDifference::newton_meters({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                from_frame};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0}))};
            WARN_NOTHROW(bc * t1);
        }

        SUBCASE("base change - angular")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            FramedTorqueDifference const t1{
                TorqueDifference::newton_meters({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                from_frame};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::zero(),
                    AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}))};
            WARN_NOTHROW(bc * t1);
        }

        SUBCASE("base change - transform")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            FramedTorqueDifference const t1{
                TorqueDifference::newton_meters({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                from_frame};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}))};
            WARN_NOTHROW(bc * t1);
        }

        SUBCASE("base change - difference of changed states is changed difference")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedTorque const t1{
                Torque::newton_meters({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                {.name = name, .base_frame = from_frame}};
            FramedTorque const t2{
                Torque::newton_meters({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}),
                {.name = name, .base_frame = from_frame}};
            FramedTorqueDifference const td = t2 - t1;

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 0, .y = 0, .z = 1}, .angle = 90}))};
            auto const t1_new = bc * t1;
            auto const t2_new = bc * t2;
            auto const td_new = t2_new - t1_new;
            WARN_NOTHROW(bc * td == Circa(td_new));
            WARN_NOTHROW(t1_new + (bc * td) == Circa(t2_new));
        }
    }

    TEST_CASE("testing framed wrenches")
    {
        SUBCASE("construction")
        {
            FramedWrench const w1{
                Wrench(Force::newtons({.x = 1, .y = 2, .z = 3}),
                       Torque::newton_meters({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedWrench const w2 = FramedWrench::zero({"::", "::"});
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
                            Force::newtons({.x = 1, .y = 2, .z = 3}),
                            Torque::newton_meters({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                        1e-3));
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
                            Force::newtons({.x = 1, .y = 3, .z = -2}),
                            Torque::newton_meters({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                        1e-3));
        }
    }

    TEST_CASE("testing framed wrench differences")
    {
        SUBCASE("construction")
        {
            FramedWrenchDifference const w1{
                WrenchDifference(ForceDifference::newtons({.x = 1, .y = 2, .z = 3}),
                                 TorqueDifference::newton_meters(
                                     {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                "ARMAR-6::RobotRoot"};
            FramedWrenchDifference const w2 = FramedWrenchDifference::zero("::");
            FramedWrenchDifference const w3{w1};

            CHECK(w1.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(w1.get_framed_object() ==
                  Circa(WrenchDifference(ForceDifference::newtons({.x = 1, .y = 2, .z = 3}),
                                         TorqueDifference::newton_meters(
                                             {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))));

            CHECK(w2.get_base_frame() == "::");
            CHECK(w2.get_framed_object() == Circa(WrenchDifference::zero()));

            CHECK(w3.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(w3.get_framed_object() ==
                  Circa(WrenchDifference(ForceDifference::newtons({.x = 1, .y = 2, .z = 3}),
                                         TorqueDifference::newton_meters(
                                             {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))));
        }

        SUBCASE("base change - translation")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            FramedWrenchDifference const w1{
                WrenchDifference(ForceDifference::newtons({.x = 1, .y = 2, .z = 3}),
                                 TorqueDifference::newton_meters(
                                     {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                from_frame};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0}))};
            WARN_NOTHROW(bc * w1);
        }

        SUBCASE("base change - angular")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            FramedWrenchDifference const w1{
                WrenchDifference(ForceDifference::newtons({.x = 1, .y = 2, .z = 3}),
                                 TorqueDifference::newton_meters(
                                     {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                from_frame};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::zero(),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};
            WARN_NOTHROW(bc * w1);
        }

        SUBCASE("base change - transform")
        { // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            FramedWrenchDifference const w1{
                WrenchDifference(ForceDifference::newtons({.x = 1, .y = 2, .z = 3}),
                                 TorqueDifference::newton_meters(
                                     {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                from_frame};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}))};
            WARN_NOTHROW(bc * w1);
        }

        SUBCASE("base change - difference of changed states is changed difference")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedWrench const w1{
                Wrench(Force::newtons({.x = 1, .y = 2, .z = 3}),
                       Torque::newton_meters({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                {.name = from_frame, .base_frame = from_frame}};
            FramedWrench const w2{
                Wrench(Force::newtons({.x = 10, .y = 9, .z = 8}),
                       Torque::newton_meters({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90})),
                {.name = name, .base_frame = from_frame}};
            FramedWrenchDifference const wd = w2 - w1;

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};
            auto const w1_new = bc * w1;
            auto const w2_new = bc * w2;
            auto const wd_new = w2_new - w1_new;
            WARN_NOTHROW(bc * wd == Circa(wd_new));
            WARN_NOTHROW(w1_new + (bc * wd) == Circa(w2_new));
        }
    }

    TEST_CASE("Examples and Exercises from Modern Robotics")
    {
        SUBCASE("Example 3.28 Modern Robotics")
        {
            // https://hades.mech.northwestern.edu/images/0/0c/MR-tablet-v2.pdf
            FramedWrench const F_hand_in_H{
                Wrench(Force::newtons({.x = 0, .y = -5, .z = 0}), Torque::zero()),
                {.name = "Hand", .base_frame = "H"}};
            FramedWrench const F_apple_in_A{
                Wrench(Force::newtons({.x = 0, .y = 0, .z = 1}), Torque::zero()),
                {.name = "Apple", .base_frame = "A"}};
            SpatialDisplacement const T_hf{LinearDisplacement::meters({-0.1, 0, 0}),
                                           AngularDisplacement::zero()};
            SpatialDisplacement const T_af{
                LinearDisplacement::meters({-0.25, 0, 0}),
                AngularDisplacement::degrees({.axis = {1, 0, 0}, .angle = -90})};

            auto const from_H_to_F = BaseChange{"H", "F", T_hf};
            auto const from_A_to_F = BaseChange{"A", "F", T_af};
            auto const F_apple_in_F = from_A_to_F * F_apple_in_A;
            auto const F_hand_in_F = from_H_to_F * F_hand_in_H;
            auto const F_f = F_hand_in_F + F_apple_in_F;
            CHECK(F_apple_in_F ==
                  Circa(FramedWrench(Wrench(Force::newtons({0, -1, 0}),
                                            Torque::newton_meters({.x = 0, .y = 0, .z = -0.25})),
                                     {.name = "Apple", .base_frame = "F"})));
            CHECK(F_hand_in_F ==
                  Circa(FramedWrench(Wrench(Force::newtons({0, -5, 0}),
                                            Torque::newton_meters({.x = 0, .y = 0, .z = -0.5})),
                                     {.name = "Hand", .base_frame = "F"})));
            CHECK(F_f ==
                  Circa(FramedWrench(Wrench(Force::newtons({0, -6, 0}),
                                            Torque::newton_meters({.x = 0, .y = 0, .z = -0.75})),
                                     {.name = "Hand", .base_frame = "F"})));
        }
        SUBCASE("Practice Exercise 3.16")
        {
            // https://hades.mech.northwestern.edu/images/e/ef/MR_practice_exercises.pdf
            auto const F_b = FramedWrench(Wrench(Force::newtons({-100, 0, -500}),
                                                 Torque::newton_meters({.x = 0, .y = 0, .z = 0})),
                                          {.name = "Branch", .base_frame = "B"});
            auto const F_t =
                FramedWrench(Wrench(Force::newtons({0, 100, -500}),
                                    Torque::newton_meters({.x = -800, .y = 1000, .z = 200})),
                             {.name = "Branch", .base_frame = "T"});
            auto const base_change = BaseChange{
                "B",
                "T",
                SpatialDisplacement(LinearDisplacement::meters({2, 1, 3}),
                                    AngularDisplacement::degrees({.axis = {0, 0, 1}, .angle = -90}))
                    .inverse()};
            for (int i = 0; i < 100; ++i)
            {
                // Test numerical stability
                CHECK(base_change * F_b == Circa(F_t));
            }
        }
        SUBCASE("Final Exam 2017 Exercise 5c")
        {
            // https://hades.mech.northwestern.edu/images/2/28/SNU-2017-exams.pdf
            auto const F_b = FramedWrench(Wrench(Force::newtons({2, 1, 1}), Torque::zero()),
                                          {.name = "Base", .base_frame = "B"});
            SpatialDisplacement const T_sb{
                LinearDisplacement::meters({3, 3, 4}),
                AngularDisplacement::degrees({.axis = {0, 1, 0}, .angle = -90})};
            auto const from_B_to_S = BaseChange{"B", "S", T_sb.inverse()};
            auto const F_s = FramedWrench(Wrench(Force::newtons({-1, 1, 2}),
                                                 Torque::newton_meters({.x = 2, .y = -10, .z = 6})),
                                          {.name = "Base", .base_frame = "S"});
            FramedForce const f_b =
                FramedForce(Force::newtons({2, 1, 1}), {.name = "Base", .base_frame = "B"});
            CHECK(from_B_to_S * f_b == Circa(FramedForce(Force::newtons({-1, 1, 2}),
                                                         {.name = "Base", .base_frame = "S"})));

            CHECK(F_s == Circa(from_B_to_S * F_b));
        }
    }
}
