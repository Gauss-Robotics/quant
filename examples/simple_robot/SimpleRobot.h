#pragma once

#include <quant/framed_units/position.h>

#include <map>
#include <string>

namespace simple_robot_example
{

    class SimpleRobot
    {
    public:
        SimpleRobot(quant::FramedSpatialDisplacement const& origin)
        {
            using namespace quant;

            FramedSpatialDisplacement const root = origin.enframe(
                SpatialDisplacement(Pose(Position::millimeters({.x = 300}),
                                         Orientation::radians(AxisAngle::around_z(2)))),
                frames.root);

            this->root = root;

            FramedSpatialDisplacement const chest =
                root.enframe(SpatialDisplacement(), frames.chest);

            FramedSpatialDisplacement const arm_right =
                chest.enframe(SpatialDisplacement(), frames.arm_right);

            FramedSpatialDisplacement const tcp_right =
                arm_right.enframe(SpatialDisplacement(), frames.tcp_right);

            FramedSpatialDisplacement const arm_left =
                chest.enframe(SpatialDisplacement(), frames.arm_left);

            FramedSpatialDisplacement const tcp_left =
                arm_left.enframe(SpatialDisplacement(), frames.tcp_left);

            FramedSpatialDisplacement const camera =
                chest.enframe(SpatialDisplacement(), frames.camera);

            _frames[std::string(root.get_name())] = root;
        }

        void
        look_at(quant::FramedPose const& location)
        {
            ;
        }

        quant::FramedPose
        detect_object() const
        {
            quant::Pose const object_pose;
            return quant::FramedPose(object_pose, {.name = "Cup", .base_frame = frames.camera});
        }

        void
        grasp(quant::FramedPose const& grasp)
        {
            ;
        }

        struct RobotFrames
        {
            std::string root = "Robot::Root";
            std::string chest = "Robot::Chest";
            std::string arm_right = "Robot::RightArm";
            std::string tcp_right = "Robot::RightTCP";
            std::string arm_left = "Robot::LeftArm";
            std::string tcp_left = "Robot::LeftTCP";
            std::string camera = "Robot::Camera";
        } const frames;

        quant::FramedSpatialDisplacement root = quant::FramedSpatialDisplacement(
            quant::SpatialDisplacement(quant::Pose(quant::Position::millimeters({.x = 42}))),
            {.name = "asdf"});

    private:
        std::map<std::string, quant::FramedSpatialDisplacement> _frames;
    };

}  // namespace simple_robot_example
