#pragma once

namespace quant::framed_units::position
{

    class FramedPosition;
    class FramedOrientation;
    class FramedPose;

    class FramedLinearDisplacement;
    class FramedAngularDisplacement;
    class FramedSpatialDisplacement;

}  // namespace quant::framed_units::position

namespace quant
{

    using framed_units::position::FramedOrientation;
    using framed_units::position::FramedPose;
    using framed_units::position::FramedPosition;

    using framed_units::position::FramedAngularDisplacement;
    using framed_units::position::FramedLinearDisplacement;
    using framed_units::position::FramedSpatialDisplacement;

}  // namespace quant
