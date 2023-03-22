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

        T const&
        pointFromOrigin() const
        {
            // point.deltaToOrigin() = delta = point - origin
            // delta.pointFromOrigin() = point = delta + origin
            return differenceObject_;
        }

        bool
        operator==(Difference<T> const& rhs) const
        {
            return this->differenceObject_ == rhs.differenceObject_;
        }

        bool
        operator!=(Difference<T> const& rhs) const
        {
            return this->differenceObject_ != rhs.differenceObject_;
        }

    protected:
        T differenceObject_;
    };

    template <typename T>
    T
    operator+(typename DefineDifferenceType<T>::DifferenceType const& lhs, T const& rhs);

    template <typename T>
    typename DefineDifferenceType<T>::DifferenceType
    operator-(T const& lhs, T const& rhs);

}  // namespace quant::geometry

namespace quant
{

    using geometry::Difference;

}  // namespace quant
