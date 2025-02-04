#pragma once

#include <quant/geometry/forward_declarations.h>
#include <quant/units/position/forward_declarations.h>

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

    using PositionDomain = Define3DDomain<Define3DSubDomain<units::position::Position, units::position::LinearDisplacement, R3Type>,
                                          Define3DSubDomain<units::position::Orientation, units::position::AngularDisplacement, SO3Type>,
                                          Define3DSubDomain<units::position::Pose, units::position::SpatialDisplacement, SE3Type>>;

    template <>
    struct DefineTraits<units::position::Position>
    {
        using Domain = PositionDomain;
        using State = units::position::Position;
        using Difference = units::position::LinearDisplacement;
        using GeometricType = LinearStateType;
    };

    template <>
    struct DefineTraits<units::position::LinearDisplacement>
    {
        using Domain = PositionDomain;
        using State = units::position::Position;
        using Difference = units::position::LinearDisplacement;
        using GeometricType = LinearDifferenceType;
    };

    template <>
    struct DefineTraits<units::position::Orientation>
    {
        using Domain = PositionDomain;
        using State = units::position::Orientation;
        using Difference = units::position::AngularDisplacement;
        using GeometricType = AngularStateType;
    };

    template <>
    struct DefineTraits<units::position::AngularDisplacement>
    {
        using Domain = PositionDomain;
        using State = units::position::Orientation;
        using Difference = units::position::AngularDisplacement;
        using GeometricType = AngularDifferenceType;
    };

    template <>
    struct DefineTraits<units::position::Pose>
    {
        using Domain = PositionDomain;
        using State = units::position::Pose;
        using Difference = units::position::SpatialDisplacement;
        using GeometricType = SpatialStateType;
    };

    template <>
    struct DefineTraits<units::position::SpatialDisplacement>
    {
        using Domain = PositionDomain;
        using State = units::position::Pose;
        using Difference = units::position::SpatialDisplacement;
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
