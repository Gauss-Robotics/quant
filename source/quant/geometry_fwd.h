#pragma once

#include <cinttypes>

namespace quant::geometry
{

    template <typename Domain>
    struct InstantiateDomain;

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

    struct StateType
    {
    };

    struct ScalarStateType : public StateType
    {
    };

    struct LinearStateType : public StateType
    {
    };

    struct AngularStateType : public StateType
    {
    };

    struct SpatialStateType : public StateType
    {
    };

    struct DifferenceType
    {
    };

    struct ScalarDifferenceType : public DifferenceType
    {
    };

    struct LinearDifferenceType : public DifferenceType
    {
    };

    struct AngularDifferenceType : public DifferenceType
    {
    };

    struct SpatialDifferenceType : public DifferenceType
    {
    };

    template <typename StateT>
    struct DefineDifferenceTypeOf
    {
        using DifferenceType = Difference<StateT>;
    };

    template <typename StateT>
    using DifferenceTypeOf = typename DefineDifferenceTypeOf<StateT>::DifferenceType;

    template <typename DifferenceT>
    struct DefineStateTypeOf
    {
        using StateType = typename DifferenceT::StateType;
    };

}  // namespace quant::geometry

namespace quant
{

    using geometry::AxisAngle;
    using geometry::Vector;

    using geometry::DifferenceTypeOf;

}  // namespace quant
