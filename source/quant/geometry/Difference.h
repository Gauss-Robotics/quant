#pragma once

#include <quant/geometry_fwd.h>

namespace quant::geometry
{

    /**
     * Template meta programming utility to define the framed type of a type via template
     * specialization.
     */
    template <typename Type>
    struct DefineDifferenceType
    {
        using DifferenceType = Difference<Type>;
    };

    /**
     * Represents the difference of two objects of type T.
     */
    template <typename T>
    class Difference
    {
    public:
        Difference() : differenceObject_{}
        {
            ;
        }

        explicit Difference(T const& differenceObject) : differenceObject_{differenceObject}
        {
            ;
        }

        bool
        operator==(Difference<T> const& rhs) const
        {
            return differenceObject_ == rhs.differenceObject_;
        }

        bool
        operator!=(Difference<T> const& rhs) const
        {
            return differenceObject_ != rhs.differenceObject_;
        }

    public:
        T differenceObject_;
    };

    template <typename T>
    T
    operator+(typename DefineDifferenceType<T>::DifferenceType const& lhs, T const& rhs)
    {
        return lhs.differenceObject_.representation_ + rhs.representation_;
    }

    template <typename T>
    typename DefineDifferenceType<T>::DifferenceType
    operator-(T const& lhs, T const& rhs)
    {
        using DifferenceType = typename DefineDifferenceType<T>::DifferenceType;
        return DifferenceType(lhs.representation_ - rhs.representation_);
    }

}  // namespace quant::geometry

namespace quant
{

    using geometry::Difference;

}  // namespace quant
