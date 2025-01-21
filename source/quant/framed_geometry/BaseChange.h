
#include <quant/framed_geometry/forward_declarations.h>
#include <quant/units/position/SpatialDisplacement.h>

#include <array>

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
        std::array<char, frame_data_max_string_size> from_frame;
        std::array<char, frame_data_max_string_size> to_frame;
        units::position::SpatialDisplacement transformation;
    };

    struct Shift
    {
        // TODO: multiplication from the right
        //  from_frame has to be the same as to_frame and the frame_name of the framed unit

        /**
         * In case of Positions/Orientations/Poses, this corresponds to the right plus operator
         * (from https://arxiv.org/pdf/1812.01537, Eq. (25)). It always adds a difference of the
         * same unit at the position of the framed unit (i.e., "dX is expressed in the local frame
         * at X").
         */
    };
}  // namespace quant::framed_geometry