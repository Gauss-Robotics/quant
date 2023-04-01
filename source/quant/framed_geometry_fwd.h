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

    /**
     * @brief Template meta programming utility to define the framed type of a type via template
     * specialization.
     *
     * Default is a `Framed<Quantity>`, but the built-in units usually have `FramedQuantity`
     * specialization with convenience APIs, defined operators, etc.
     *
     * Example: `FramedLinearDisplacement` is a specialized `Framed<LinearDisplacement>`.
     */
    template <typename Quantity>
    struct DefineFramedTypeOf
    {
        using FramedType = framed_geometry::Framed<Quantity>;
    };

    /**
     * @brief Lookup type def for semantic template resolution.
     */
    template <typename Quantity>
    using FramedTypeOf = typename DefineFramedTypeOf<Quantity>::FramedType;

}  // namespace quant::traits

namespace quant
{

    using framed_geometry::Framed;
    using framed_geometry::FrameData;

}  // namespace quant
