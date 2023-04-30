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

    template <typename Type>
    concept framed = requires { typename framed_traits_of<Type>::Framed; };

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
