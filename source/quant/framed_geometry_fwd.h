#pragma once

#include <quant/geometry_fwd.h>

namespace quant::framed_geometry
{

    struct FrameData;

    template <typename T>
    class Framed;

}  // namespace quant::framed_geometry

namespace quant::traits
{

    template <typename Type>
    struct DefineFramedTraits
    {
    };

    template <typename Type>
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

namespace quant
{

    using framed_geometry::Framed;
    using framed_geometry::FrameData;

}  // namespace quant
