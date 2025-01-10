#pragma once

#include <quant/geometry/forward_declarations.h>
#include <quant/units/forward_declarations.h>

#include <concepts>
#include <cstdint>

namespace quant::framed_geometry
{

    /**
     * @brief Maximum number of characters or byte used for a frame identifier (name or base_frame).
     */
    constexpr std::uint32_t frame_data_max_string_size = 128;

    struct FrameData;

    struct Difference;

    template <typename QuantityT>
    struct FrameConversion;

}  // namespace quant::framed_geometry

namespace quant::traits
{

    template <typename Type>
    struct DefineFramedTraits
    {
    };

    template <typename Type>
    using framed_traits_of = DefineFramedTraits<Type>;

    template <typename QuantityT>
    concept has_frame_conversion =
        requires(QuantityT& pose, units::position::SpatialDisplacement const& transform) {
            {
                framed_geometry::FrameConversion<QuantityT>::convert(pose, transform)
            } -> std::same_as<QuantityT&>;
        };

    template <typename Type>
    concept is_frameable = has_frame_conversion<Type> && three_dimensional_domain<Type>;

    /**
     * @brief Concept of a framed type.
     */
    template <typename Type>
    concept framed = requires { typename Type::FramedGeometricObject; };

    template <typename Type>
    concept framed_state = framed<Type> and state<typename Type::FramedGeometricObject>;

    template <typename Type>
    concept framed_scalar_state =
        framed<Type> and scalar_state<typename Type::FramedGeometricObject>;

    template <typename Type>
    concept framed_scalar_difference =
        framed<Type> and scalar_difference<typename Type::FramedGeometricObject>;

    template <typename Type>
    using framed_domain_type_of =
        typename framed_traits_of<typename Type::FramedGeometricObject>::FramedDomain;

    template <typename Type1, typename Type2>
    concept same_framed_domain =
        std::same_as<framed_domain_type_of<Type1>, framed_domain_type_of<Type2>>;

}  // namespace quant::traits

namespace quant::framed_geometry
{
    template <typename T>
        requires traits::is_frameable<T>
    class Framed;
}

namespace quant
{

    using framed_geometry::Framed;
    using framed_geometry::FrameData;

}  // namespace quant

namespace quant::traits
{
    namespace detail
    {

        template <typename Type, typename = void>
        struct evaluate_framed_type
        {
            using FramedType = framed_geometry::Framed<Type>;
        };

        template <typename Type>
        struct evaluate_framed_type<Type, std::void_t<typename framed_traits_of<Type>::Framed>>
        {
            using FramedType = typename framed_traits_of<Type>::Framed;
        };

    }  // namespace detail

    template <typename Type>
    using framed_type_of = typename detail::evaluate_framed_type<Type>::FramedType;
}  // namespace quant::traits