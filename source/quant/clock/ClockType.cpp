#include "ClockType.h"


namespace quant
{

    const quant::meta::EnumNames<time::ClockType> time::ClockTypeNames{
        {ClockType::Realtime, "Realtime"},
        {ClockType::Monotonic, "Monotonic"},
        {ClockType::Virtual, "Virtual"},
        {ClockType::Unknown, "Unknown"},
    };

} // namespace quant
