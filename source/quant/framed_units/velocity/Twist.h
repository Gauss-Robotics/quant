#pragma once

#include <quant/framed_geometry/State.h>
#include <quant/framed_geometry/forward_declarations.h>
#include <quant/framed_units/velocity/AngularVelocity.h>
#include <quant/framed_units/velocity/LinearVelocity.h>
#include <quant/framed_units/velocity/forward_declarations.h>
#include <quant/units/velocity/Twist.h>

#include <ostream>

namespace quant::framed_units::velocity
{

    class Twist : public FramedState<units::velocity::Twist>
    {
    public:
        FramedAngularVelocity
        angular() const
        {
            return FramedAngularVelocity{get_framed_object().angular(),
                                         {get_name(), get_base_frame()}};
        }

        FramedLinearVelocity linear() const
        {
            return FramedLinearVelocity{get_framed_object().linear(),
                                        {get_name(), get_base_frame()}};
        }

        using State::State;
    };

    std::ostream&
    operator<<(std::ostream& os, Twist const& rhs);

}  // namespace quant::framed_units::velocity
