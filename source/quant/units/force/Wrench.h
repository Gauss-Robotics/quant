#pragma once

#include <quant/geometry/Spatial.h>
#include <quant/units/force/Force.h>
#include <quant/units/force/Torque.h>
#include <quant/units/force_fwd.h>

namespace quant::units::force
{

    /**
     * @brief Represents a wrench, i.e., a screw of force and torque.
     */
    class Wrench : public Spatial<Domain>
    {
        // Construct.
    public:
        using Spatial<Domain>::Spatial;
    };

}  // namespace quant::units::force
