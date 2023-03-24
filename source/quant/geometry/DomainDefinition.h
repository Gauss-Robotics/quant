#pragma once

namespace quant::geometry
{

    /**
     * Template meta programming utility to define the framed type of a type via template
     * specialization.
     */
    template <typename QuantityT>
    struct DefineDifferenceType
    {
    };

    /**
     * Lookup type def for semantic template resolution.
     */
    template <typename QuantityT>
    using DifferenceTypeOf = typename DefineDifferenceType<QuantityT>::DifferenceType;

}  // namespace quant::geometry
