#pragma once

#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/geometry/detail/QuantityAccessor.h>
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

        static QuantityT
        zero()
        {
            return QuantityT::Zero();
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

        using StateType = QuantityT;

    protected:
        QuantityT differenceObject_;
    };

    /**
     * SFINAE type and alias for a difference of quantities.
     */
    template <typename QuantityT>
    using QuantityDifference =
        std::enable_if_t<traits::isState<QuantityT>, traits::DifferenceTypeOf<QuantityT>>;

    /**
     * Difference operator for quantities.
     */
    template <typename QuantityT>
    QuantityDifference<QuantityT>
    operator-(QuantityT const& lhs, QuantityT const& rhs)
    {
        using State = detail::QuantityAccessor<QuantityT>;
        using Difference = detail::DifferenceAccessor<traits::DifferenceTypeOf<QuantityT>,
                                                      traits::DifferenceTypeOf<QuantityT>>;

        return Difference::make(State::representation(lhs) - State::representation(rhs));
    }

}  // namespace quant::geometry
