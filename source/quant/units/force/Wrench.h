#pragma once

#include <quant/geometry/SpatialState.h>
#include <quant/units/force/Force.h>
#include <quant/units/force/Torque.h>
#include <quant/units/force_fwd.h>

namespace quant::units::force
{

    /**
     * @brief Represents a wrench, i.e., a screw of force and torque.
     */
    class Wrench : public geometry::SpatialState<Domain>
    {
        // Construct.
    public:
        using SpatialState<Domain>::SpatialState;
    };

}  // namespace quant::units::force
