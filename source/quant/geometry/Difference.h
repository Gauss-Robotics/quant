#pragma once

#include <quant/geometry/detail/Accessors.h>
#include <quant/geometry_fwd.h>

#include <type_traits>
#include <typeinfo>

namespace quant::geometry
{

    /**
     * Template meta programming utility to define the framed type of a type via template
     * specialization.
     */
    template <typename QuantityT>
    struct DefineDifferenceType
    {
        using DifferenceType = Difference<QuantityT>;
    };

    /**
     * Lookup type def for semantic template resolution.
     */
    template <typename QuantityT>
    using DifferenceTypeOf = typename DefineDifferenceType<QuantityT>::DifferenceType;

    /**
     * Represents the difference of two objects of type T.
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

    public:  // TODO(dreher) Shouldn't be public.
        QuantityT differenceObject_;
    };

    template <typename QuantityT>
    typename std::enable_if_t<std::is_same_v<typename QuantityT::GeometricType, ScalarStateType>,
                              DifferenceTypeOf<QuantityT>>
    operator-(QuantityT const& lhs, QuantityT const& rhs)
    {
        using sacc = detail::QuantityAccessor<QuantityT>;
        using dacc = detail::DifferenceAccessor<QuantityT>;
        return typename QuantityT::DomainType::Difference(
            dacc::make(sacc::representation(lhs) - sacc::representation(rhs)));
    }

    template <typename QuantityT>
    typename std::enable_if_t<std::is_same_v<typename QuantityT::GeometricType, LinearStateType>,
                              DifferenceTypeOf<QuantityT>>
    operator-(QuantityT const& lhs, QuantityT const& rhs)
    {
        using sacc = detail::QuantityAccessor<QuantityT>;
        using dacc = detail::DifferenceAccessor<QuantityT>;
        return typename QuantityT::DomainType::LinearDifference(
            dacc::make(sacc::representation(lhs) - sacc::representation(rhs)));
    }

    template <typename Domain>
    class ScalarDifference : public Difference<typename Domain::State>
    {
    public:
        using Difference<typename Domain::State>::Difference;

        explicit ScalarDifference(typename Domain::State const& differenceObject) :
            Difference<typename Domain::State>(differenceObject)
        {
            ;
        }

        static typename Domain::State
        Zero()
        {
            return typename Domain::State::Zero();
        }

        typename Domain::State
        operator+(typename Domain::State const& rhs) const
        {
            using acc = detail::QuantityAccessor<typename Domain::State>;
            return acc::make(acc::representation(this->differenceObject_) +
                             acc::representation(rhs));
        }

        using GeometricRepresentationType = typename Domain::State::GeometricRepresentationType;
        using GeometricType = DifferenceType;
        using DomainType = Domain;

        friend class detail::DifferenceAccessor<Domain>;
    };

    template <typename Domain>
    class LinearDifference : public Difference<typename Domain::LinearState>
    {
    public:
        using Difference<typename Domain::LinearState>::Difference;

        explicit LinearDifference(typename Domain::LinearState const& differenceObject) :
            Difference<typename Domain::LinearState>(differenceObject)
        {
            ;
        }

        static typename Domain::LinearState
        Zero()
        {
            return typename Domain::LinearState::Zero();
        }

        typename Domain::LinearState
        operator+(typename Domain::LinearState const& rhs) const
        {
            using lsacc = detail::QuantityAccessor<typename Domain::LinearState>;
            return lsacc::make(lsacc::representation(this->differenceObject_) +
                               lsacc::representation(rhs));
        }

        using GeometricRepresentationType =
            typename Domain::LinearState::GeometricRepresentationType;
        using GeometricType = DifferenceType;
        using DomainType = Domain;

        friend class detail::DifferenceAccessor<Domain>;
    };

    template <typename Domain>
    class AngularDifference : public Difference<typename Domain::AngularState>
    {
    public:
        using Difference<typename Domain::AngularState>::Difference;

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
            using lsacc = detail::QuantityAccessor<typename Domain::LinearState>;
            using asacc = detail::QuantityAccessor<typename Domain::AngularState>;
            return lsacc::make(asacc::representation(this->differenceObject_) *
                               lsacc::representation(rhs));
        }

        typename Domain::LinearDifference
        operator*(typename Domain::LinearDifference const& rhs) const
        {
            using lsacc = detail::QuantityAccessor<typename Domain::LinearState>;
            using asacc = detail::QuantityAccessor<typename Domain::AngularState>;
            using ldacc = detail::DifferenceAccessor<typename Domain::LinearDifference>;
            return ldacc::make(asacc::representation(this->differenceObject_) *
                               lsacc::representation(rhs.differenceObject_));
        }

        typename Domain::AngularState
        operator*(typename Domain::AngularState const& rhs) const
        {
            using asacc = detail::QuantityAccessor<typename Domain::AngularState>;
            return asacc::make(asacc::representation(this->differenceObject_) *
                               asacc::representation(rhs));
        }

        using GeometricRepresentationType =
            typename Domain::AngularState::GeometricRepresentationType;
        using GeometricType = DifferenceType;
        using DomainType = Domain;

        friend class detail::DifferenceAccessor<Domain>;
    };

}  // namespace quant::geometry
