#pragma once

#include <quant/geometry/Scalar.h>
#include <quant/geometry/constants.h>
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/geometry/forward_declarations.h>

#include <compare>
#include <cstdint>

namespace quant::geometry
{

    template <typename StateType, typename RepresentationType = double>
    class ScalarState
    {
    public:
        static StateType
        zero()
        {
            return StateType{0};
        }

        // Scale.

        StateType
        operator-() const
        {
            return StateType{-_representation};
        }

        StateType
        operator*(std::int64_t const rhs) const
        {
            return StateType(_representation * rhs);
        }

        StateType
        operator/(std::int64_t const rhs) const
        {
            return StateType(_representation / rhs);
        }

        /**
         * @brief Calculate the ratio of two states.
         *
         * @param rhs Other state.
         * @return Ratio of the two states as double.
         */
        double
        operator/(StateType const& rhs) const
        {
            return _representation / rhs._representation;
        }

        // Compare.

        bool
        operator==(StateType const& rhs) const
        {
            return _representation == rhs._representation;
        }

        bool
        operator!=(StateType const& rhs) const
        {
            return _representation != rhs._representation;
        }

        std::strong_ordering
        operator<=>(StateType const& rhs) const
        {
            return _representation <=> rhs._representation;
        }

        bool
        is_approx(StateType const& rhs,
                  double tolerance = constants::floating_point_tolerance) const
        {
            return std::abs(_representation - rhs._representation) < tolerance;
        }

        using GeometricRepresentationType = RepresentationType;

    protected:
        // Construct.

        ScalarState() : _representation{0}
        {
            ;
        }

        ScalarState(Scalar scalar) : _representation{scalar}
        {
            ;
        }

        Scalar
        to_scalar() const
        {
            return _representation;
        }

        RepresentationType _representation;

        friend class detail::StateAccessor<StateType>;
    };

    template <typename StateType>
        requires quant::traits::scalar_state<StateType>
    StateType
    operator*(std::int64_t lhs, StateType const& rhs)
    {
        return rhs * lhs;
    }

    template <typename StateType>
        requires quant::traits::scalar_state<StateType>
    StateType
    operator/(std::int64_t lhs, StateType const& rhs)
    {
        return rhs / lhs;
    }

    /**
     * @brief Add two scalar states.
     *
     * @param lhs Left-hand-side summand scalar state.
     * @param lhs Right-hand-side summand scalar state.
     * @return Sum of the two scalar states.
     */
    // template <typename ScalarStateType>
    //     requires traits::scalar_state<ScalarStateType>
    // ScalarStateType
    // operator+(ScalarStateType const& lhs, ScalarStateType const rhs)
    // {
    //     using ScalarState = detail::StateAccessor<ScalarStateType>;
    //
    //     return ScalarState::make(ScalarState::representation(lhs) +
    //                                   ScalarState::representation(rhs));
    // }

}  // namespace quant::geometry
