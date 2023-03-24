#pragma once

namespace quant::geometry
{

    class Vector;

    class AxisAngle;

    template <typename BaseQuantityT>
    class Difference;

    template <typename BaseQuantityT>
    class LinearDifference;

    template <typename BaseQuantityT>
    class AngularDifference;

    template <typename BaseQuantityT>
    struct DefineDifferenceType;

    template <typename BaseQuantityT>
    using DifferenceTypeOf = typename DefineDifferenceType<BaseQuantityT>::DifferenceType;

    template <typename BaseQuantityT, typename ScalarType = double>
    class ScalarQuantity;

    template <typename BaseQuantityT>
    class ScalarIntQuantity;

    template <typename BaseQuantityT>
    class VectorQuantity;

    template <typename BaseQuantityT>
    class QuaternionQuantity;

    template <typename BaseQuantityT>
    class IsometryQuantity;

    template <typename Linear, typename Angular, typename Derived>
    class Spatial;

}  // namespace quant::geometry

namespace quant
{

    using geometry::AngularDifference;
    using geometry::AxisAngle;
    using geometry::Difference;
    using geometry::DifferenceTypeOf;
    using geometry::LinearDifference;
    using geometry::Spatial;
    using geometry::Vector;

}  // namespace quant
