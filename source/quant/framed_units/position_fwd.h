#pragma once

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

namespace quant
{

    using FramedOrientation = framed_units::position::Orientation;
    using FramedPose = framed_units::position::Pose;
    using FramedPosition = framed_units::position::Position;

    using FramedAngularDisplacement = framed_units::position::AngularDisplacement;
    using FramedLinearDisplacement = framed_units::position::LinearDisplacement;
    using FramedSpatialDisplacement = framed_units::position::SpatialDisplacement;

}  // namespace quant
