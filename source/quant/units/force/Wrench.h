#pragma once

#include <quant/geometry/SpatialState.h>
#include <quant/units/force/Force.h>
#include <quant/units/force/Torque.h>
#include <quant/units/force/forward_declarations.h>

namespace quant::units::force
{

    /**
     * @brief Represents a wrench, i.e., a screw of force and torque.
     */
    class Wrench : public geometry::SpatialState<Wrench>
    {
        // Construct.
    public:
        using SpatialState::SpatialState;
    };

    std::ostream&
    operator<<(std::ostream& out, Wrench const& rhs);

}  // namespace quant::units::force
