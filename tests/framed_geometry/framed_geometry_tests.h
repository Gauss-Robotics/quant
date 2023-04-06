#pragma once

#include <quant/framed_geometry.h>
#include <quant/units.h>

#include <doctest/doctest.h>

#include <iostream>

using namespace quant;  // NOLINT

TEST_CASE("testing basic constructions")
{
    void* d = nullptr;  // Dummy.

    Framed<void*> const f1{d, {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};

    CHECK(f1.name == "TCP");
    CHECK(f1.base_frame == "ARMAR-6::RobotRoot");

    Framed<void*> const f2{d, {.name = "CoM", .base_frame = "ARMAR-6::RobotRoot"}};

    CHECK(f2.name == "CoM");
    CHECK(f2.base_frame == "ARMAR-6::RobotRoot");
}

TEST_CASE("testing enframing")
{
    Position const p = Position::zero();

    Framed<Position> const origin{p, {.name = "::Origin", .base_frame = ""}};

    CHECK(origin.name == "::Origin");
    CHECK(origin.base_frame == "");

    Framed<Position> const robot_root =
        origin.enframe(Position::meters({.x = 1}), "ARMAR-6::RobotRoot");

    CHECK(robot_root.name == "ARMAR-6::RobotRoot");
    CHECK(robot_root.base_frame == "::Origin");

    Framed<Position> const right_hand_tcp =
        robot_root.enframe(Position::meters({.x = 0.3, .y = 0.5, .z = 1.8}), "ARMAR-6::TCP_R");

    CHECK(right_hand_tcp.name == "ARMAR-6::TCP_R");
    CHECK(right_hand_tcp.base_frame == "ARMAR-6::RobotRoot");

    Framed<Position> const right_hand_com =
        robot_root.enframe(Position::meters({.x = 0.32, .y = 0.5, .z = 1.79}), "ARMAR-6::CoM_R");

    CHECK(right_hand_com.name == "ARMAR-6::CoM_R");
    CHECK(right_hand_com.base_frame == "ARMAR-6::RobotRoot");
}

TEST_CASE("testing basic framed differences")
{
    SUBCASE("testing framed difference with Position")
    {
        Position const p = Position::zero();  // Dummy position.

        Framed<Position> const tcp{p, {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
        Framed<Position> const com{p, {.name = "CoM", .base_frame = "ARMAR-6::RobotRoot"}};

        Framed<LinearDisplacement> const ld = tcp - com;

        CHECK(ld.name == "TCP");
        CHECK(ld.base_frame == "CoM");
    }

    SUBCASE("testing framed difference with Orientation")
    {
        Orientation const p = Orientation::zero();  // Dummy orientation.

        Framed<Orientation> const tcp{p, {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
        Framed<Orientation> const com{p, {.name = "CoM", .base_frame = "ARMAR-6::RobotRoot"}};

        // Framed<AngularDisplacement> const ad = tcp - com;

        // CHECK(ad.baseFrame == "ARMAR-6::RobotRoot");
    }

    SUBCASE("testing framed difference with Pose")
    {
        Pose const p = Pose::zero();  // Dummy pose.

        Framed<Pose> const tcp{p, {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
        Framed<Pose> const com{p, {.name = "CoM", .base_frame = "ARMAR-6::RobotRoot"}};

        // Framed<SpatialDisplacement> const sd = tcp - com;

        // CHECK(sd.baseFrame == "ARMAR-6::RobotRoot");
    }
}
