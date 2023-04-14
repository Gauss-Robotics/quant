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
            quant::FramedSpatialDisplacement const root =
                origin.enframe(quant::SpatialDisplacement(), frames.root);

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

            quant::FramedSpatialDisplacement const camera =
                chest.enframe(quant::SpatialDisplacement(), frames.camera);

            _frames[std::string(root.name)] = root;
        }

        void
        look_at(quant::FramedPose const& location)
        {
        }

        quant::FramedPose
        detect_object() const
        {
            quant::Pose const object_pose;
            return quant::FramedPose(object_pose, {.name = "Object", .base_frame = frames.camera});
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

    private:
        std::map<std::string, quant::FramedSpatialDisplacement> _frames;
    };

}  // namespace simple_robot_example
