#pragma once


#include <ostream>

#include <Eigen/Geometry>

#include <quant/geometry/QuaternionQuantity.h>
#include <quant/units/position_fwd.h>


namespace quant::units::position
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

} // namespace quant::units::position


namespace quant
{
    using units::position::Orientation;
} // namespace quant
