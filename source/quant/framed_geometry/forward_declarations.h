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
    concept framed_state_structure = requires {
            typename DefineFramedTraits<Type>::FramedDomain;
            typename DefineFramedTraits<Type>::Framed;
            typename DefineFramedTraits<Type>::FramedDifference;
    };
    // TODO: should there be two different trait structures?
    template <typename Type>
    concept framed_difference_structure = requires {
        typename DefineFramedTraits<Type>::FramedDomain;
        typename DefineFramedTraits<Type>::Framed;
        typename DefineFramedTraits<Type>::FramedState;
    };

    template <typename Type>
        requires framed_state_structure<Type> or framed_difference_structure<Type>
    using framed_traits_of = DefineFramedTraits<Type>;

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

    template <typename Type>
    using framed_type_of = typename framed_traits_of<Type>::Framed;

    template <typename QuantityT>
    concept has_frame_conversion =
        requires(framed_geometry::BaseChange const& transform, const QuantityT& quantity) {
        {
            transform * quantity
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
        requires traits::is_frameable<T>
    class Framed;
}

namespace quant
{

    using framed_geometry::Framed;
    using framed_geometry::FrameIdentifier;

}  // namespace quant