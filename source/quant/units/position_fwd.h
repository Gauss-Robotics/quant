#pragma once

namespace quant::units::position
{

    class Position;
    class Orientation;
    class Pose;

    class LinearDisplacement;
    class AngularDisplacement;
    class SpatialDisplacement;

}  // namespace quant::units::position

namespace quant
{

    using units::position::Orientation;
    using units::position::Pose;
    using units::position::Position;

    using units::position::AngularDisplacement;
    using units::position::LinearDisplacement;
    using units::position::SpatialDisplacement;

}  // namespace quant
