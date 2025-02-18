#pragma once

#include <quant/framed_geometry/forward_declarations.h>
#include <quant/geometry/forward_declarations.h>
#include <quant/units/position/forward_declarations.h>

#include <functional>

namespace quant::framed_units::position
{

    class Position;
    class Orientation;
    class Pose;

    class LinearDisplacement;
    class AngularDisplacement;
    class SpatialDisplacement;

    units::position::Position
    position_basis_change(units::position::Position const&, framed_geometry::BaseChange const&);
    units::position::Orientation
    orientation_basis_change(units::position::Orientation const&,
                             framed_geometry::BaseChange const&);
    units::position::Pose
    pose_basis_change(units::position::Pose const&, framed_geometry::BaseChange const&);
    units::position::LinearDisplacement
    ld_basis_change(units::position::LinearDisplacement const&, framed_geometry::BaseChange const&);
    units::position::AngularDisplacement
    ad_basis_change(units::position::AngularDisplacement const&,
                    framed_geometry::BaseChange const&);
    units::position::SpatialDisplacement
    sd_basis_change(units::position::SpatialDisplacement const&,
                    framed_geometry::BaseChange const&);
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

namespace quant::traits
{

    using FramedPositionDomain =
        Define3DDomain<Define3DSubDomain<FramedPosition, FramedLinearDisplacement, R3Type>,
                       Define3DSubDomain<FramedOrientation, FramedAngularDisplacement, SO3Type>,
                       Define3DSubDomain<FramedPose, FramedSpatialDisplacement, SE3Type>>;

    template <>
    struct DefineFramedTraits<Position> :
        public traits_of<Position>
    {
        using FramedDomain = FramedPositionDomain;
        using FramedState = framed_units::position::Position;
        using FramedDifference = framed_units::position::LinearDisplacement;
        static constexpr auto basis_change_function =
            &framed_units::position::position_basis_change;
    };

    template <>
    struct DefineFramedTraits<LinearDisplacement> :
        public traits_of<LinearDisplacement>
    {
        using FramedDomain = FramedPositionDomain;
        using FramedDifference = framed_units::position::LinearDisplacement;
        using FramedState = framed_units::position::Position;
        static constexpr auto basis_change_function = framed_units::position::ld_basis_change;
    };

    template <>
    struct DefineFramedTraits<Orientation> :
        public traits_of<Orientation>
    {
        using FramedDomain = FramedPositionDomain;
        using FramedState = framed_units::position::Orientation;
        using FramedDifference = framed_units::position::AngularDisplacement;
        static constexpr auto basis_change_function =
            framed_units::position::orientation_basis_change;
    };

    template <>
    struct DefineFramedTraits<AngularDisplacement> :
        public traits_of<AngularDisplacement>
    {
        using FramedDomain = FramedPositionDomain;
        using FramedDifference = framed_units::position::AngularDisplacement;
        using FramedState = framed_units::position::Orientation;
        static constexpr auto basis_change_function = framed_units::position::ad_basis_change;
    };

    template <>
    struct DefineFramedTraits<Pose> : public traits_of<Pose>
    {
        using FramedDomain = FramedPositionDomain;
        using FramedState = framed_units::position::Pose;
        using FramedDifference = framed_units::position::SpatialDisplacement;
        static constexpr auto basis_change_function = framed_units::position::pose_basis_change;
    };

    template <>
    struct DefineFramedTraits<SpatialDisplacement> :
        public traits_of<SpatialDisplacement>
    {
        using FramedDomain = FramedPositionDomain;
        using FramedDifference = framed_units::position::SpatialDisplacement;
        using FramedState = framed_units::position::Pose;
        static constexpr auto basis_change_function = framed_units::position::sd_basis_change;
    };

}  // namespace quant::traits
