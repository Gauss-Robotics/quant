#pragma once

#include <quant/framed_geometry/forward_declarations.h>
#include <quant/geometry/forward_declarations.h>
#include <quant/units/position/forward_declarations.h>

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

namespace quant::framed_geometry
{
    template <typename Frame1T, typename Frame2T, typename LDType, typename ADType>
        requires std::convertible_to<Frame1T, std::string_view> and
                 std::convertible_to<Frame2T, std::string_view> and
                 std::constructible_from<LinearDisplacement, std::decay_t<LDType>> and
                 std::constructible_from<AngularDisplacement, std::decay_t<ADType>>
    struct BaseChangeBuilder<Frame1T, Frame2T, LDType, ADType>
    {
        static BaseChange
        build(Frame1T&& from_frame, Frame2T&& to_frame, LDType&& translation, ADType&& rotation)
        {
            return BaseChange(
                std::string_view(std::forward<Frame1T>(from_frame)),
                std::string_view(std::forward<Frame2T>(to_frame)),
                SpatialDisplacement(LinearDisplacement(std::forward<LDType>(translation)),
                                    AngularDisplacement(std::forward<ADType>(rotation))));
        }
    };

    template <typename Frame1T, typename Frame2T, typename LDType>
        requires std::convertible_to<Frame1T, std::string_view> and
                 std::convertible_to<Frame2T, std::string_view> and
                 std::constructible_from<LinearDisplacement, std::decay_t<LDType>>
    struct BaseChangeBuilder<Frame1T, Frame2T, LDType>
    {
        static BaseChange
        build(Frame1T&& from_frame, Frame2T&& to_frame, LDType&& translation)
        {
            return BaseChange(
                std::string_view(std::forward<Frame1T>(from_frame)),
                std::string_view(std::forward<Frame2T>(to_frame)),
                SpatialDisplacement(LinearDisplacement(std::forward<LDType>(translation)),
                                    AngularDisplacement::zero()));
        }
    };

    template <typename Frame1T, typename Frame2T, typename ADType>
        requires std::convertible_to<Frame1T, std::string_view> and
                 std::convertible_to<Frame2T, std::string_view> and
                 std::constructible_from<AngularDisplacement, std::decay_t<ADType>>
    struct BaseChangeBuilder<Frame1T, Frame2T, ADType>
    {
        static BaseChange
        build(Frame1T&& from_frame, Frame2T&& to_frame, ADType&& rotation)
        {
            return BaseChange(
                std::string_view(std::forward<Frame1T>(from_frame)),
                std::string_view(std::forward<Frame2T>(to_frame)),
                SpatialDisplacement(LinearDisplacement::zero(),
                                    AngularDisplacement(std::forward<ADType>(rotation))));
        }
    };

    template <typename Frame1T, typename Frame2T, typename SDType>
        requires std::convertible_to<Frame1T, std::string_view> and
                 std::convertible_to<Frame2T, std::string_view> and
                 std::constructible_from<SpatialDisplacement, std::decay_t<SDType>>
    struct BaseChangeBuilder<Frame1T, Frame2T, SDType>
    {
        static BaseChange
        build(Frame1T&& from_frame, Frame2T&& to_frame, SDType&& rotation)
        {
            return BaseChange(std::string_view(std::forward<Frame1T>(from_frame)),
                              std::string_view(std::forward<Frame2T>(to_frame)),
                              SpatialDisplacement(std::forward<SDType>(rotation)));
        }
    };

    template <typename FrameT, typename FSDType>
        requires std::convertible_to<FrameT, std::string_view> and
                 std::constructible_from<FramedSpatialDisplacement, std::decay_t<FSDType>>
    struct BaseChangeBuilder<FSDType, FrameT>
    {
        static BaseChange
        build(FSDType&& from, FrameT&& to_frame)
        {
            return BaseChange(from.get_base_frame(),
                              std::string_view(std::forward<FrameT>(to_frame)),
                              from.get_framed_object());
        }
    };

    template <typename FramedPose1T, typename FramedPose2T>
        requires std::is_same_v<FramedPose, std::decay_t<FramedPose1T>> and
                 std::is_same_v<FramedPose, std::decay_t<FramedPose2T>>
    struct BaseChangeBuilder<FramedPose1T, FramedPose2T>
    {
        static BaseChange
        build(FramedPose1T&& from, FramedPose2T&& to)
        {
            return BaseChange(from.get_name(), to.get_name(), to.rminus(from).get_framed_object());
        }
    };
}  // namespace quant::framed_geometry

namespace quant::traits
{

    using FramedPositionDomain =
        Define3DDomain<Define3DSubDomain<FramedPosition, FramedLinearDisplacement, R3Type>,
                       Define3DSubDomain<FramedOrientation, FramedAngularDisplacement, SO3Type>,
                       Define3DSubDomain<FramedPose, FramedSpatialDisplacement, SE3Type>>;

    template <>
    struct DefineFramedTraits<Position> : public traits_of<Position>
    {
        using FramedDomain = FramedPositionDomain;
        using FramedState = framed_units::position::Position;
        using FramedDifference = framed_units::position::LinearDisplacement;
        static constexpr auto basis_change_function =
            &framed_units::position::position_basis_change;
    };

    template <>
    struct DefineFramedTraits<LinearDisplacement> : public traits_of<LinearDisplacement>
    {
        using FramedDomain = FramedPositionDomain;
        using FramedDifference = framed_units::position::LinearDisplacement;
        using FramedState = framed_units::position::Position;
        static constexpr auto basis_change_function = framed_units::position::ld_basis_change;
    };

    template <>
    struct DefineFramedTraits<Orientation> : public traits_of<Orientation>
    {
        using FramedDomain = FramedPositionDomain;
        using FramedState = framed_units::position::Orientation;
        using FramedDifference = framed_units::position::AngularDisplacement;
        static constexpr auto basis_change_function =
            framed_units::position::orientation_basis_change;
    };

    template <>
    struct DefineFramedTraits<AngularDisplacement> : public traits_of<AngularDisplacement>
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
    struct DefineFramedTraits<SpatialDisplacement> : public traits_of<SpatialDisplacement>
    {
        using FramedDomain = FramedPositionDomain;
        using FramedDifference = framed_units::position::SpatialDisplacement;
        using FramedState = framed_units::position::Pose;
        static constexpr auto basis_change_function = framed_units::position::sd_basis_change;
    };

}  // namespace quant::traits
