#pragma once


#include <string>

#include <Eigen/Core>
#include <Eigen/Geometry>


namespace simox
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
        FromEigen(const Eigen::Vector3d& eigen)
        {
            return {.x = eigen.x(), .y = eigen.y(), .z = eigen.z()};
        }

        Eigen::Vector3d
        toEigen() const
        {
            return {x, y, z};
        }
    };


    std::ostream& operator<<(std::ostream& os, const Vector& v);


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
        FromEigen(const Eigen::AngleAxisd& eigen)
        {
            return {.angle = eigen.angle(), .axis = Vector::FromEigen(eigen.axis())};
        }

        Eigen::AngleAxisd
        toEigen() const
        {
            return {angle, axis.toEigen()};
        }
    };


    std::ostream& operator<<(std::ostream& os, const AxisAngle& aa);


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
            // delta.pointFromOrigin()    = point = delta + origin
            return differenceObject_;
        }

        bool
        operator==(const Difference<T>& rhs) const
        {
            return this->differenceObject_ == rhs.differenceObject_;
        }
        bool
        operator!=(const Difference<T>& rhs) const
        {
            return this->differenceObject_ != rhs.differenceObject_;
        }

    protected:
        T differenceObject_;
    };


    template <typename Linear, typename Angular, typename Derived>
    class Spatial;

    template <typename Linear, typename Angular, typename Derived>
    Derived operator+(const Difference<Linear>& op, const Spatial<Linear, Angular, Derived>& rhs);

    template <typename Linear, typename Angular, typename Derived>
    Derived operator-(const Linear& op, const Spatial<Linear, Angular, Derived>& rhs);

    template <typename Linear, typename Angular, typename Derived>
    Derived operator+(const Difference<Angular>& op, const Spatial<Linear, Angular, Derived>& rhs);

    template <typename Linear, typename Angular, typename Derived>
    Derived operator-(const Angular& op, const Spatial<Linear, Angular, Derived>& rhs);


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
        template <typename _Linear, typename _Angular, typename _Derived>
        friend _Derived simox::operator+(const Difference<_Linear>& op,
                                         const Spatial<_Linear, _Angular, _Derived>& rhs);

        template <typename _Linear, typename _Angular, typename _Derived>
        friend _Derived simox::operator-(const _Linear& op,
                                         const Spatial<_Linear, _Angular, _Derived>& rhs);

        template <typename _Linear, typename _Angular, typename _Derived>
        friend _Derived operator+(const Difference<_Angular>& op,
                                  const Spatial<_Linear, _Angular, _Derived>& rhs);

        template <typename _Linear, typename _Angular, typename _Derived>
        friend _Derived operator-(const _Angular& op,
                                  const Spatial<_Linear, _Angular, _Derived>& rhs);

    protected:
        Linear linear_;
        Angular angular_;
    };

} // namespace simox


template <typename Linear, typename Angular, typename Derived>
Derived
simox::operator+(const Difference<Linear>& op, const Spatial<Linear, Angular, Derived>& rhs)
{
    return Derived(op + rhs.linear_, rhs.angular_);
}

template <typename Linear, typename Angular, typename Derived>
Derived
simox::operator-(const Linear& op, const Spatial<Linear, Angular, Derived>& rhs)
{
    return Derived(rhs.linear_ - op, rhs.angular_);
}

template <typename Linear, typename Angular, typename Derived>
Derived
simox::operator+(const Difference<Angular>& op, const Spatial<Linear, Angular, Derived>& rhs)
{
    return Derived(rhs.linear_, op + rhs.angular_);
}

template <typename Linear, typename Angular, typename Derived>
Derived
simox::operator-(const Angular& op, const Spatial<Linear, Angular, Derived>& rhs)
{
    return Derived(rhs.linear_, rhs.angular_ - op);
}


namespace simox::io
{

    std::string toString(const Vector& v, const std::string& unit = "");
    std::string toString(const AxisAngle& aa, const std::string& unit = "");

} // namespace simox::io
