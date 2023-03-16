#pragma once


#include <Eigen/Geometry>

#include <quant/core/length/Transform.h>
#include <quant/core/length/frame/FrameMixin.h>


namespace quant::position
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

} // namespace quant::position


namespace quant
{
    using core::position::FrameTransform;
} // namespace quant
