#pragma once

#include <quant/geometry_fwd.h>

#include <Eigen/Core>

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

    template <typename DifferenceT>
    class DifferenceAccessor
    {
    public:
        static typename DifferenceT::GeometricRepresentationType
        representation(DifferenceT const& d)
        {
            return d.differenceObject_;
        }

        static DifferenceT
        make(typename DifferenceT::GeometricRepresentationType differenceObject)
        {
            return DifferenceT(differenceObject);
        }
    };

}  // namespace quant::geometry::detail
