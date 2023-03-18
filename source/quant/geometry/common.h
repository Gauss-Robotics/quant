#pragma once


#include <Eigen/Core>
#include <Eigen/Geometry>

#include <string>

namespace quant
{

    /**
     * @brief Euclidian point convenience struct for named parameter semantics.
     */
    struct Vector
    {
        double x = 0;
        double y = 0;
        double z = 0;

        static Vector
        UnitX()
        {
            return {.x = 1};
        }

        static Vector
        UnitY()
        {
            return {.y = 1};
        }

        static Vector
        UnitZ()
        {
            return {.z = 1};
        }

        static Vector
        FromEigen(Eigen::Vector3d const& eigen)
        {
            return {.x = eigen.x(), .y = eigen.y(), .z = eigen.z()};
        }

        Eigen::Vector3d
        toEigen() const
        {
            return {x, y, z};
        }
    };

    std::ostream& operator<<(std::ostream& os, Vector const& v);

    /**
     * @brief Angle around axis convenience struct for named parameter semantics.
     */
    struct AxisAngle
    {
        double angle = 0;
        Vector axis{.x = 1, .y = 0, .z = 0};

        static AxisAngle
        AroundX(double angle)
        {
            return {.angle = angle, .axis = Vector::UnitX()};
        }

        static AxisAngle
        AroundY(double angle)
        {
            return {.angle = angle, .axis = Vector::UnitY()};
        }

        static AxisAngle
        AroundZ(double angle)
        {
            return {.angle = angle, .axis = Vector::UnitZ()};
        }

        static AxisAngle
        FromEigen(Eigen::AngleAxisd const& eigen)
        {
            return {.angle = eigen.angle(), .axis = Vector::FromEigen(eigen.axis())};
        }

        Eigen::AngleAxisd
        toEigen() const
        {
            return {angle, axis.toEigen()};
        }
    };

    std::ostream& operator<<(std::ostream& os, AxisAngle const& aa);

    template <typename T>
    class Difference
    {
    public:
        Difference() : differenceObject_{}
        {
            ;
        }

        explicit Difference(const T& differenceObject) : differenceObject_{differenceObject}
        {
            ;
        }

        const T&
        pointFromOrigin() const
        {
            // point.deltaToOrigin() = delta = point - origin
            // delta.pointFromOrigin() = point = delta + origin
            return differenceObject_;
        }

        bool
        operator==(Difference<T> const& rhs) const
        {
            return this->differenceObject_ == rhs.differenceObject_;
        }

        bool
        operator!=(Difference<T> const& rhs) const
        {
            return this->differenceObject_ != rhs.differenceObject_;
        }

    protected:
        T differenceObject_;
    };


    template <typename Linear, typename Angular, typename Derived>
    class Spatial;

    template <typename Linear, typename Angular, typename Derived>
    Derived operator+(Difference<Linear> const& op, Spatial<Linear, Angular, Derived> const& rhs);

    template <typename Linear, typename Angular, typename Derived>
    Derived operator-(Linear const& op, Spatial<Linear, Angular, Derived> const& rhs);

    template <typename Linear, typename Angular, typename Derived>
    Derived operator+(Difference<Angular> const& op, Spatial<Linear, Angular, Derived> const& rhs);

    template <typename Linear, typename Angular, typename Derived>
    Derived operator-(Angular const& op, Spatial<Linear, Angular, Derived> const& rhs);

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
        friend Derived_ quant::operator+(Difference<Linear_> const& op,
                                         Spatial<Linear_, Angular_, Derived_> const& rhs);

        template <typename Linear_, typename Angular_, typename Derived_>
        friend Derived_ quant::operator-(Linear_ const& op,
                                         Spatial<Linear_, Angular_, Derived_> const& rhs);

        template <typename Linear_, typename Angular_, typename Derived_>
        friend Derived_ operator+(Difference<Angular_> const& op,
                                  Spatial<Linear_, Angular_, Derived_> const& rhs);

        template <typename Linear_, typename Angular_, typename Derived_>
        friend Derived_ operator-(Angular_ const& op,
                                  Spatial<Linear_, Angular_, Derived_> const& rhs);

    protected:
        Linear linear_;
        Angular angular_;
    };

}  // namespace quant

template <typename Linear, typename Angular, typename Derived>
Derived
quant::operator+(Difference<Linear> const& op, Spatial<Linear, Angular, Derived> const& rhs)
{
    return Derived(op + rhs.linear_, rhs.angular_);
}

template <typename Linear, typename Angular, typename Derived>
Derived
quant::operator-(Linear const& op, Spatial<Linear, Angular, Derived> const& rhs)
{
    return Derived(rhs.linear_ - op, rhs.angular_);
}

template <typename Linear, typename Angular, typename Derived>
Derived
quant::operator+(Difference<Angular> const& op, Spatial<Linear, Angular, Derived> const& rhs)
{
    return Derived(rhs.linear_, op + rhs.angular_);
}

template <typename Linear, typename Angular, typename Derived>
Derived
quant::operator-(Angular const& op, Spatial<Linear, Angular, Derived> const& rhs)
{
    return Derived(rhs.linear_, rhs.angular_ - op);
}

namespace quant::io
{

    std::string toString(Vector const& v, std::string const& unit = "");
    std::string toString(AxisAngle const& aa, std::string const& unit = "");

}  // namespace quant::io
