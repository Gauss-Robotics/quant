
#include <quant/framed_geometry/forward_declarations.h>
#include <quant/units/position/SpatialDisplacement.h>

#include <array>

namespace quant::framed_geometry
{
    struct Difference
    {
        std::array<char, frame_data_max_string_size> from_frame;
        std::array<char, frame_data_max_string_size> to_frame;
        units::position::SpatialDisplacement transformation;
    };

    struct BaseChange : Difference
    {
        // TODO: multiplication from the left
        //  from_frame should be different from to_frame and from_frame needs to be the base_frame
        //  of the framed unit
    };

    struct Shift : Difference
    {
        // TODO: multiplication from the right
        //  from_frame has to be the same as to_frame and the frame_name of the framed unit
    };
}  // namespace quant::framed_geometry