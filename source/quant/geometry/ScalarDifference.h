#pragma once

#include <quant/geometry/Difference.h>
#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/geometry_fwd.h>

#include <type_traits>
#include <typeinfo>

namespace quant::geometry
{

    /**
     * Models a scalar difference.
     */
    template <typename Domain>
    class ScalarDifference : public Difference<typename Domain::State>
    {
    public:
        explicit ScalarDifference(typename Domain::State const& difference_object) :
            Difference<typename Domain::State>(difference_object)
        {
            ;
        }

        typename Domain::State
        operator+(typename Domain::State const& rhs) const
        {
            using State = detail::QuantityAccessor<typename Domain::State>;
            using Difference =
                detail::DifferenceAccessor<typename Domain::Difference, ScalarDifference<Domain>>;
            return State::make(Difference::representation(*this) + State::representation(rhs));
        }

        using Difference<typename Domain::State>::Difference;

        using GeometricRepresentationType = typename Domain::State::GeometricRepresentationType;

        friend class detail::DifferenceAccessor<typename Domain::Difference,
                                                ScalarDifference<Domain>>;
    };

}  // namespace quant::geometry
