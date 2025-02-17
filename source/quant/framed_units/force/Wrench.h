#pragma once

#include <quant/framed_geometry/State.h>
#include <quant/framed_units/force/Force.h>
#include <quant/framed_units/force/Torque.h>
#include <quant/units/force/Wrench.h>

namespace quant::framed_units::force
{

    /**
     * @brief Represents a wrench, i.e., a screw of force and torque.
     */
    class Wrench : public framed_geometry::State<units::force::Wrench>
    {
        // Construct.
    public:
        Torque
        angular() const;
        Force
        linear() const;
        using State::State;
    };

}  // namespace quant::framed_units::force
