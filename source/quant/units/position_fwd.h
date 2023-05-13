#pragma once

#include <quant/geometry_fwd.h>

namespace quant::units::position
{

    class Position;
    class Orientation;
    class Pose;

    class LinearDisplacement;
    class AngularDisplacement;
    class SpatialDisplacement;

}  // namespace quant::units::position

namespace quant::traits
{

    using PositionDomain = Define3DDomain<units::position::Position,
                                          units::position::Orientation,
                                          units::position::Pose,
                                          units::position::LinearDisplacement,
                                          units::position::AngularDisplacement,
                                          units::position::SpatialDisplacement>;

    template <>
    struct DefineTraits<units::position::Position>
    {
        using Domain = PositionDomain;
        using Difference = units::position::LinearDisplacement;
        using GeometricType = LinearStateType;
    };

    template <>
    struct DefineTraits<units::position::LinearDisplacement>
    {
        using Domain = PositionDomain;
        using State = units::position::Position;
        using GeometricType = LinearDifferenceType;
    };

    template <>
    struct DefineTraits<units::position::Orientation>
    {
        using Domain = PositionDomain;
        using Difference = units::position::AngularDisplacement;
        using GeometricType = AngularStateType;
    };

    template <>
    struct DefineTraits<units::position::AngularDisplacement>
    {
        using Domain = PositionDomain;
        using State = units::position::Orientation;
        using GeometricType = AngularDifferenceType;
    };

    template <>
    struct DefineTraits<units::position::Pose>
    {
        using Domain = PositionDomain;
        using Difference = units::position::SpatialDisplacement;
        using GeometricType = SpatialStateType;
    };

    template <>
    struct DefineTraits<units::position::SpatialDisplacement>
    {
        using Domain = PositionDomain;
        using State = units::position::Pose;
        using GeometricType = SpatialDifferenceType;
    };

}  // namespace quant::traits

namespace quant
{

    using units::position::Orientation;
    using units::position::Pose;
    using units::position::Position;

    using units::position::AngularDisplacement;
    using units::position::LinearDisplacement;
    using units::position::SpatialDisplacement;

}  // namespace quant
