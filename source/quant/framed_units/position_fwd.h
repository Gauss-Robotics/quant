#pragma once

#include <quant/framed_geometry_fwd.h>
#include <quant/geometry_fwd.h>
#include <quant/units/position_fwd.h>

namespace quant::framed_units::position
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

}  // namespace quant::framed_units::position

namespace quant::traits
{

    template <>
    struct DefineDifferenceTypeOf<framed_units::position::Position>
    {
        using DifferenceType = framed_units::position::LinearDisplacement;
    };

    template <>
    struct DefineStateTypeOf<framed_units::position::LinearDisplacement>
    {
        using StateType = framed_units::position::Position;
    };

    template <>
    struct DefineDifferenceTypeOf<framed_units::position::Orientation>
    {
        using DifferenceType = framed_units::position::AngularDisplacement;
    };

    template <>
    struct DefineStateTypeOf<framed_units::position::AngularDisplacement>
    {
        using StateType = framed_units::position::Orientation;
    };

    template <>
    struct DefineDifferenceTypeOf<framed_units::position::Pose>
    {
        using DifferenceType = framed_units::position::SpatialDisplacement;
    };

    template <>
    struct DefineStateTypeOf<framed_units::position::SpatialDisplacement>
    {
        using StateType = framed_units::position::Pose;
    };

    template <>
    struct DefineFramedTypeOf<quant::units::position::Position>
    {
        using FramedType = quant::framed_units::position::Position;
    };

    template <>
    struct DefineFramedTypeOf<quant::units::position::SpatialDisplacement>
    {
        using FramedType = quant::framed_units::position::SpatialDisplacement;
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
