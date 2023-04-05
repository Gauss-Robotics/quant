#pragma once

#include <quant/geometry/Difference.h>
#include <quant/geometry_fwd.h>

namespace quant::geometry
{

    template <typename Domain>
    class SpatialState
    {
    public:
        SpatialState(typename Domain::LinearState linear, typename Domain::AngularState angular) :
            _linear{linear}, _angular{angular}
        {
            ;
        }

        static typename Domain::SpatialState
        zero()
        {
            using Linear = typename Domain::LinearState;
            using Angular = typename Domain::AngularState;
            return typename Domain::SpatialState(Linear::zero(), Angular::zero());
        }

        typename Domain::LinearState
        linear() const
        {
            return _linear;
        }

        typename Domain::AngularState
        angular() const
        {
            return _angular;
        }

        friend typename Domain::SpatialState
        operator+(typename Domain::LinearDifference const& op,
                  typename Domain::SpatialState const& rhs)
        {
            return typename Domain::SpatialState(op + rhs._linear, rhs._angular);
        }

        friend typename Domain::SpatialState
        operator-(typename Domain::LinearState const& op, typename Domain::SpatialState const& rhs)
        {
            return typename Domain::SpatialState(rhs._linear - op, rhs._angular);
        }

        friend typename Domain::SpatialState
        operator+(typename Domain::AngularDifference const& op,
                  typename Domain::SpatialState const& rhs)
        {
            return typename Domain::SpatialState(rhs._linear, op * rhs._angular);
        }

        friend typename Domain::SpatialState
        operator-(typename Domain::AngularState const& op, typename Domain::SpatialState const& rhs)
        {
            return typename Domain::SpatialState(rhs._linear, rhs._angular - op);
        }

        using GeometricType = traits::StateType;

    protected:
        typename Domain::LinearState _linear;
        typename Domain::AngularState _angular;
    };

}  // namespace quant::geometry
