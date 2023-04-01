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
            linear_{linear}, angular_{angular}
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
            return linear_;
        }

        typename Domain::AngularState
        angular() const
        {
            return angular_;
        }

        friend typename Domain::SpatialState
        operator+(typename Domain::LinearDifference const& op,
                  typename Domain::SpatialState const& rhs)
        {
            return typename Domain::SpatialState(op + rhs.linear_, rhs.angular_);
        }

        friend typename Domain::SpatialState
        operator-(typename Domain::LinearState const& op, typename Domain::SpatialState const& rhs)
        {
            return typename Domain::SpatialState(rhs.linear_ - op, rhs.angular_);
        }

        friend typename Domain::SpatialState
        operator+(typename Domain::AngularDifference const& op,
                  typename Domain::SpatialState const& rhs)
        {
            return typename Domain::SpatialState(rhs.linear_, op * rhs.angular_);
        }

        friend typename Domain::SpatialState
        operator-(typename Domain::AngularState const& op, typename Domain::SpatialState const& rhs)
        {
            return typename Domain::SpatialState(rhs.linear_, rhs.angular_ - op);
        }

        using GeometricType = traits::StateType;

    protected:
        typename Domain::LinearState linear_;
        typename Domain::AngularState angular_;
    };

}  // namespace quant::geometry
