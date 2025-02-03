#include "Wrench.h"

#include "forward_declarations.h"

namespace quant::framed_units::force
{

    Torque
    Wrench::angular() const
    {
        return {get_framed_object().angular(),
                {.name = get_name(), .base_frame = get_base_frame()}};
    }

    Force
    Wrench::linear() const
    {
        return {get_framed_object().linear(), {.name = get_name(), .base_frame = get_base_frame()}};
    }

    std::ostream&
    operator<<(std::ostream& out, Wrench const& rhs)
    {
        return out << rhs.to_string();
    }

    units::force::Wrench
    base_change::wrench(units::force::Wrench const& wrench,
                        framed_geometry::BaseChange const& base_change)
    {
        throw std::runtime_error("Not implemented");
    }
}  // namespace quant::framed_units::force