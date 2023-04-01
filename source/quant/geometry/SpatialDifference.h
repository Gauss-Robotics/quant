#pragma once

#include <quant/geometry/Difference.h>
#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/geometry_fwd.h>

namespace quant::geometry
{

    /**
     * Models a spatial difference.
     */
    template <typename Domain>
    class SpatialDifference : public Difference<typename Domain::SpatialState>
    {
    public:
        using Difference<typename Domain::SpatialState>::Difference;

        using GeometricRepresentationType =
            typename Domain::LinearState::GeometricRepresentationType;
        using GeometricType = traits::StateType;

        friend class detail::DifferenceAccessor<typename Domain::LinearDifference,
                                                LinearDifference<Domain>>;
    };

}  // namespace quant::geometry
