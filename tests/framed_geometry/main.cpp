#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN


#include <quant/framed_geometry.h>
#include <quant/units.h>

#include <doctest/doctest.h>

#include <iostream>


using namespace quant;

TEST_CASE("testing basic constructions")
{
    Framed<void*> const f1{{.name = "TCP", .baseFrame = "ARMAR-6::RobotRoot"}};

    CHECK(f1.name == "TCP");
    CHECK(f1.baseFrame == "ARMAR-6::RobotRoot");

    Framed<void*> const f2{{.name = "CoM", .baseFrame = "ARMAR-6::RobotRoot"}};

    CHECK(f2.name == "CoM");
    CHECK(f2.baseFrame == "ARMAR-6::RobotRoot");
}

TEST_CASE("testing basic framed differences")
{
    SUBCASE("testing framed difference with Position")
    {
        Position const pos = Position::Origin();  // Example data type, could be anything.

        Framed<Position> const tcp{{.name = "TCP", .baseFrame = "ARMAR-6::RobotRoot"}};
        Framed<Position> const com{{.name = "CoM", .baseFrame = "ARMAR-6::RobotRoot"}};

        Framed<LinearDisplacement> const ld = tcp - com;

        CHECK(ld.name == "TCP");
        CHECK(ld.baseFrame == "CoM");
    }

    SUBCASE("testing framed difference with Orientation")
    {
        Framed<Orientation> const tcp{{.name = "TCP", .baseFrame = "ARMAR-6::RobotRoot"}};
        Framed<Orientation> const com{{.name = "CoM", .baseFrame = "ARMAR-6::RobotRoot"}};

        // Framed<AngularDisplacement> const ad = tcp - com;

        // CHECK(ad.baseFrame == "ARMAR-6::RobotRoot");
    }

    SUBCASE("testing framed difference with Pose")
    {
        Framed<Pose> const tcp{{.name = "TCP", .baseFrame = "ARMAR-6::RobotRoot"}};
        Framed<Pose> const com{{.name = "CoM", .baseFrame = "ARMAR-6::RobotRoot"}};

        // Framed<SpatialDisplacement> const sd = tcp - com;

        // CHECK(sd.baseFrame == "ARMAR-6::RobotRoot");
    }
}
