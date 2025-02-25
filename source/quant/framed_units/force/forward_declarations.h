#pragma once

#include <quant/framed_geometry/forward_declarations.h>
#include <quant/geometry/forward_declarations.h>
#include <quant/units/force/forward_declarations.h>

namespace quant::framed_units::force
{

    class Force;
    class Torque;
    class Wrench;

    class ForceDifference;
    class TorqueDifference;
    class WrenchDifference;

    namespace base_change
    {
        units::force::Force
        force(units::force::Force const&, framed_geometry::BaseChange const&);
        units::force::Torque
        torque(units::force::Torque const&, framed_geometry::BaseChange const&);
        units::force::Wrench
        wrench(units::force::Wrench const&, framed_geometry::BaseChange const&);
        units::force::ForceDifference
        force_difference(units::force::ForceDifference const&, framed_geometry::BaseChange const&);
        units::force::TorqueDifference
        torque_difference(units::force::TorqueDifference const&,
                          framed_geometry::BaseChange const&);
        units::force::WrenchDifference
        wrench_difference(units::force::WrenchDifference const&,
                          framed_geometry::BaseChange const&);
    }  // namespace base_change
}  // namespace quant::framed_units::force

namespace quant
{

    using FramedTorque = framed_units::force::Torque;
    using FramedWrench = framed_units::force::Wrench;
    using FramedForce = framed_units::force::Force;

    using FramedTorqueDifference = framed_units::force::TorqueDifference;
    using FramedForceDifference = framed_units::force::ForceDifference;
    using FramedWrenchDifference = framed_units::force::WrenchDifference;

}  // namespace quant

namespace quant::traits
{
    using FramedForceDomain =
        Define3DDomain<Define3DSubDomain<FramedForce, FramedForceDifference, R3Type>,
                       Define3DSubDomain<FramedTorque, FramedTorqueDifference, R3Type>,
                       Define3DSubDomain<FramedWrench, FramedWrenchDifference, R6Type>>;

    template <>
    struct DefineFramedTraits<Force> : public traits_of<Force>
    {
        using FramedDomain = FramedForceDomain;
        using FramedState = framed_units::force::Force;
        using FramedDifference = framed_units::force::ForceDifference;
        static constexpr auto basis_change_function = &framed_units::force::base_change::force;
    };

    template <>
    struct DefineFramedTraits<ForceDifference> : public traits_of<ForceDifference>
    {
        using FramedDomain = FramedForceDomain;
        using FramedDifference = framed_units::force::ForceDifference;
        using FramedState = framed_units::force::Force;
        static constexpr auto basis_change_function =
            framed_units::force::base_change::force_difference;
    };

    template <>
    struct DefineFramedTraits<Torque> : public traits_of<Torque>
    {
        using FramedDomain = FramedForceDomain;
        using FramedState = framed_units::force::Torque;
        using FramedDifference = framed_units::force::TorqueDifference;
        static constexpr auto basis_change_function = framed_units::force::base_change::torque;
    };

    template <>
    struct DefineFramedTraits<TorqueDifference> : public traits_of<TorqueDifference>
    {
        using FramedDomain = FramedForceDomain;
        using FramedDifference = framed_units::force::TorqueDifference;
        using FramedState = framed_units::force::Torque;
        static constexpr auto basis_change_function =
            framed_units::force::base_change::torque_difference;
    };

    template <>
    struct DefineFramedTraits<Wrench> : public traits_of<Wrench>
    {
        using FramedDomain = FramedForceDomain;
        using FramedState = framed_units::force::Wrench;
        using FramedDifference = framed_units::force::WrenchDifference;
        static constexpr auto basis_change_function = framed_units::force::base_change::wrench;
    };

    template <>
    struct DefineFramedTraits<WrenchDifference> : public traits_of<WrenchDifference>
    {
        using FramedDomain = FramedForceDomain;
        using FramedDifference = framed_units::force::WrenchDifference;
        using FramedState = framed_units::force::Wrench;
        static constexpr auto basis_change_function =
            framed_units::force::base_change::wrench_difference;
    };

}  // namespace quant::traits
