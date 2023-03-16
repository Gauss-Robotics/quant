#pragma once


#include <Eigen/Geometry>

#include <simox/core/length/Transform.h>
#include <simox/core/length/frame/FrameMixin.h>


namespace simox::core::position
{

    class FramedPosition;


    /**
     * @brief Describes the Transform `tf` of frame `frame` with respect to base frame `baseFrame`.
     */
    class FrameTransform : public Transform, public FrameMixin
    {
    public:
        FrameTransform(const Transform& tf, const FrameMixin& m);

        FrameTransform(const Transform& tf, const FrameID frame, const FrameID& baseFrame);

        FrameTransform inverse() const;

        std::string str() const;

        // Transform.
    public:
        FrameTransform operator*(const FrameTransform& rhs) const;

        // Apply.
    public:
        FramedPosition operator*(const FramedPosition& rhs) const;
    };

} // namespace simox::core::position


namespace simox
{
    using core::position::FrameTransform;
} // namespace simox
