#include "ClockType.h"


namespace simox::core
{

    const simox::meta::EnumNames<time::ClockType> time::ClockTypeNames{
        {ClockType::Realtime, "Realtime"},
        {ClockType::Monotonic, "Monotonic"},
        {ClockType::Virtual, "Virtual"},
        {ClockType::Unknown, "Unknown"},
    };

} // namespace simox::core
