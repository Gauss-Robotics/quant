#pragma once

#include <quant/geometry/Scalar.h>
#include <quant/geometry/constants.h>
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/geometry_fwd.h>

#include <sstream>

namespace quant::geometry
{

    template <typename StateType>
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

        bool
        is_approx(StateType const& rhs,
                  double tolerance = constants::floating_point_tolerance) const
        {
            return std::abs(_representation - rhs._representation) < tolerance;
        }

        using GeometricRepresentationType = double;

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

        double _representation;

        friend class detail::StateAccessor<StateType>;
    };

}  // namespace quant::geometry
