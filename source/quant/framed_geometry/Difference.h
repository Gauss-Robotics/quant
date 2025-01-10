
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
}  // namespace quant::framed_geometry