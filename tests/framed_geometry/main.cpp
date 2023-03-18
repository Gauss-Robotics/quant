#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN


#include <iostream>

#include <doctest/doctest.h>

#include <quant/framed_geometry.h>
#include <quant/units.h>


using namespace quant;


const double Precision = 1e-6;


TEST_CASE("testing basic constructions")
{
    const FrameID fid{"ARMAR-6::RobotRoot"};

    SUBCASE("testing FrameID")
    {
        CHECK(fid.name == "ARMAR-6::RobotRoot");

        const FrameID fid2{"ARMAR-6::RobotRoot"};

        CHECK(fid == fid2);

        const FrameID fid3{"ARMAR-6::DepthCamera"};

        CHECK(fid != fid3);

        const FrameID fid4{"ARMAR-7::RobotRoot"};

        CHECK(fid != fid4);
    }

    SUBCASE("testing with a Position")
    {
        const Framed<Position> p1{fid};
        const Framed<Position> p2{fid};

        const Frame<LinearDisplacement> d1 = p2 - p1;

        CHECK(d1.baseFrame == "ARMAR-6::RobotRoot");
    }

    SUBCASE("testing with a Pose")
    {
        const Framed<Pose> p1{fid};
        const Framed<Pose> p2{fid};
        const Framed<Pose> p3{FrameID{"ARMAR-7::RobotRoot"}};

        const Frame<SpatialDisplacement> d1 = p2 - p1;

        CHECK(d1.baseFrame == "ARMAR-6::RobotRoot");


    }


}
