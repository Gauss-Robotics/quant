#pragma once


#include <quant/geometry/QuaternionQuantity.h>
#include <quant/units/position_fwd.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::position
{

    class Orientation : public geometry::QuaternionQuantity<Orientation>
    {
    public:
        // Construct.

        using geometry::QuaternionQuantity<Orientation>::QuaternionQuantity;

        static Orientation
        Radians(AxisAngle const& aa)
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
        friend Position operator*(Difference<Orientation> const& rotation,
                                  Position const& position);
        friend Difference<Position> operator*(Difference<Orientation> const& rotation,
                                              Difference<Position> const& translation);
    };

    std::ostream& operator<<(std::ostream& out, Orientation const& rhs);

}  // namespace quant::units::position

namespace quant
{
    using units::position::Orientation;
}  // namespace quant
