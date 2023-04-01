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
            using State = QuantityAccessor<typename DifferenceT::StateType>;
            return State::representation(d.difference_object_);
        }

        static DifferenceT
        make(typename DifferenceT::GeometricRepresentationType difference_object)
        {
            using State = QuantityAccessor<typename DifferenceT::StateType>;
            return DifferenceT(State::make(difference_object));
        }
    };

}  // namespace quant::geometry::detail
