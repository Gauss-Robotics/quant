#include "SimpleRobot.h"

using namespace simple_robot_example;

int
main(int argc, char* argv[])
{
    quant::FramedSpatialDisplacement origin(quant::SpatialDisplacement(), {.name = "::Origin"});
    SimpleRobot robot{origin};

    return 0;
}
