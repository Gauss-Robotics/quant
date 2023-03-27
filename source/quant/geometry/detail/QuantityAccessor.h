#pragma once

#include <quant/geometry_fwd.h>

namespace quant::geometry::detail
{

    template <typename BaseQuantityT>
    class QuantityAccessor
    {
    public:
        static typename BaseQuantityT::GeometricRepresentationType
        representation(BaseQuantityT const& vq)
        {
            return vq.representation_;
        }

        static BaseQuantityT
        make(typename BaseQuantityT::GeometricRepresentationType representation)
        {
            return BaseQuantityT(representation);
        }
    };

}  // namespace quant::geometry::detail
