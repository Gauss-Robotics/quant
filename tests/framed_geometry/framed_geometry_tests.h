#pragma once

#include <quant/framed_geometry.h>
#include <quant/units.h>

#include <doctest/doctest.h>

#include <iostream>

using namespace quant;

TEST_CASE("testing basic constructions")
{
    void* d = nullptr;  // Dummy.

    Framed<void*> const f1{d, {.name = "TCP", .baseFrame = "ARMAR-6::RobotRoot"}};

    CHECK(f1.name == "TCP");
    CHECK(f1.baseFrame == "ARMAR-6::RobotRoot");

    Framed<void*> const f2{d, {.name = "CoM", .baseFrame = "ARMAR-6::RobotRoot"}};

    CHECK(f2.name == "CoM");
    CHECK(f2.baseFrame == "ARMAR-6::RobotRoot");
}

TEST_CASE("testing enframing")
{
    Position const p = Position::zero();

    Framed<Position> const origin{p, {.name = "::Origin", .baseFrame = ""}};

    CHECK(origin.name == "::Origin");
    CHECK(origin.baseFrame == "");

    Framed<Position> const robotRoot =
        origin.enframe(Position::meters({.x = 1}), "ARMAR-6::RobotRoot");

    CHECK(robotRoot.name == "ARMAR-6::RobotRoot");
    CHECK(robotRoot.baseFrame == "::Origin");

    Framed<Position> const rightHandTcp =
        robotRoot.enframe(Position::meters({.x = 0.3, .y = 0.5, .z = 1.8}), "ARMAR-6::TCP_R");

    CHECK(rightHandTcp.name == "ARMAR-6::TCP_R");
    CHECK(rightHandTcp.baseFrame == "ARMAR-6::RobotRoot");

    Framed<Position> const rightHandCom =
        robotRoot.enframe(Position::meters({.x = 0.32, .y = 0.5, .z = 1.79}), "ARMAR-6::CoM_R");

    CHECK(rightHandCom.name == "ARMAR-6::CoM_R");
    CHECK(rightHandCom.baseFrame == "ARMAR-6::RobotRoot");
}

TEST_CASE("testing basic framed differences")
{
    SUBCASE("testing framed difference with Position")
    {
        Position const p = Position::zero();  // Dummy position.

        Framed<Position> const tcp{p, {.name = "TCP", .baseFrame = "ARMAR-6::RobotRoot"}};
        Framed<Position> const com{p, {.name = "CoM", .baseFrame = "ARMAR-6::RobotRoot"}};

        Framed<LinearDisplacement> const ld = tcp - com;

        CHECK(ld.name == "TCP");
        CHECK(ld.baseFrame == "CoM");
    }

    SUBCASE("testing framed difference with Orientation")
    {
        Orientation const p = Orientation::zero();  // Dummy orientation.

        Framed<Orientation> const tcp{p, {.name = "TCP", .baseFrame = "ARMAR-6::RobotRoot"}};
        Framed<Orientation> const com{p, {.name = "CoM", .baseFrame = "ARMAR-6::RobotRoot"}};

        // Framed<AngularDisplacement> const ad = tcp - com;

        // CHECK(ad.baseFrame == "ARMAR-6::RobotRoot");
    }

    SUBCASE("testing framed difference with Pose")
    {
        Pose const p = Pose::zero();  // Dummy pose.

        Framed<Pose> const tcp{p, {.name = "TCP", .baseFrame = "ARMAR-6::RobotRoot"}};
        Framed<Pose> const com{p, {.name = "CoM", .baseFrame = "ARMAR-6::RobotRoot"}};

        // Framed<SpatialDisplacement> const sd = tcp - com;

        // CHECK(sd.baseFrame == "ARMAR-6::RobotRoot");
    }
}
