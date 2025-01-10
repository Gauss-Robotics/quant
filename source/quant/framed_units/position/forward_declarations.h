#pragma once

#include <quant/framed_geometry/forward_declarations.h>
#include <quant/geometry/forward_declarations.h>
#include <quant/units/position/forward_declarations.h>

namespace quant::framed_units::position
{

    class Position;
    class Orientation;
    class Pose;

    class LinearDisplacement;
    class AngularDisplacement;
    class SpatialDisplacement;

}  // namespace quant::framed_units::position

namespace quant::traits
{

    using FramedPositionDomain = Define3DDomain<framed_units::position::Position,
                                                framed_units::position::Orientation,
                                                framed_units::position::Pose,
                                                framed_units::position::LinearDisplacement,
                                                framed_units::position::AngularDisplacement,
                                                framed_units::position::SpatialDisplacement>;

    template <>
    struct DefineFramedTraits<units::position::Position> :
        public traits_of<units::position::Position>
    {
        using FramedDomain = FramedPositionDomain;
        using Framed = framed_units::position::Position;
        using FramedDifference = framed_units::position::LinearDisplacement;
    };

    template <>
    struct DefineFramedTraits<units::position::LinearDisplacement> :
        public traits_of<units::position::LinearDisplacement>
    {
        using FramedDomain = FramedPositionDomain;
        using Framed = framed_units::position::LinearDisplacement;
        using FramedState = framed_units::position::Position;
    };

    template <>
    struct DefineFramedTraits<units::position::Orientation> :
        public traits_of<units::position::Orientation>
    {
        using FramedDomain = FramedPositionDomain;
        using Framed = framed_units::position::Orientation;
        using FramedDifference = framed_units::position::AngularDisplacement;
    };

    template <>
    struct DefineFramedTraits<units::position::AngularDisplacement> :
        public traits_of<units::position::AngularDisplacement>
    {
        using FramedDomain = FramedPositionDomain;
        using Framed = framed_units::position::AngularDisplacement;
        using FramedState = framed_units::position::Orientation;
    };

    template <>
    struct DefineFramedTraits<units::position::Pose> : public traits_of<units::position::Pose>
    {
        using FramedDomain = FramedPositionDomain;
        using Framed = framed_units::position::Pose;
        using FramedDifference = framed_units::position::SpatialDisplacement;
    };

    template <>
    struct DefineFramedTraits<units::position::SpatialDisplacement> :
        public traits_of<units::position::SpatialDisplacement>
    {
        using FramedDomain = FramedPositionDomain;
        using Framed = framed_units::position::SpatialDisplacement;
        using FramedState = framed_units::position::Pose;
    };

}  // namespace quant::traits

namespace quant
{

    using FramedOrientation = framed_units::position::Orientation;
    using FramedPose = framed_units::position::Pose;
    using FramedPosition = framed_units::position::Position;

    using FramedAngularDisplacement = framed_units::position::AngularDisplacement;
    using FramedLinearDisplacement = framed_units::position::LinearDisplacement;
    using FramedSpatialDisplacement = framed_units::position::SpatialDisplacement;

}  // namespace quant
