#pragma once

#include <quant/geometry/Difference.h>
#include <quant/geometry_fwd.h>

namespace quant::geometry
{

    template <typename Linear, typename Angular, typename Derived>
    Derived
    operator+(DifferenceTypeOf<Linear> const& op, Spatial<Linear, Angular, Derived> const& rhs);

    template <typename Linear, typename Angular, typename Derived>
    Derived
    operator-(Linear const& op, Spatial<Linear, Angular, Derived> const& rhs);

    template <typename Linear, typename Angular, typename Derived>
    Derived
    operator+(DifferenceTypeOf<Angular> const& op, Spatial<Linear, Angular, Derived> const& rhs);

    template <typename Linear, typename Angular, typename Derived>
    Derived
    operator-(Angular const& op, Spatial<Linear, Angular, Derived> const& rhs);

    template <typename Linear, typename Angular, typename Derived>
    class Spatial
    {
    public:
        Spatial(Linear linear, Angular angular) : linear_{linear}, angular_{angular}
        {
            ;
        }

        static Derived
        Zero()
        {
            return Derived(Linear::Zero(), Angular::Zero());
        }

        Linear
        linear() const
        {
            return linear_;
        }

        Angular
        angular() const
        {
            return angular_;
        }

    public:
        template <typename Linear_, typename Angular_, typename Derived_>
        friend Derived_
        geometry::operator+(DifferenceTypeOf<Linear_> const& op,
                            Spatial<Linear_, Angular_, Derived_> const& rhs);

        template <typename Linear_, typename Angular_, typename Derived_>
        friend Derived_
        geometry::operator-(Linear_ const& op, Spatial<Linear_, Angular_, Derived_> const& rhs);

        template <typename Linear_, typename Angular_, typename Derived_>
        friend Derived_
        operator+(DifferenceTypeOf<Angular_> const& op,
                  Spatial<Linear_, Angular_, Derived_> const& rhs);

        template <typename Linear_, typename Angular_, typename Derived_>
        friend Derived_
        operator-(Angular_ const& op, Spatial<Linear_, Angular_, Derived_> const& rhs);

    protected:
        Linear linear_;
        Angular angular_;
    };

}  // namespace quant::geometry

namespace quant
{

    template <typename Linear, typename Angular, typename Derived>
    Derived
    geometry::operator+(DifferenceTypeOf<Linear> const& op,
                        Spatial<Linear, Angular, Derived> const& rhs)
    {
        return Derived(op + rhs.linear_, rhs.angular_);
    }

    template <typename Linear, typename Angular, typename Derived>
    Derived
    geometry::operator-(Linear const& op, Spatial<Linear, Angular, Derived> const& rhs)
    {
        return Derived(rhs.linear_ - op, rhs.angular_);
    }

    template <typename Linear, typename Angular, typename Derived>
    Derived
    geometry::operator+(DifferenceTypeOf<Angular> const& op,
                        Spatial<Linear, Angular, Derived> const& rhs)
    {
        return Derived(rhs.linear_, op * rhs.angular_);
    }

    template <typename Linear, typename Angular, typename Derived>
    Derived
    geometry::operator-(Angular const& op, Spatial<Linear, Angular, Derived> const& rhs)
    {
        return Derived(rhs.linear_, rhs.angular_ - op);
    }

}  // namespace quant
