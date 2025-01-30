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

namespace quant::traits
{

    using FramedVelocityDomain = Define3DDomain<framed_units::velocity::LinearVelocity,
                                                framed_units::velocity::AngularVelocity,
                                                framed_units::velocity::Twist,
                                                framed_units::velocity::LinearVelocityDifference,
                                                framed_units::velocity::AngularVelocityDifference,
                                                framed_units::velocity::TwistDifference>;

    template <>
    struct DefineFramedTraits<units::velocity::LinearVelocity> :
        public traits_of<units::velocity::LinearVelocity>
    {
        using FramedDomain = FramedVelocityDomain;
        using FramedState = framed_units::velocity::LinearVelocity;
        using FramedDifference = framed_units::velocity::LinearVelocityDifference;
        static constexpr auto basis_change_function =
            &framed_units::velocity::base_change::linear_velocity;
    };

    template <>
    struct DefineFramedTraits<units::velocity::LinearVelocityDifference> :
        public traits_of<units::velocity::LinearVelocityDifference>
    {
        using FramedDomain = FramedVelocityDomain;
        using FramedDifference = framed_units::velocity::LinearVelocityDifference;
        using FramedState = framed_units::velocity::LinearVelocity;
        static constexpr auto basis_change_function =
            framed_units::velocity::base_change::linear_velocity_difference;
    };

    template <>
    struct DefineFramedTraits<units::velocity::AngularVelocity> :
        public traits_of<units::velocity::AngularVelocity>
    {
        using FramedDomain = FramedVelocityDomain;
        using FramedState = framed_units::velocity::AngularVelocity;
        using FramedDifference = framed_units::velocity::AngularVelocityDifference;
        static constexpr auto basis_change_function =
            framed_units::velocity::base_change::angular_velocity;
    };

    template <>
    struct DefineFramedTraits<units::velocity::AngularVelocityDifference> :
        public traits_of<units::velocity::AngularVelocityDifference>
    {
        using FramedDomain = FramedVelocityDomain;
        using FramedDifference = framed_units::velocity::AngularVelocityDifference;
        using FramedState = framed_units::velocity::AngularVelocity;
        static constexpr auto basis_change_function =
            framed_units::velocity::base_change::angular_velocity_difference;
    };

    template <>
    struct DefineFramedTraits<units::velocity::Twist> : public traits_of<units::velocity::Twist>
    {
        using FramedDomain = FramedVelocityDomain;
        using FramedState = framed_units::velocity::Twist;
        using FramedDifference = framed_units::velocity::TwistDifference;
        static constexpr auto basis_change_function = framed_units::velocity::base_change::twist;
    };

    template <>
    struct DefineFramedTraits<units::velocity::TwistDifference> :
        public traits_of<units::velocity::TwistDifference>
    {
        using FramedDomain = FramedVelocityDomain;
        using FramedDifference = framed_units::velocity::TwistDifference;
        using FramedState = framed_units::velocity::Twist;
        static constexpr auto basis_change_function =
            framed_units::velocity::base_change::twist_difference;
    };

}  // namespace quant::traits

namespace quant
{

    using FramedAngularVelocity = framed_units::velocity::AngularVelocity;
    using FramedTwist = framed_units::velocity::Twist;
    using FramedLinearVelocity = framed_units::velocity::LinearVelocity;

    using FramedAngularVelocityDifference = framed_units::velocity::AngularVelocityDifference;
    using FramedLinearVelocityDifference = framed_units::velocity::LinearVelocityDifference;
    using FramedTwistDifference = framed_units::velocity::TwistDifference;

}  // namespace quant
