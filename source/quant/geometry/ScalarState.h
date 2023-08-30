#pragma once

#include <quant/geometry/Scalar.h>
#include <quant/geometry/constants.h>
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/geometry_fwd.h>

#include <compare>
#include <sstream>

namespace quant::geometry
{

    template <typename StateType, typename RepresentationType = double>
    class ScalarState
    {
    public:
        // Construct.

        ScalarState() : _representation{0}
        {
            ;
        }

        static StateType
        zero()
        {
            return StateType(0);
        }

        // Scale.

        StateType
        operator*(long const rhs) const
        {
            return StateType(_representation * rhs);
        }

        StateType
        operator/(long const rhs) const
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
    operator*(long lhs, StateType const& rhs)
    {
        return rhs * lhs;
    }

    template <typename StateType>
        requires quant::traits::scalar_state<StateType>
    StateType
    operator/(long lhs, StateType const& rhs)
    {
        return rhs / lhs;
    }

}  // namespace quant::geometry
