#pragma once

#include <type_traits>

namespace quant::geometry
{

    struct Scalar;
    struct Vector;
    struct AxisAngle;

    template <typename BaseQuantityT>
    class ScalarState;

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

    template <typename T>
    class Circa;

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

    template <typename DifferenceT>
    using StateTypeOf = typename DefineStateTypeOf<DifferenceT>::StateType;

    /**
     * @brief Tests whether the given type `Type` is a geometric state (primary template).
     *
     * In case of `Type` not being a state, `std::is_same` in the specialized template will yield in
     * substitution failure, the primary template will be used, and `isState<Type>` will evaluate to
     * false.
     */
    template <typename Type, typename = void>
    inline constexpr bool is_state = false;

    /**
     * @brief Tests whether the given type `Type` is a geometric state (specialized template).
     *
     * If `Type` is a state, the primary template will be overridden and `isState<Type>` will
     * evaluate to `true`.
     */
    template <typename Type>
    inline constexpr bool
        is_state<Type, std::void_t<std::is_same<typename Type::GeometricType, StateType>>> = true;

    template <typename Type, typename = void>
    inline constexpr bool is_difference = false;

    template <typename Type>
    inline constexpr bool is_difference<Type, std::void_t<typename Type::StateType>> = true;

}  // namespace quant::traits

namespace quant
{

    using geometry::AxisAngle;
    using geometry::Circa;
    using geometry::Vector;

}  // namespace quant
