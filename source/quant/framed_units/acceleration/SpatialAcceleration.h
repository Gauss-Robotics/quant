#pragma once

#include <quant/framed_geometry/State.h>
#include <quant/units/acceleration/SpatialAcceleration.h>

#include <ostream>

#include "quant/framed_units/acceleration.h"
#include "quant/framed_units/velocity/forward_declarations.h"

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

    std::ostream&
    operator<<(std::ostream& out, SpatialAcceleration const& rhs);

}  // namespace quant::framed_units::acceleration
