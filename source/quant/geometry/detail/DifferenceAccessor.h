#pragma once

#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/geometry/forward_declarations.h>

namespace quant::geometry::detail
{

    template <typename DifferenceType>
    class DifferenceAccessor
    {
    public:
        static typename DifferenceType::GeometricRepresentationType
        representation(
            geometry::Difference<typename DifferenceType::DifferenceObjectType> const& difference)
        {
            using State = StateAccessor<typename DifferenceType::DifferenceObjectType>;
            return State::representation(difference._difference_object);
        }

        static DifferenceType
        make(typename DifferenceType::GeometricRepresentationType representation)
        {
            using State = StateAccessor<typename DifferenceType::DifferenceObjectType>;
            return DifferenceType(State::make(representation));
        }
    };

}  // namespace quant::geometry::detail
