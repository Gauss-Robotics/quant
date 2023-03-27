#pragma once

#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/geometry_fwd.h>

namespace quant::geometry::detail
{

    template <typename DifferenceT, typename BaseDifferenceT>
    class DifferenceAccessor
    {
    public:
        static typename DifferenceT::GeometricRepresentationType
        representation(BaseDifferenceT const& d)
        {
            using State = QuantityAccessor<typename DifferenceT::DifferenceObjectType>;
            return State::representation(d.differenceObject_);
        }

        static DifferenceT
        make(typename DifferenceT::GeometricRepresentationType differenceObject)
        {
            using State = QuantityAccessor<typename DifferenceT::DifferenceObjectType>;
            return DifferenceT(State::make(differenceObject));
        }
    };

}  // namespace quant::geometry::detail
