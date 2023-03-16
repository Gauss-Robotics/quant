#pragma once


#include <ostream>

#include <Eigen/Geometry>

#include <simox/core/geometry/QuaternionQuantity.h>
#include <simox/core/units/position/forward_declarations.h>


namespace simox::core::units::position
{

    class Orientation : public geometry::QuaternionQuantity<Orientation>
    {
    public:
        // Construct.

        using geometry::QuaternionQuantity<Orientation>::QuaternionQuantity;

        static Orientation
        Radians(const AxisAngle& aa)
        {
            return {aa};
        }

        // Convert.

        AxisAngle
        toRadians() const
        {
            return this->toAngleAxis();
        }


    protected:
        friend Position operator*(const Difference<Orientation>& rotation, const Position& position);
        friend Difference<Position> operator*(const Difference<Orientation>& rotation,
                                         const Difference<Position>& translation);
    };


    std::ostream& operator<<(std::ostream& out, const Orientation& rhs);

} // namespace simox::core::units::position


namespace simox
{
    using core::units::position::Orientation;
} // namespace simox
