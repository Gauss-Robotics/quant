#pragma once

#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/geometry_fwd.h>

#include <type_traits>
#include <typeinfo>

namespace quant::geometry
{

    /**
     * Represents the difference of two states of type `QuantityT`.
     */
    template <typename QuantityT>
    class Difference
    {
    public:
        Difference() : difference_object_{}
        {
            ;
        }

        explicit Difference(QuantityT const& difference_object) :
            difference_object_{difference_object}
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
            return difference_object_ == rhs.difference_object_;
        }

        bool
        operator!=(Difference<QuantityT> const& rhs) const
        {
            return difference_object_ != rhs.difference_object_;
        }

        using StateType = QuantityT;

    protected:
        QuantityT difference_object_;
    };

    /**
     * @brief SFINAE type and alias for a difference of quantities.
     *
     * If `QuantityT` is a state, this type evaluates to the defined difference type of `QuantityT`
     * via `traits::DifferenceTypeOf<QuantityT>`, otherwise this type will result in substitution
     * failure.
     */
    template <typename QuantityT>
    using QuantityDifference =
        std::enable_if_t<traits::is_state<QuantityT>, traits::DifferenceTypeOf<QuantityT>>;

    /**
     * @brief Generic difference operator.
     *
     * Returns the difference of the left-hand-side and right-hand-side either as the defined
     * difference type of the template type QuantityT, or generally as `Difference<QuantityT>` if
     * and only if `QuantityT` is a state.
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
