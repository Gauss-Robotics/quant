#pragma once

#include <quant/geometry/detail/Accessors.h>
#include <quant/geometry_fwd.h>

#include <type_traits>
#include <typeinfo>

namespace quant::geometry
{

    /**
     * Represents the difference of two objects of type QuantityT.
     */
    template <typename QuantityT>
    class Difference
    {
    public:
        Difference() : differenceObject_{}
        {
            ;
        }

        explicit Difference(QuantityT const& differenceObject) : differenceObject_{differenceObject}
        {
            ;
        }

        bool
        operator==(Difference<QuantityT> const& rhs) const
        {
            return differenceObject_ == rhs.differenceObject_;
        }

        bool
        operator!=(Difference<QuantityT> const& rhs) const
        {
            return differenceObject_ != rhs.differenceObject_;
        }

        using DifferenceObjectType = QuantityT;

    protected:
        QuantityT differenceObject_;
    };

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
        using GeometricType = DifferenceType;
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
        using GeometricType = DifferenceType;
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

        static typename Domain::AngularState
        Zero()
        {
            return typename Domain::AngularState::Zero();
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
        using GeometricType = DifferenceType;
        using DomainType = Domain;

        friend class detail::DifferenceAccessor<typename Domain::AngularDifference,
                                                AngularDifference<Domain>>;
    };

}  // namespace quant::geometry
