#pragma once

#include <quant/framed_geometry/forward_declarations.h>
#include <quant/geometry/forward_declarations.h>
#include <quant/units/velocity/forward_declarations.h>

#include <functional>

namespace quant::framed_units::velocity
{

    class LinearVelocity;
    class AngularVelocity;
    class Twist;

    class LinearVelocityDifference;
    class AngularVelocityDifference;
    class TwistDifference;

    namespace base_change
    {
        units::velocity::LinearVelocity
        linear_velocity(units::velocity::LinearVelocity const&, framed_geometry::BaseChange const&);
        units::velocity::AngularVelocity
        angular_velocity(units::velocity::AngularVelocity const&,
                         framed_geometry::BaseChange const&);
        units::velocity::Twist
        twist(units::velocity::Twist const&, framed_geometry::BaseChange const&);
        units::velocity::LinearVelocityDifference
        linear_velocity_difference(units::velocity::LinearVelocityDifference const&,
                                   framed_geometry::BaseChange const&);
        units::velocity::AngularVelocityDifference
        angular_velocity_difference(units::velocity::AngularVelocityDifference const&,
                                    framed_geometry::BaseChange const&);
        units::velocity::TwistDifference
        twist_difference(units::velocity::TwistDifference const&,
                         framed_geometry::BaseChange const&);
    }  // namespace base_change
}  // namespace quant::framed_units::velocity

namespace quant
{

    using FramedAngularVelocity = framed_units::velocity::AngularVelocity;
    using FramedTwist = framed_units::velocity::Twist;
    using FramedLinearVelocity = framed_units::velocity::LinearVelocity;

    using FramedAngularVelocityDifference = framed_units::velocity::AngularVelocityDifference;
    using FramedLinearVelocityDifference = framed_units::velocity::LinearVelocityDifference;
    using FramedTwistDifference = framed_units::velocity::TwistDifference;

}  // namespace quant

namespace quant::traits
{
    using FramedVelocityDomain = Define3DDomain<
        Define3DSubDomain<FramedLinearVelocity, FramedLinearVelocityDifference, R3Type>,
        Define3DSubDomain<FramedAngularVelocity, FramedAngularVelocityDifference, R3Type>,
        Define3DSubDomain<FramedTwist, FramedTwistDifference, R6Type>>;

    template <>
    struct DefineFramedTraits<LinearVelocity> : public traits_of<LinearVelocity>
    {
        using FramedDomain = FramedVelocityDomain;
        using FramedState = framed_units::velocity::LinearVelocity;
        using FramedDifference = framed_units::velocity::LinearVelocityDifference;
        static constexpr auto basis_change_function =
            &framed_units::velocity::base_change::linear_velocity;
    };

    template <>
    struct DefineFramedTraits<LinearVelocityDifference> : public traits_of<LinearVelocityDifference>
    {
        using FramedDomain = FramedVelocityDomain;
        using FramedDifference = framed_units::velocity::LinearVelocityDifference;
        using FramedState = framed_units::velocity::LinearVelocity;
        static constexpr auto basis_change_function =
            framed_units::velocity::base_change::linear_velocity_difference;
    };

    template <>
    struct DefineFramedTraits<AngularVelocity> : public traits_of<AngularVelocity>
    {
        using FramedDomain = FramedVelocityDomain;
        using FramedState = framed_units::velocity::AngularVelocity;
        using FramedDifference = framed_units::velocity::AngularVelocityDifference;
        static constexpr auto basis_change_function =
            framed_units::velocity::base_change::angular_velocity;
    };

    template <>
    struct DefineFramedTraits<AngularVelocityDifference> :
        public traits_of<AngularVelocityDifference>
    {
        using FramedDomain = FramedVelocityDomain;
        using FramedDifference = framed_units::velocity::AngularVelocityDifference;
        using FramedState = framed_units::velocity::AngularVelocity;
        static constexpr auto basis_change_function =
            framed_units::velocity::base_change::angular_velocity_difference;
    };

    template <>
    struct DefineFramedTraits<Twist> : public traits_of<Twist>
    {
        using FramedDomain = FramedVelocityDomain;
        using FramedState = framed_units::velocity::Twist;
        using FramedDifference = framed_units::velocity::TwistDifference;
        static constexpr auto basis_change_function = framed_units::velocity::base_change::twist;
    };

    template <>
    struct DefineFramedTraits<TwistDifference> : public traits_of<TwistDifference>
    {
        using FramedDomain = FramedVelocityDomain;
        using FramedDifference = framed_units::velocity::TwistDifference;
        using FramedState = framed_units::velocity::Twist;
        static constexpr auto basis_change_function =
            framed_units::velocity::base_change::twist_difference;
    };

}  // namespace quant::traits