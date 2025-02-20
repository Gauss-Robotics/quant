#pragma once

#include <quant/geometry/SE3TangentState.h>
#include <quant/units/force/Force.h>
#include <quant/units/force/Torque.h>
#include <quant/units/force/forward_declarations.h>

namespace quant::units::force
{

    /**
     * @brief Represents a wrench, i.e., a screw of force and torque.
     */
    class Wrench : public geometry::SE3TangentState<Wrench>
    {
        // Construct.
    public:
        using SE3TangentState::SE3TangentState;
    };

    std::ostream&
    operator<<(std::ostream& out, Wrench const& rhs);

}  // namespace quant::units::force
