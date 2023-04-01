#pragma once

#include <quant/geometry/Difference.h>
#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/geometry_fwd.h>

namespace quant::geometry
{

    /**
     * Models a linear difference.
     */
    template <typename Domain>
    class LinearDifference : public Difference<typename Domain::LinearState>
    {
    public:
        explicit LinearDifference(typename Domain::LinearState const& difference_object) :
            Difference<typename Domain::LinearState>(difference_object)
        {
            ;
        }

        typename Domain::LinearState
        operator+(typename Domain::LinearState const& rhs) const
        {
            using LinearState = detail::QuantityAccessor<typename Domain::LinearState>;
            using LinearDifference = detail::DifferenceAccessor<typename Domain::LinearDifference,
                                                                LinearDifference<Domain>>;
            return LinearState::make(LinearDifference::representation(*this) +
                                     LinearState::representation(rhs));
        }

        using Difference<typename Domain::LinearState>::Difference;

        using GeometricRepresentationType =
            typename Domain::LinearState::GeometricRepresentationType;

        friend class detail::DifferenceAccessor<typename Domain::LinearDifference,
                                                LinearDifference<Domain>>;
    };

}  // namespace quant::geometry
