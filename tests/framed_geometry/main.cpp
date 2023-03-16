#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>

#include <doctest/doctest.h>

#include <quant/framed_geometry.h>
#include <quant/units.h>


const double Precision = 1e-6;

using namespace quant;


TEST_CASE("testing framed_geometry")
{
    const FrameID fid{.agent = "ARMAR-6", .frame = "RobotRoot"};

    SUBCASE("testing FrameID")
    {
        CHECK(fid.agent == "ARMAR-6");
        CHECK(fid.frame == "RobotRoot");

        CHECK(fid.toString() == "ARMAR-6::RobotRoot");

        const FrameID fid2{.agent = "ARMAR-6", .frame = "RobotRoot"};

        CHECK(fid == fid2);

        const FrameID fid3{.agent = "ARMAR-6", .frame = "DepthCamera"};

        CHECK(fid != fid3);

        const FrameID fid4{.agent = "ARMAR-7", .frame = "RobotRoot"};

        CHECK(fid != fid4);
    }

    Framed<Position> p1{fid};
    Difference<Framed<Position>> d1 = p1 - p1;

    SUBCASE("testing framed custom type")
    {

    }
}
