#pragma once

#include <cinttypes>

namespace quant::geometry
{

    class Vector;

    class AxisAngle;

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

    struct DifferenceType
    {
    };

    template <typename BaseQuantityT>
    class Difference;

    template <typename Domain>
    class ScalarDifference;

    template <typename Domain>
    class LinearDifference;

    template <typename Domain>
    class AngularDifference;

    template <typename BaseQuantityT, typename ScalarType = double>
    class ScalarQuantity;

    template <typename T>
    using ScalarIntegerQuantity = ScalarQuantity<T, std::int64_t>;

    template <typename BaseQuantityT>
    class VectorQuantity;

    template <typename BaseQuantityT>
    class QuaternionQuantity;

    template <typename BaseQuantityT>
    class IsometryQuantity;

    template <typename Domain>
    class Spatial;

}  // namespace quant::geometry

namespace quant
{

    using geometry::AngularDifference;
    using geometry::AxisAngle;
    using geometry::Difference;
    using geometry::LinearDifference;
    using geometry::ScalarDifference;
    using geometry::Spatial;
    using geometry::Vector;

}  // namespace quant
