#pragma once

#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/geometry_fwd.h>

#include <type_traits>
#include <typeinfo>

namespace quant::geometry
{

    /**
     * Models an angular difference.
     */
    template <typename Domain>
    class AngularDifference : public Difference<typename Domain::AngularState>
    {
    public:
        explicit AngularDifference(typename Domain::AngularState const& differenceObject) :
            Difference<typename Domain::AngularState>(differenceObject)
        {
            ;
        }

        typename Domain::LinearState
        operator*(typename Domain::LinearState const& rhs) const
        {
            using LinearState = detail::QuantityAccessor<typename Domain::LinearState>;
            using AngularDifference = detail::DifferenceAccessor<typename Domain::AngularDifference,
                                                                 AngularDifference<Domain>>;
            return LinearState::make(AngularDifference::representation(*this) *
                                     LinearState::representation(rhs));
        }

        typename Domain::LinearDifference
        operator*(typename Domain::LinearDifference const& rhs) const
        {
            using AngularDifference = detail::DifferenceAccessor<typename Domain::AngularDifference,
                                                                 AngularDifference<Domain>>;
            using LinearDifference = detail::DifferenceAccessor<typename Domain::LinearDifference,
                                                                LinearDifference<Domain>>;
            return LinearDifference::make(AngularDifference::representation(*this) *
                                          LinearDifference::representation(rhs));
        }

        typename Domain::AngularState
        operator*(typename Domain::AngularState const& rhs) const
        {
            using AngularState = detail::QuantityAccessor<typename Domain::AngularState>;
            using AngularDifference = detail::DifferenceAccessor<typename Domain::AngularDifference,
                                                                 AngularDifference<Domain>>;
            return AngularState::make(AngularDifference::representation(*this) *
                                      AngularState::representation(rhs));
        }

        using Difference<typename Domain::AngularState>::Difference;

        using GeometricRepresentationType =
            typename Domain::AngularState::GeometricRepresentationType;
        using DomainType = Domain;

        friend class detail::DifferenceAccessor<typename Domain::AngularDifference,
                                                AngularDifference<Domain>>;
    };

}  // namespace quant::geometry
