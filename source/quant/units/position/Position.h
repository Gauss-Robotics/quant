#pragma once


#include <ostream>

#include <Eigen/Geometry>

#include <quant/geometry/VectorQuantity.h>
#include <quant/units/position_fwd.h>
#include <quant/units/time/Duration.h>


namespace quant::units::position
{

    class LinearDisplacement;


    class Position : public geometry::VectorQuantity<Position, LinearDisplacement>
    {
        friend LinearDisplacement;

    public:
        // Construct.

        using geometry::VectorQuantity<Position, LinearDisplacement>::VectorQuantity;

        static Position
        MilliMeters(double x, double y, double z)
        {
            return {x, y, z};
        }

        static Position
        MilliMeters(Vector xyz)
        {
            return {xyz.x, xyz.y, xyz.z};
        }

        static Position
        Meters(double x, double y, double z)
        {
            constexpr int m2mm = 1'000;
            return {x * m2mm, y * m2mm, z * m2mm};
        }

        static Position
        Meters(Vector xyz)
        {
            constexpr int m2mm = 1'000;
            return {xyz.x * m2mm, xyz.y * m2mm, xyz.z * m2mm};
        }

        // Convert.

        Vector
        toMilliMeters() const
        {
            return {representation_.x(), representation_.y(), representation_.z()};
        }


    protected:

        friend Position operator*(const Difference<Orientation>& rotation,
                                  const Position& position);
        friend Difference<Position> operator*(const Difference<Orientation>& rotation,
                                              const Difference<Position>& translation);
    };


    std::ostream& operator<<(std::ostream& out, const Position& rhs);


    /// Rotate a position.
    Position operator*(const Difference<Orientation>& rotation, const Position& position);

    /// Rotate a translation.
    Difference<Position> operator*(const Difference<Orientation>& rotation,
                                   const Difference<Position>& translation);


} // namespace quant::units::position


namespace quant
{
    using units::position::Position;
} // namespace quant
