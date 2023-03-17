#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>

#include <doctest/doctest.h>

#include <quant/framed_geometry.h>
#include <quant/units.h>


const double Precision = 1e-6;

using namespace quant;


TEST_CASE("testing framed_geometry")
{
    const FrameID<> fid{.frame = "ARMAR-6::RobotRoot"};

    SUBCASE("testing FrameID")
    {
        CHECK(fid.frame == "ARMAR-6::RobotRoot");

        CHECK(fid.toString() == "ARMAR-6::RobotRoot");

        const FrameID<> fid2{.frame = "ARMAR-6::RobotRoot"};

        CHECK(fid == fid2);

        const FrameID<> fid3{.frame = "ARMAR-6::DepthCamera"};

        CHECK(fid != fid3);

        const FrameID<> fid4{.frame = "ARMAR-7::RobotRoot"};

        CHECK(fid != fid4);
    }

    Framed<Position> p1{fid};
    Framed<Position> p2{fid};

    Frame<Displacement> d1 = p2 - p1;

    SUBCASE("testing framed custom type")
    {
        CHECK(d1.baseFrame_.toString() == "ARMAR-6::RobotRoot");
    }
}
