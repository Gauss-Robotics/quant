#include <iostream>

#include "SimpleRobot.h"

using namespace simple_robot_example;  // NOLINT

int
main(int argc, char* argv[])  // NOLINT
{
    using namespace quant;

    // Initialize robot.
    FramedPose origin(Pose(), {.name = "Origin"});

    std::cout << "Info: " << origin << std::endl;

    SimpleRobot robot{origin};

    std::cout << "Robot location: " << robot.root << std::endl;

    // Detect an object on the table.
    FramedPose const table = origin.enframe(Pose(Position::millimeters({.x = 300, .y = 430}),
                                                 Orientation::radians(AxisAngle::around_z(3))),
                                            "Table");
    robot.look_at(table);

    std::cout << "Robot looking at: " << table << std::endl;

    FramedPose const object = robot.detect_object();

    std::cout << "Robot detected object at: " << object << std::endl;

    const auto object_in_root = robot.transform_to_frame(object, robot.frames.root);
    std::cout << "In root frame at: " << object_in_root << std::endl;

    const auto object_in_tcp_right = robot.transform_to_frame(object, robot.frames.tcp_right);

    // Grasp an object.
    robot.grasp(object_in_tcp_right);

    return 0;
}
