#pragma once
#include <quant/framed_geometry/forward_declarations.h>
#include <quant/units/position/SpatialDisplacement.h>

#include <string_view>

namespace quant::framed_geometry
{
    struct BaseChange
    {
        /**
         * In case of Positions/Orientations/Poses, this corresponds to the left plus operator
         * (from https://arxiv.org/pdf/1812.01537, Eq. (27)). It always multiplies a
         * SpatialDifference (i.e., the difference between the from_frame and to_frame) with the
         * unit in a way that is unique to each unit, and thereby changes the reference/base
         * frame of the framed unit.
         */
        std::string_view from_frame;
        std::string_view to_frame;
        units::position::SpatialDisplacement transformation;
    };
}  // namespace quant::framed_geometry