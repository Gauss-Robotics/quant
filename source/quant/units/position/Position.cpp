#include "Position.h"

#include <quant/units/position/Orientation.h>


namespace quant::units::position
{

    /*Translation
    Position::operator-(const Position& rhs) const
    {
        return {representation_ - rhs.representation_};
    }


    LinearVelocity
    Position::operator/(const Duration& rhs) const
    {
        return LinearVelocity(representation_ / rhs.toSecondsDouble());
    }*/

} // namespace quant::units::position


namespace quant::units
{

    std::ostream&
    position::operator<<(std::ostream& out, const Position& rhs)
    {
        out << rhs.toString("Position", "mm");
        return out;
    }


    Position
    position::operator*(const Difference<Orientation>& rotation, const Position& position)
    {
        return Position{rotation.pointFromOrigin().representation_ * position.representation_};
    }


    Difference<Position>
    position::operator*(const Difference<Orientation>& rotation, const Difference<Position>& translation)
    {
        return Position{rotation.pointFromOrigin().representation_ *
                        translation.pointFromOrigin().representation_}
            .deltaToOrigin();
    }

} // namespace quant::units
