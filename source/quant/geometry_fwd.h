#pragma once

#include <cinttypes>

namespace quant::geometry
{

    class Vector;
    class AxisAngle;

    template <typename BaseQuantityT, typename ScalarType = double>
    class ScalarState;

    template <typename T>
    using ScalarIntegerState = ScalarState<T, std::int64_t>;

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

}  // namespace quant::geometry

namespace quant
{

    using geometry::AxisAngle;
    using geometry::Vector;

}  // namespace quant
