#pragma once

#include <quant/framed_geometry.h>
#include <quant/units.h>

#include <doctest/doctest.h>

#include <iostream>

using namespace quant;  // NOLINT

TEST_CASE("testing basic constructions")
{
    Position d;  // Dummy.

    Framed<Position> const f1{d, {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};

    CHECK(f1.get_name() == "TCP");
    CHECK(f1.get_base_frame() == "ARMAR-6::RobotRoot");

    Framed<Position> const f2{d, {.name = "CoM", .base_frame = "ARMAR-6::RobotRoot"}};

    CHECK(f2.get_name() == "CoM");
    CHECK(f2.get_base_frame() == "ARMAR-6::RobotRoot");
}

TEST_CASE("testing enframing")
{
    LinearDisplacement const p = LinearDisplacement::zero();

    Framed<LinearDisplacement> const origin{p, {.name = "::Origin", .base_frame = ""}};

    CHECK(origin.get_name() == "::Origin");
    CHECK(origin.get_base_frame() == "");

    Framed<LinearDisplacement> const robot_root =
        origin.enframe(LinearDisplacement::meters({.x = 1}), "ARMAR-6::RobotRoot");

    CHECK(robot_root.get_name() == "ARMAR-6::RobotRoot");
    CHECK(robot_root.get_base_frame() == "::Origin");

    Framed<LinearDisplacement> const right_hand_tcp = robot_root.enframe(
        LinearDisplacement::meters({.x = 0.3, .y = 0.5, .z = 1.8}), "ARMAR-6::TCP_R");

    CHECK(right_hand_tcp.get_name() == "ARMAR-6::TCP_R");
    CHECK(right_hand_tcp.get_base_frame() == "ARMAR-6::RobotRoot");

    Framed<LinearDisplacement> const right_hand_com = robot_root.enframe(
        LinearDisplacement::meters({.x = 0.32, .y = 0.5, .z = 1.79}), "ARMAR-6::CoM_R");

    CHECK(right_hand_com.get_name() == "ARMAR-6::CoM_R");
    CHECK(right_hand_com.get_base_frame() == "ARMAR-6::RobotRoot");
}

TEST_CASE("testing basic framed differences")
{
    SUBCASE("testing framed difference with Position")
    {
        Position const p = Position::zero();  // Dummy position.

        Framed<Position> const tcp{p, {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
        Framed<Position> const com{p, {.name = "CoM", .base_frame = "ARMAR-6::RobotRoot"}};

        Framed<LinearDisplacement> const ld = tcp - com;

        CHECK(ld.get_name() == "TCP");
        CHECK(ld.get_base_frame() == "ARMAR-6::RobotRoot");
    }

    SUBCASE("testing framed difference with Orientation")
    {
        Orientation const p = Orientation::zero();  // Dummy orientation.

        Framed<Orientation> const tcp{p, {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
        Framed<Orientation> const com{p, {.name = "CoM", .base_frame = "ARMAR-6::RobotRoot"}};

        // Framed<AngularDisplacement> const ad = tcp - com;

        // CHECK(ad.get_name() == "TCP");
        // CHECK(ad.get_base_frame() == "ARMAR-6::RobotRoot");
    }

    SUBCASE("testing framed difference with Pose")
    {
        Pose const p = Pose::zero();  // Dummy pose.

        Framed<Pose> const tcp{p, {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
        Framed<Pose> const com{p, {.name = "CoM", .base_frame = "ARMAR-6::RobotRoot"}};

        // Framed<SpatialDisplacement> const sd = tcp - com;

        // CHECK(sd.get_name() == "TCP");
        // CHECK(sd.get_base_frame() == "ARMAR-6::RobotRoot");
    }
}
