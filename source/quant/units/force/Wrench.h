#pragma once


#include <quant/geometry/common.h>
#include <quant/units/force/Force.h>
#include <quant/units/force/Torque.h>


namespace quant::units::force
{

    /**
     * @brief Represents a wrench, i.e., a screw of force and torque.
     */
    class Wrench : public Spatial<Force, Torque, Wrench>
    {
        // Construct.
    public:
        using Spatial<Force, Torque, Wrench>::Spatial;
    };

} // namespace quant::units::force


namespace quant
{
    using units::force::Wrench;
}
