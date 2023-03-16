#pragma once


#include <ostream>

#include <Eigen/Geometry>

#include <simox/core/geometry/VectorQuantity.h>
#include <simox/core/units/position/forward_declarations.h>
#include <simox/core/units/time/Duration.h>


namespace simox::core::units::position
{

    class Displacement;


    class Position : public geometry::VectorQuantity<Position, Displacement>
    {
        friend Displacement;

    public:
        // Construct.

        using geometry::VectorQuantity<Position, Displacement>::VectorQuantity;

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
        friend class Translation;
        friend class Rotation;
        friend class Transform;

        friend class FrameTransform;

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


} // namespace simox::core::units::position


namespace simox
{
    using core::units::position::Position;
} // namespace simox
