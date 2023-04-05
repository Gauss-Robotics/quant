#include "Duration.h"

namespace quant::units::time
{

    bool
    Duration::is_positive() const
    {
        return _difference_object.is_positive();
    }

    bool
    Duration::is_zero() const
    {
        return _difference_object.is_zero();
    }

}  // namespace quant::units::time
