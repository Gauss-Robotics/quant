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

            quant::FramedSpatialDisplacement const armRight =
                chest.enframe(quant::SpatialDisplacement(), frames.armRight);

            quant::FramedSpatialDisplacement const tcpRight =
                armRight.enframe(quant::SpatialDisplacement(), frames.tcpRight);

            quant::FramedSpatialDisplacement const armLeft =
                chest.enframe(quant::SpatialDisplacement(), frames.armLeft);

            quant::FramedSpatialDisplacement const tcpLeft =
                armLeft.enframe(quant::SpatialDisplacement(), frames.tcpLeft);
        }

        struct RobotFrames
        {
            std::string root = "Robot::Root";
            std::string chest = "Robot::Chest";
            std::string armRight = "Robot::RightArm";
            std::string tcpRight = "Robot::RightTCP";
            std::string armLeft = "Robot::LeftArm";
            std::string tcpLeft = "Robot::LeftTCP";
        } const frames;

    private:
        std::unordered_map<std::string, quant::FramedSpatialDisplacement> frames_;
    };

}  // namespace simple_robot_example
