#include "Force.h"

namespace quant::units::force
{

    Force
    Force::newton(geometry::Vector xyz)
    {
        return {xyz};
    }

    Vector
    Force::to_newton() const
    {
        return {to_vector(), constants::names::force, constants::symbols::newton};
    }

    std::string
    Force::to_string() const
    {
        return to_newton().to_string();
    }

    std::ostream&
    operator<<(std::ostream& os, Force const& rhs)
    {
        return os << rhs.to_string();
    }
}  // namespace quant::units::force
