#include <iostream>>

#include "SimpleRobot.h"

using namespace simple_robot_example;  // NOLINT

int
main(int argc, char* argv[])  // NOLINT
{
    // Transform.
    auto pose = quant::SpatialDisplacement(
        quant::Pose(quant::Position::millimeters({.x = 100}),
                    quant::Orientation::radians({.axis = {.y = 1}, .angle = 3.})));

    // Initialize robot.
    quant::FramedSpatialDisplacement origin(pose, {.name = "::Origin"});

    SimpleRobot robot{origin};

    std::cout << "Robot placed at: " << origin << std::endl;

    // Detect an object on the table.
    quant::FramedPose const table = origin.enframe(quant::Pose(), "table");
    robot.look_at(table);

    std::cout << "Robot looking at: " << table << std::endl;

    quant::FramedPose const object = robot.detect_object();

    std::cout << "Robot detected object at: " << object << std::endl;

    // Grasp an object.
    robot.grasp(object);

    return 0;
}
