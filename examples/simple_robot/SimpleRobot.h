#pragma once

#include <quant/framed_units/position.h>

#include <map>
#include <string>

namespace simple_robot_example
{

    class SimpleRobot
    {
    public:
        SimpleRobot(quant::FramedPose const& origin)
        {
            using namespace quant;

            FramedPose const root =
                origin.enframe(Pose(Position::millimeters({.x = 300}),
                                    Orientation::radians(AxisAngle::around_z(2))),
                               frames.root);

            this->root = root;

            FramedPose const chest =
                root.enframe(Pose(Position::millimeters({10, 0, 10}),
                                  Orientation::degrees(AxisAngle::around_x(90))),
                             frames.chest);

            FramedPose const arm_right =
                chest.enframe(Pose(Position::millimeters({0, 0, 100})), frames.arm_right);

            FramedPose const tcp_right = arm_right.enframe(
                Pose(Orientation::degrees({.axis = {0, 1, 0}, .angle = 45})), frames.tcp_right);

            FramedPose const arm_left =
                chest.enframe(arm_right.get_framed_object().inverse(), frames.arm_left);

            FramedPose const tcp_left =
                arm_left.enframe(Pose(-arm_right.get_framed_object().linear(),
                                      arm_right.get_framed_object().angular()),
                                 frames.tcp_left);

            FramedPose const camera = chest.enframe(Pose(Position::millimeters({100, 100, 100})), frames.camera);

            _frames[std::string(root.get_name())] = root;
            _frames[std::string(chest.get_name())] = chest;
            _frames[std::string(arm_right.get_name())] = arm_right;
            _frames[std::string(tcp_right.get_name())] = tcp_right;
            _frames[std::string(arm_left.get_name())] = arm_left;
            _frames[std::string(tcp_left.get_name())] = tcp_left;
            _frames[std::string(camera.get_name())] = camera;
            _frames[std::string(origin.get_name())] = origin;
        }

        void
        look_at(quant::FramedPose const& location)
        {
            ;
        }

        quant::FramedPose
        detect_object() const
        {

            quant::Pose const object_pose(
                quant::Position::millimeters(
                    quant::units::Vector::from_eigen(Eigen::Vector3d::Random())),
                quant::Orientation::radians(
                    quant::AxisAngle::from_eigen(Eigen::Quaterniond::UnitRandom())));
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

        quant::BaseChange get_frame_transformation(std::string const& from_frame,
                                                   std::string const& to_frame) const
        {
            const auto from_pose = _frames.at(from_frame);
            const auto to_pose = _frames.at(to_frame);
            if (from_pose.get_base_frame() != to_pose.get_base_frame())
            {
                try {
                    quant::FramedPose from_pose_in_root;
                    quant::FramedPose to_pose_in_root;
                    if (from_pose.get_base_frame() != frames.root)
                    {
                        from_pose_in_root = transform_to_frame(from_pose, frames.root);
                    }
                    else
                    {
                        from_pose_in_root = from_pose;
                    }
                    if (to_pose.get_name() == frames.root)
                    {
                        return quant::BaseChange{.from_frame = from_frame,
                                                 .to_frame = to_frame,
                                                 .transformation = quant::SpatialDisplacement(from_pose_in_root.get_framed_object())};
                    }
                    if (to_pose.get_base_frame() != frames.root)
                    {
                        to_pose_in_root = transform_to_frame(to_pose, frames.root);
                    }
                    else
                    {
                        to_pose_in_root = to_pose;
                    }
                    return quant::BaseChange{.from_frame = from_frame,
                                             .to_frame = to_frame,
                                             .transformation = (to_pose_in_root - from_pose_in_root).get_framed_object()};
                } catch (std::out_of_range const&) {
                    throw std::runtime_error("Frames are not connected.");
                }
            }
            return quant::BaseChange{.from_frame = from_frame,
                                     .to_frame = to_frame,
                                     .transformation = (to_pose - from_pose).get_framed_object()};
        }

        quant::FramedPose transform_to_frame(const quant::FramedPose& pose, std::string const& to_frame) const
        {
            const auto base_change = get_frame_transformation(std::string(pose.get_base_frame()), to_frame);
            return base_change * pose;
        }

        quant::FramedPose root =
            quant::FramedPose(quant::Pose(quant::Position::millimeters({.x = 42})),
                              {.name = frames.root});

    private:
        std::map<std::string, quant::FramedPose> _frames;
    };

}  // namespace simple_robot_example
