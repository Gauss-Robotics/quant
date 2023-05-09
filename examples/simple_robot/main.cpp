#include "SimpleRobot.h"

using namespace simple_robot_example;  // NOLINT

int
main(int argc, char* argv[])  // NOLINT
{
    // Initialize robot.
    quant::FramedSpatialDisplacement origin(
        quant::SpatialDisplacement(
            quant::Pose(quant::Position::millimeters({.x = 100}),
                        quant::Orientation::radians({.axis = {.y = 1}, .angle = 3.}))),
        {.name = "::Origin"});
    SimpleRobot robot{origin};

    // Detect an object on the table.
    quant::FramedPose const table = origin.enframe(quant::Pose(), "table");
    robot.look_at(table);
    quant::FramedPose const object = robot.detect_object();

    // Grasp an object.
    robot.grasp(object);

    return 0;
}
