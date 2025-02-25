#pragma once

#include <quant/framed_geometry/State.h>
#include <quant/framed_units/acceleration.h>
#include <quant/framed_units/acceleration/forward_declarations.h>
#include <quant/units/acceleration/SpatialAcceleration.h>

namespace quant::framed_units::acceleration
{

    class SpatialAcceleration :
        public framed_geometry::State<units::acceleration::SpatialAcceleration>
    {
    public:
        AngularAcceleration
        angular() const;

        LinearAcceleration
        linear() const;

        using State::State;
    };
}  // namespace quant::framed_units::acceleration
