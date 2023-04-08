#pragma once

#include <quant/geometry/Scalar.h>
#include <quant/geometry/constants.h>
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/geometry_fwd.h>

#include <sstream>

namespace quant::geometry
{

    template <typename Domain>
    class ScalarState
    {
    public:
        // Construct.

        ScalarState() : _representation{0}
        {
            ;
        }

        static typename Domain::State
        zero()
        {
            return typename Domain::State(0);
        }

        // Compare.

        bool
        operator==(typename Domain::State const& rhs) const
        {
            return _representation == rhs._representation;
        }

        bool
        operator!=(typename Domain::State const& rhs) const
        {
            return _representation != rhs._representation;
        }

        bool
        is_approx(typename Domain::State const& rhs,
                  double tolerance = constants::floating_point_tolerance) const
        {
            return std::abs(_representation - rhs._representation) < tolerance;
        }

        using GeometricRepresentationType = double;
        using GeometricType = traits::StateType;

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

        friend class detail::QuantityAccessor<typename Domain::State>;
    };

}  // namespace quant::geometry
