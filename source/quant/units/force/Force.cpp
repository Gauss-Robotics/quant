#include "Force.h"

namespace quant::units::force
{

    Force
    Force::newtons(geometry::Vector xyz)
    {
        return {xyz};
    }

    Vector
    Force::to_newtons() const
    {
        return {to_vector(), constants::names::force, constants::symbols::newton};
    }

    std::string
    Force::to_string() const
    {
        return to_newtons().to_string();
    }

    std::ostream&
    operator<<(std::ostream& os, Force const& rhs)
    {
        return os << rhs.to_string();
    }
}  // namespace quant::units::force
