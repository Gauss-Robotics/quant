#pragma once

#include <quant/geometry/forward_declarations.h>

namespace quant::geometry::detail
{

    template <typename BaseQuantityT>
    class StateAccessor
    {
    public:
        static const typename BaseQuantityT::GeometricRepresentationType&
        representation(BaseQuantityT const& vq)
        {
            return vq._representation;
        }

        static typename BaseQuantityT::GeometricRepresentationType&
        representation(BaseQuantityT& vq)
        {
            return vq._representation;
        }

        static BaseQuantityT
        make(typename BaseQuantityT::GeometricRepresentationType representation)
        {
            return BaseQuantityT(representation);
        }
    };

}  // namespace quant::geometry::detail
