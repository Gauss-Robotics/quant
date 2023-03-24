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
    /*typename std::enable_if_t<
        std::is_base_of_v<ScalarQuantity<QuantityT, std::int64_t>, QuantityT> or
            std::is_base_of_v<VectorQuantity<QuantityT>, QuantityT>,*/
    DifferenceTypeOf<QuantityT>  //>
    operator-(QuantityT const& lhs, QuantityT const& rhs)
    {
        using acc = detail::Accessor<QuantityT>;
        return DifferenceTypeOf<QuantityT>(
            acc::make(acc::representation(lhs) - acc::representation(rhs)));
    }

    template <typename QuantityT>
    class LinearDifference : public Difference<QuantityT>
    {
    public:
        using Difference<QuantityT>::Difference;

        QuantityT
        operator+(QuantityT const& rhs) const
        {
            using acc = detail::Accessor<QuantityT>;
            return acc::make(acc::representation(this->differenceObject_) +
                             acc::representation(rhs));
        }
    };

    template <typename QuantityT>
    class AngularDifference : public Difference<QuantityT>
    {
    public:
        using Difference<QuantityT>::Difference;

        QuantityT
        operator*(QuantityT const& rhs) const
        {
            using acc = detail::Accessor<QuantityT>;
            return acc::make(acc::representation(this->differenceObject_) *
                             acc::representation(rhs));
        }
    };

}  // namespace quant::geometry
