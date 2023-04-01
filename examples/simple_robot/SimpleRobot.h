#pragma once

#include <quant/framed_units/position.h>

#include <string>
#include <unordered_map>

namespace simple_robot_example
{

    class SimpleRobot
    {
    public:
        SimpleRobot(quant::FramedSpatialDisplacement const& global_frame)
        {
            quant::FramedSpatialDisplacement const root =
                global_frame.enframe(quant::SpatialDisplacement(), frames.root);

            quant::FramedSpatialDisplacement const chest =
                root.enframe(quant::SpatialDisplacement(), frames.chest);

            quant::FramedSpatialDisplacement const arm_right =
                chest.enframe(quant::SpatialDisplacement(), frames.arm_right);

            quant::FramedSpatialDisplacement const tcp_right =
                arm_right.enframe(quant::SpatialDisplacement(), frames.tcp_right);

            quant::FramedSpatialDisplacement const arm_left =
                chest.enframe(quant::SpatialDisplacement(), frames.arm_left);

            quant::FramedSpatialDisplacement const tcp_left =
                arm_left.enframe(quant::SpatialDisplacement(), frames.tcp_left);
        }

        struct RobotFrames
        {
            std::string root = "Robot::Root";
            std::string chest = "Robot::Chest";
            std::string arm_right = "Robot::RightArm";
            std::string tcp_right = "Robot::RightTCP";
            std::string arm_left = "Robot::LeftArm";
            std::string tcp_left = "Robot::LeftTCP";
        } const frames;

    private:
        std::unordered_map<std::string, quant::FramedSpatialDisplacement> frames_;
    };

}  // namespace simple_robot_example
