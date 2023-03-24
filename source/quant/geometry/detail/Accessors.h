#pragma once

#include <quant/geometry_fwd.h>

#include <Eigen/Core>

namespace quant::geometry::detail
{

    template <typename BaseQuantityT>
    class Accessor
    {
    public:
        static typename BaseQuantityT::Representation
        representation(BaseQuantityT const& vq)
        {
            return vq.representation_;
        }

        static BaseQuantityT
        make(typename BaseQuantityT::Representation representation)
        {
            return BaseQuantityT(representation);
        }

        static typename BaseQuantityT::Representation
        add(BaseQuantityT const& rhs, BaseQuantityT const& lhs)
        {
            return rhs + lhs;
        }
    };

}  // namespace quant::geometry::detail
