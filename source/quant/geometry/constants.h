#pragma once

#include <limits>

namespace quant::geometry::constants
{

    constexpr double floating_point_tolerance =
        static_cast<double>(std::numeric_limits<float>::epsilon()) * 100;

}
