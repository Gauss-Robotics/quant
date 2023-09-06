#include "Frequency.h"

#include <quant/framed_units/time/Duration.h>

namespace quant::framed_units::time
{
    FramedDuration
    Frequency::to_period() const
    {
        return FramedDuration{get_framed_object().to_period(), {.base_frame = get_base_frame()}};
    }

}  // namespace quant::framed_units::time
