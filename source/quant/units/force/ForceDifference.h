#pragma once

#include <quant/geometry/Difference.h>
#include <quant/units/force/Force.h>
#include <quant/units/force/forward_declarations.h>

namespace quant::units::force
{

    class ForceDifference : public geometry::Difference<Force>
    {
    public:
        static ForceDifference
        newtons(geometry::Vector xyz);

        Vector
        to_newtons() const;

        std::string
        to_string() const;

        using Difference::Difference;
    };

    std::ostream&
    operator<<(std::ostream& os, ForceDifference const& rhs);

}  // namespace quant::units::force
