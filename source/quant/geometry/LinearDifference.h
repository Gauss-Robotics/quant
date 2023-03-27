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
     * Models a linear difference.
     */
    template <typename Domain>
    class LinearDifference : public Difference<typename Domain::LinearState>
    {
    public:
        explicit LinearDifference(typename Domain::LinearState const& differenceObject) :
            Difference<typename Domain::LinearState>(differenceObject)
        {
            ;
        }

        static typename Domain::LinearState
        zero()
        {
            return typename Domain::LinearState::Zero();
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
        using GeometricType = LinearDifferenceType;
        using DomainType = Domain;

        friend class detail::DifferenceAccessor<typename Domain::LinearDifference,
                                                LinearDifference<Domain>>;
    };

    /**
     * SFINAE type and alias for a difference of linear quantities.
     */
    template <typename QuantityT>
    using LinearQuantityDifference =
        std::enable_if_t<std::is_same_v<typename QuantityT::GeometricType, LinearStateType>,
                         typename QuantityT::DomainType::LinearDifference>;

    /**
     * Difference operator for linear quantities.
     */
    template <typename QuantityT>
    LinearQuantityDifference<QuantityT>
    operator-(QuantityT const& lhs, QuantityT const& rhs)
    {
        using Domain = typename QuantityT::DomainType;
        using LinearState = detail::QuantityAccessor<typename Domain::LinearState>;
        using LinearDifference =
            detail::DifferenceAccessor<typename Domain::LinearDifference, LinearDifference<Domain>>;
        return LinearDifference::make(LinearState::representation(lhs) -
                                      LinearState::representation(rhs));
    }

}  // namespace quant::geometry
