#pragma once

#include <quant/geometry_fwd.h>

namespace quant::framed_geometry
{

    template <typename T>
    class Framed;

    struct StateType : public geometry::StateType
    {
    };

    /*struct ScalarStateType : public StateType
    {
    };

    struct LinearStateType : public StateType
    {
    };

    struct AngularStateType : public StateType
    {
    };

    struct SpatialStateType : public StateType
    {
    };*/

}  // namespace quant::framed_geometry

namespace quant
{

    using framed_geometry::Framed;

}
