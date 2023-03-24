#pragma once

namespace quant::geometry
{

    template <typename BaseQuantityT>
    class Difference;

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

}  // namespace quant::geometry

namespace quant
{

    using geometry::Difference;
    using geometry::DifferenceTypeOf;

}  // namespace quant
