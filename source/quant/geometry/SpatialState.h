#pragma once

#include <quant/geometry/Difference.h>
#include <quant/geometry/forward_declarations.h>

namespace quant::geometry
{

    template <typename StateType>
    class SpatialState
    {
    public:
        using LinearStateType = traits::linear_state_in_domain_of<StateType>;
        using AngularStateType = traits::angular_state_in_domain_of<StateType>;
        using LinearDifferenceType = traits::linear_difference_in_domain_of<StateType>;
        using AngularDifferenceType = traits::angular_difference_in_domain_of<StateType>;

        SpatialState(LinearStateType linear, AngularStateType angular) :
            _linear{linear}, _angular{angular}
        {
            ;
        }

        static StateType
        zero()
        {
            return StateType(LinearStateType::zero(), AngularStateType::zero());
        }

        LinearStateType
        linear() const
        {
            return _linear;
        }

        AngularStateType
        angular() const
        {
            return _angular;
        }

        friend StateType
        operator+(LinearDifferenceType const& op, StateType const& rhs)
        {
            return StateType(op + rhs._linear, rhs._angular);
        }

        friend StateType
        operator-(LinearStateType const& op, StateType const& rhs)
        {
            return StateType(rhs._linear - op, rhs._angular);
        }

        friend StateType
        operator*(AngularDifferenceType const& op, StateType const& rhs)
        {
            return StateType(rhs._linear, op * rhs._angular);
        }

        friend StateType
        operator-(AngularStateType const& op, StateType const& rhs)
        {
            return StateType(rhs._linear, rhs._angular - op);
        }

    protected:
        LinearStateType _linear;
        AngularStateType _angular;
    };

}  // namespace quant::geometry
