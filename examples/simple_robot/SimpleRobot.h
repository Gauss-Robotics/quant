#pragma once

#include <quant/framed_units/position.h>

#include <string>
#include <unordered_map>

namespace simple_robot_example
{

    class SimpleRobot
    {
    public:
        SimpleRobot(quant::FramedSpatialDisplacement const& globalFrame)
        {
            quant::FramedSpatialDisplacement const root =
                globalFrame.enframe(quant::SpatialDisplacement(), frames.root);

            quant::FramedSpatialDisplacement const chest =
                root.enframe(quant::SpatialDisplacement(), frames.chest);
        }

        struct RobotFrames
        {
            std::string root = "Robot::Root";
            std::string chest = "Robot::Chest";
            std::string armRight = "Robot::RightArm";
            std::string tcpRight = "Robot::RightTCP";
            std::string armLeft = "Robot::LeftArm";
            std::string tcpLeft = "Robot::LeftTCP";
        } frames;

    private:
        std::unordered_map<std::string, quant::FramedSpatialDisplacement> frames_;
    };

}  // namespace simple_robot_example
