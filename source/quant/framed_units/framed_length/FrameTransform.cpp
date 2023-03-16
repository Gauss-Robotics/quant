#include "FrameTransform.h"

#include <simox/core/length/FramedPosition.h>
#include <simox/core/length/exceptions.h>


namespace simox::core::length
{

    FrameTransform::FrameTransform(const Transform& tf, const FrameMixin& m) :
        Transform(tf), FrameMixin(m)
    {
        ;
    }


    FrameTransform::FrameTransform(const Transform& tf,
                                   const frame::FrameID frame,
                                   const frame::FrameID& baseFrame) :
        Transform(tf), FrameMixin({.frame = frame, .baseFrame = baseFrame})
    {
        ;
    }


    FrameTransform
    FrameTransform::inverse() const
    {
        return FrameTransform(_representation.inverse(), {.frame = baseFrame, .baseFrame = frame});
    }


    FrameTransform
    FrameTransform::operator*(const FrameTransform& rhs) const
    {
        if (frame != rhs.baseFrame)
        {
            throw FrameMismatch(str() + " and " + rhs.str() + " are incompatible.  " +
                                "Expected base frame of lhs (' " + baseFrame.str() +
                                "') to be equal to " + "frame of rhs ('" + rhs.frame.str() + "').");
        }

        return FrameTransform(Transform(_representation * rhs._representation),
                              {.frame = frame, .baseFrame = rhs.baseFrame});
    }


    FramedPosition
    FrameTransform::operator*(const FramedPosition& rhs) const
    {
        if (baseFrame != rhs.baseFrame)
        {
            throw FrameMismatch(str() + " and " + rhs.str() + " are incompatible.  " +
                                "Expected base frame of lhs (' " + baseFrame.str() +
                                "') to be equal to " + "frame of rhs ('" + rhs.baseFrame.str() +
                                "').");
        }

        return {Position(_representation * rhs.representation_), baseFrame};
    }


    std::string
    FrameTransform::str() const
    {
        return "Transform " + FrameMixin::strTemplate();
    }

} // namespace simox::core::length
