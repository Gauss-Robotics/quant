#include "ForceDifference.h"

namespace quant::units::force
{
    ForceDifference
    ForceDifference::newtons(geometry::Vector xyz)
    {
        return ForceDifference{Force::newtons(xyz)};
    }

    Vector
    ForceDifference::to_newtons() const
    {
        return _difference_object.to_newtons();
    }

    std::string
    ForceDifference::to_string() const
    {
        return _difference_object.to_string();
    }

    std::ostream&
    operator<<(std::ostream& os, ForceDifference const& rhs)
    {
        return os << rhs.to_string();
    }
}  // namespace quant::units::force
