#pragma once

namespace quant::units::jerk
{

    class LinearJerk;
    class AngularJerk;
    class SpatialJerk;

    class LinearJerkDifference;
    class AngularJerkDifference;
    class SpatialJerkDifference;

}  // namespace quant::units::jerk

namespace quant
{

    using units::jerk::AngularJerk;
    using units::jerk::LinearJerk;
    using units::jerk::SpatialJerk;

    using units::jerk::AngularJerkDifference;
    using units::jerk::LinearJerkDifference;
    using units::jerk::SpatialJerkDifference;

}  // namespace quant
