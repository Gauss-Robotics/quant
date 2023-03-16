#pragma once


#include <simox/core/geometry/common.h>
#include <simox/core/units/velocity/AngularVelocity.h>
#include <simox/core/units/velocity/LinearVelocity.h>


namespace simox::core::units::velocity
{

    /**
     * @brief Represents a twist, i.e., a screw of linear and angular velocity.
     */
    class Twist : public Spatial<LinearVelocity, AngularVelocity, Twist>
    {
        // Construct.
    public:
        using Spatial<LinearVelocity, AngularVelocity, Twist>::Spatial;
    };

} // namespace simox::core::units::velocity


namespace simox
{
    using core::units::velocity::Twist;
}
