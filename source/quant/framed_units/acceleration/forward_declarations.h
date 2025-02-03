#pragma once

#include <quant/framed_geometry/forward_declarations.h>
#include <quant/geometry/forward_declarations.h>
#include <quant/units/acceleration/forward_declarations.h>

#include <functional>

namespace quant::framed_units::acceleration
{

    class LinearAcceleration;
    class AngularAcceleration;
    class SpatialAcceleration;

    class LinearAccelerationDifference;
    class AngularAccelerationDifference;
    class SpatialAccelerationDifference;

    namespace base_change
    {
        units::acceleration::LinearAcceleration
        linear_acceleration(units::acceleration::LinearAcceleration const&,
                            framed_geometry::BaseChange const&);
        units::acceleration::AngularAcceleration
        angular_acceleration(units::acceleration::AngularAcceleration const&,
                             framed_geometry::BaseChange const&);
        units::acceleration::SpatialAcceleration
        spatial_acceleration(units::acceleration::SpatialAcceleration const&,
                             framed_geometry::BaseChange const&);
        units::acceleration::LinearAccelerationDifference
        linear_acceleration_difference(units::acceleration::LinearAccelerationDifference const&,
                                       framed_geometry::BaseChange const&);
        units::acceleration::AngularAccelerationDifference
        angular_acceleration_difference(units::acceleration::AngularAccelerationDifference const&,
                                        framed_geometry::BaseChange const&);
        units::acceleration::SpatialAccelerationDifference
        spatial_acceleration_difference(units::acceleration::SpatialAccelerationDifference const&,
                                        framed_geometry::BaseChange const&);
    }  // namespace base_change
}  // namespace quant::framed_units::acceleration

namespace quant::traits
{

    using FramedAccelerationDomain =
        Define3DDomain<framed_units::acceleration::LinearAcceleration,
                       framed_units::acceleration::AngularAcceleration,
                       framed_units::acceleration::SpatialAcceleration,
                       framed_units::acceleration::LinearAccelerationDifference,
                       framed_units::acceleration::AngularAccelerationDifference,
                       framed_units::acceleration::SpatialAccelerationDifference>;

    template <>
    struct DefineFramedTraits<units::acceleration::LinearAcceleration> :
        public traits_of<units::acceleration::LinearAcceleration>
    {
        using FramedDomain = FramedAccelerationDomain;
        using FramedState = framed_units::acceleration::LinearAcceleration;
        using FramedDifference = framed_units::acceleration::LinearAccelerationDifference;
        static constexpr auto basis_change_function =
            &framed_units::acceleration::base_change::linear_acceleration;
    };

    template <>
    struct DefineFramedTraits<units::acceleration::LinearAccelerationDifference> :
        public traits_of<units::acceleration::LinearAccelerationDifference>
    {
        using FramedDomain = FramedAccelerationDomain;
        using FramedDifference = framed_units::acceleration::LinearAccelerationDifference;
        using FramedState = framed_units::acceleration::LinearAcceleration;
        static constexpr auto basis_change_function =
            framed_units::acceleration::base_change::linear_acceleration_difference;
    };

    template <>
    struct DefineFramedTraits<units::acceleration::AngularAcceleration> :
        public traits_of<units::acceleration::AngularAcceleration>
    {
        using FramedDomain = FramedAccelerationDomain;
        using FramedState = framed_units::acceleration::AngularAcceleration;
        using FramedDifference = framed_units::acceleration::AngularAccelerationDifference;
        static constexpr auto basis_change_function =
            framed_units::acceleration::base_change::angular_acceleration;
    };

    template <>
    struct DefineFramedTraits<units::acceleration::AngularAccelerationDifference> :
        public traits_of<units::acceleration::AngularAccelerationDifference>
    {
        using FramedDomain = FramedAccelerationDomain;
        using FramedDifference = framed_units::acceleration::AngularAccelerationDifference;
        using FramedState = framed_units::acceleration::AngularAcceleration;
        static constexpr auto basis_change_function =
            framed_units::acceleration::base_change::angular_acceleration_difference;
    };

    template <>
    struct DefineFramedTraits<units::acceleration::SpatialAcceleration> :
        public traits_of<units::acceleration::SpatialAcceleration>
    {
        using FramedDomain = FramedAccelerationDomain;
        using FramedState = framed_units::acceleration::SpatialAcceleration;
        using FramedDifference = framed_units::acceleration::SpatialAccelerationDifference;
        static constexpr auto basis_change_function =
            framed_units::acceleration::base_change::spatial_acceleration;
    };

    template <>
    struct DefineFramedTraits<units::acceleration::SpatialAccelerationDifference> :
        public traits_of<units::acceleration::SpatialAccelerationDifference>
    {
        using FramedDomain = FramedAccelerationDomain;
        using FramedDifference = framed_units::acceleration::SpatialAccelerationDifference;
        using FramedState = framed_units::acceleration::SpatialAcceleration;
        static constexpr auto basis_change_function =
            framed_units::acceleration::base_change::spatial_acceleration_difference;
    };

}  // namespace quant::traits

namespace quant
{

    using FramedAngularAcceleration = framed_units::acceleration::AngularAcceleration;
    using FramedSpatialAcceleration = framed_units::acceleration::SpatialAcceleration;
    using FramedLinearAcceleration = framed_units::acceleration::LinearAcceleration;

    using FramedAngularAccelerationDifference =
        framed_units::acceleration::AngularAccelerationDifference;
    using FramedLinearAccelerationDifference =
        framed_units::acceleration::LinearAccelerationDifference;
    using FramedSpatialAccelerationDifference =
        framed_units::acceleration::SpatialAccelerationDifference;

}  // namespace quant
