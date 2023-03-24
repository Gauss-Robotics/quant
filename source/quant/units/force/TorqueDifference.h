#pragma once

#include <quant/geometry/AxisAngle.h>
#include <quant/geometry/Difference.h>
#include <quant/units/force/Torque.h>
#include <quant/units/force_fwd.h>

namespace quant::geometry
{

    template <>
    struct DefineDifferenceType<quant::Torque>
    {
        using DifferenceType = units::force::TorqueDifference;
    };

}  // namespace quant::geometry

namespace quant::units::force
{

    class TorqueDifference : public AngularDifference<Torque>
    {

    public:
        using AngularDifference<TorqueDifference>::AngularDifference;

        static TorqueDifference
        NewtonMeters(AxisAngle const& aa)
        {
            return TorqueDifference{Torque::NewtonMeters(aa)};
        }
    };

}  // namespace quant::units::force

namespace quant
{

    using units::force::TorqueDifference;

}  // namespace quant
