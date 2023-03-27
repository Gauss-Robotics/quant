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
        explicit ScalarDifference(typename Domain::State const& differenceObject) :
            Difference<typename Domain::State>(differenceObject)
        {
            ;
        }

        static typename Domain::State
        zero()
        {
            return typename Domain::State::Zero();
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
        using GeometricType = ScalarDifferenceType;
        using DomainType = Domain;

        friend class detail::DifferenceAccessor<typename Domain::Difference,
                                                ScalarDifference<Domain>>;
    };

    /**
     * SFINAE type and alias for a difference of scalar quantities.
     */
    template <typename QuantityT>
    using ScalarQuantityDifference =
        std::enable_if_t<std::is_same_v<typename QuantityT::GeometricType, ScalarStateType>,
                         typename QuantityT::DomainType::Difference>;

    /**
     * Difference operator for scalar quantities.
     */
    template <typename QuantityT>
    ScalarQuantityDifference<QuantityT>
    operator-(QuantityT const& lhs, QuantityT const& rhs)
    {
        using Domain = typename QuantityT::DomainType;
        using State = detail::QuantityAccessor<typename Domain::State>;
        using Difference =
            detail::DifferenceAccessor<typename Domain::Difference, ScalarDifference<Domain>>;
        return Difference::make(State::representation(lhs) - State::representation(rhs));
    }

}  // namespace quant::geometry
