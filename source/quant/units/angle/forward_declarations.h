#pragma once

#include <quant/geometry/forward_declarations.h>

namespace quant::units::angle
{

    class Angle;
    class AngularDifference;

}  // namespace quant::units::angle

namespace quant::traits
{

    // TODO: this is kind of a special case, as angles are not really linear space, but the defined
    //  math operations are not working the same as for 3d curved space (e.g. multiplication
    //  instead of addition)
    using AngleDomain = Define1DDomain<units::angle::Angle, units::angle::AngularDifference, R1Type>;

    template <>
    struct DefineTraits<units::angle::Angle>
    {
        using Domain = AngleDomain;
        using Difference = units::angle::AngularDifference;
        using GeometricType = ScalarStateType;
    };

    template <>
    struct DefineTraits<units::angle::AngularDifference>
    {
        using Domain = AngleDomain;
        using State = units::angle::Angle;
        using GeometricType = ScalarDifferenceType;
    };

}  // namespace quant::traits

namespace quant
{

    using units::angle::Angle;
    using units::angle::AngularDifference;

}  // namespace quant
