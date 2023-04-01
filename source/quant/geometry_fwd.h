#pragma once

#include <cinttypes>
#include <type_traits>

namespace quant::geometry
{

    class Vector;
    class AxisAngle;

    template <typename BaseQuantityT, typename ScalarType = double>
    class ScalarState;

    template <typename BaseQuantityT>
    using ScalarIntegerState = ScalarState<BaseQuantityT, /* ScalarType = */ std::int64_t>;

    template <typename BaseQuantityT>
    class LinearState;

    template <typename BaseQuantityT>
    class AngularState;

    template <typename BaseQuantityT>
    class SpatialIsometricState;

    template <typename Domain>
    class SpatialState;

    template <typename BaseQuantityT>
    class Difference;

    template <typename Domain>
    class ScalarDifference;

    template <typename Domain>
    class LinearDifference;

    template <typename Domain>
    class AngularDifference;

    template <typename Domain>
    class SpatialDifference;

}  // namespace quant::geometry

namespace quant::traits
{

    struct StateType
    {
    };

    struct DifferenceType
    {
    };

    template <typename StateT>
    struct DefineDifferenceTypeOf
    {
        using DifferenceType = quant::geometry::Difference<StateT>;
    };

    template <typename StateT>
    using DifferenceTypeOf = typename DefineDifferenceTypeOf<StateT>::DifferenceType;

    template <typename DifferenceT>
    struct DefineStateTypeOf
    {
        using StateType = typename DifferenceT::StateType;
    };

    template <typename StateT>
    using StateTypeOf = typename DefineStateTypeOf<StateT>::StateType;

    template <typename Type, typename = void>
    inline constexpr bool isState = false;

    template <typename Type>
    inline constexpr bool
        isState<Type, std::void_t<std::is_same<typename Type::GeometricType, StateType>>> = true;

}  // namespace quant::traits

namespace quant
{

    using geometry::AxisAngle;
    using geometry::Vector;

}  // namespace quant
