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

    struct Domain
    {
        using LinearState = Position;
        using AngularState = Orientation;
        using SpatialState = Pose;
        using LinearDifference = LinearDisplacement;
        using AngularDifference = AngularDisplacement;
        using SpatialDifference = SpatialDisplacement;
    };

}  // namespace quant::units::position

namespace quant::traits
{

    template <>
    struct DefineDifferenceTypeOf<units::position::Position>
    {
        using DifferenceType = units::position::LinearDisplacement;
    };

    template <>
    struct DefineStateTypeOf<units::position::LinearDisplacement>
    {
        using StateType = units::position::Position;
    };

    template <>
    struct DefineDifferenceTypeOf<units::position::Orientation>
    {
        using DifferenceType = units::position::AngularDisplacement;
    };

    template <>
    struct DefineStateTypeOf<units::position::AngularDisplacement>
    {
        using StateType = units::position::Orientation;
    };

    template <>
    struct DefineDifferenceTypeOf<units::position::Pose>
    {
        using DifferenceType = units::position::SpatialDisplacement;
    };

    template <>
    struct DefineStateTypeOf<units::position::SpatialDisplacement>
    {
        using StateType = units::position::Pose;
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
