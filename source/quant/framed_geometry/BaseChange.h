#pragma once
#include <quant/framed_geometry/forward_declarations.h>
#include <quant/units/position/SpatialDisplacement.h>

#include <string_view>

namespace quant::framed_geometry
{
    template <typename... Args>
    struct BaseChangeBuilder;

    template <typename... Args>
    BaseChange
    make_base_change(Args&&... args);

    struct BaseChange
    {
        /**
         * In case of Positions/Orientations/Poses, this corresponds to the left plus operator
         * (from https://arxiv.org/pdf/1812.01537, Eq. (27)). It always multiplies a
         * SpatialDifference (i.e., the difference between the from_frame and to_frame) with the
         * unit in a way that is unique to each unit, and thereby changes the reference/base
         * frame of the framed unit.
         *
         * The transformation is always obtained using the right minus operator.
         */
        BaseChange() = delete;

        std::string_view from_frame;
        std::string_view to_frame;
        units::position::SpatialDisplacement transformation;

    private:
        template <typename... Args>
        friend struct BaseChangeBuilder;

        BaseChange(std::string_view from,
                   std::string_view to,
                   units::position::SpatialDisplacement const& tf) :
            from_frame(from), to_frame(to), transformation(tf)
        {
            ;
        }
    };

    template <typename... Args>
    BaseChange
    make_base_change(Args&&... args) {
        return BaseChangeBuilder<Args...>::build(std::forward<Args>(args)...);
    };


}  // namespace quant::framed_geometry