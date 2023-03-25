#pragma once

namespace quant::units::force
{

    class Force;
    class Torque;
    class Wrench;
    class ForceDifference;
    class TorqueDifference;
    class WrenchDifference;

    struct Domain
    {
        using LinearState = Force;
        using AngularState = Torque;
        using SpatialState = Wrench;
        using LinearDifference = ForceDifference;
        using AngularDifference = TorqueDifference;
        using SpatialDifference = WrenchDifference;
    };

}  // namespace quant::units::force

namespace quant
{

    using units::force::Force;
    using units::force::ForceDifference;
    using units::force::Torque;
    using units::force::TorqueDifference;
    using units::force::Wrench;

}  // namespace quant
