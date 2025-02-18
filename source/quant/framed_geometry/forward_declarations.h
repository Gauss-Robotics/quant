#pragma once

#include <quant/geometry/forward_declarations.h>
#include <quant/units/forward_declarations.h>

#include <concepts>
#include <cstdint>
#include <functional>

namespace quant::framed_geometry
{
    struct BaseChange;
}

namespace quant::traits
{

    template <typename Type>
    struct DefineFramedTraits
    {
    };

    template <typename Type>
    concept framed_traits_structure = requires {
        typename DefineFramedTraits<Type>::FramedDomain;
        typename DefineFramedTraits<Type>::FramedState;
        typename DefineFramedTraits<Type>::FramedDifference;
    } and traits_structure<Type>;

    template <typename Type>
        requires framed_traits_structure<Type>
    using framed_traits_of = DefineFramedTraits<Type>;

    /**
     * @brief Concept of a framed type.
     */
    template <typename Type>
    concept framed = requires { typename Type::FramedGeometricObject; };

    template <typename Type>
    concept framed_state = framed<Type> and state<typename Type::FramedGeometricObject>;

    template <typename Type>
    concept framed_difference = framed<Type> and difference<typename Type::FramedGeometricObject>;

    template <typename Type>
    concept framed_scalar_state =
        framed<Type> and scalar_state<typename Type::FramedGeometricObject>;

    template <typename Type>
    concept framed_spatial_state =
        framed<Type> and spatial_state<typename Type::FramedGeometricObject>;

    template <typename Type>
    concept framed_scalar_difference =
        framed<Type> and scalar_difference<typename Type::FramedGeometricObject>;

    template <typename Type>
    using framed_domain_type_of =
        typename framed_traits_of<typename Type::FramedGeometricObject>::FramedDomain;

    template <typename Type1, typename Type2>
    concept same_framed_domain =
        std::same_as<framed_domain_type_of<Type1>, framed_domain_type_of<Type2>>;

    template <typename Type>
        requires state<Type> or difference<Type>
    using framed_type_of = std::conditional_t<state<Type>,
                                              typename framed_traits_of<Type>::FramedState,
                                              typename framed_traits_of<Type>::FramedDifference>;

    template <typename Type>
        requires framed_difference<Type>
    using framed_state_of = typename framed_traits_of<Type>::FramedState;

    template <typename Type>
        requires framed_state<Type>
    using framed_difference_of = typename framed_traits_of<Type>::FramedDifference;

    template <typename Type>
        requires framed<Type>
    using unframed_type_of = typename Type::FramedGeometricObject;

    template <typename QuantityT>
    concept has_frame_conversion =
        requires(QuantityT const& quantity, framed_geometry::BaseChange const& transform) {
            {
                framed_traits_of<QuantityT>::basis_change_function(quantity, transform)
            } -> std::same_as<QuantityT>;
        };

    template <typename Type>
    concept is_frameable = three_dimensional_domain<Type>;

}  // namespace quant::traits

namespace quant::framed_geometry
{

    /**
     * @brief Maximum number of characters or byte used for a frame identifier (name or base_frame).
     */
    constexpr std::uint32_t frame_data_max_string_size = 128;

    using const_size_string = std::array<char, frame_data_max_string_size>;

    struct FrameIdentifier;

    template <typename T>
        requires traits::is_frameable<T> and traits::state<T>
    class State;
    template <typename T>
        requires traits::is_frameable<T> and traits::difference<T>
    class Difference;
}  // namespace quant::framed_geometry

namespace quant
{

    template <typename T>
    using FramedDifference = framed_geometry::Difference<T>;
    template <typename T>
    using FramedState = framed_geometry::State<T>;
    using framed_geometry::BaseChange;
    using framed_geometry::FrameIdentifier;

}  // namespace quant