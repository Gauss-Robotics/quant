#pragma once

#include <quant/framed_units/position.h>

#include <map>
#include <string>

namespace simple_robot_example
{

    class SimpleRobot
    {
    public:
        SimpleRobot(quant:: FramedPose const& origin)
        {
            using namespace quant;

             FramedPose const root = origin.enframe(
                Pose(Position::millimeters({.x = 300}),
                                         Orientation::radians(AxisAngle::around_z(2))),
                frames.root);

            this->root = root;

             FramedPose const chest =
                root.enframe(Pose(), frames.chest);

             FramedPose const arm_right =
                chest.enframe(Pose(), frames.arm_right);

             FramedPose const tcp_right =
                arm_right.enframe(Pose(), frames.tcp_right);

             FramedPose const arm_left =
                chest.enframe(Pose(), frames.arm_left);

             FramedPose const tcp_left =
                arm_left.enframe(Pose(), frames.tcp_left);

             FramedPose const camera =
                chest.enframe(Pose(), frames.camera);

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

        quant:: FramedPose root = quant:: FramedPose(
            quant::Pose(quant::Position::millimeters({.x = 42})),
             {.name="asdf"});

    private:
        std::map<std::string, quant:: FramedPose> _frames;
    };

}  // namespace simple_robot_example
