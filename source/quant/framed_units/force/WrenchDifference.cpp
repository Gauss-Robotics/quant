#include "WrenchDifference.h"

#include "forward_declarations.h"

namespace quant::framed_units::force
{
    units::force::WrenchDifference
    base_change::wrench_difference(units::force::WrenchDifference const& wrench_difference,
                                   framed_geometry::BaseChange const& base_change)
    {
        throw std::runtime_error("Not implemented");
    }
}  // namespace quant::framed_units::force