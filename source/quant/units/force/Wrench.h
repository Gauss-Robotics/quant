#pragma once


#include <simox/core/geometry/common.h>
#include <simox/core/units/force/Force.h>
#include <simox/core/units/force/Torque.h>


namespace simox::core::units::force
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

} // namespace simox::core::units::force


namespace simox
{
    using core::units::force::Wrench;
}
