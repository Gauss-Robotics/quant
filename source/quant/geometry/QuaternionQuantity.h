#pragma once


#include <quant/geometry/common.h>

#include <Eigen/Geometry>

#include <ostream>
#include <typeinfo>

namespace quant::geometry
{

    template <typename T>
    class QuaternionQuantity;


    template <typename T>
    T operator+(Difference<T> const& lhs, QuaternionQuantity<T> const& rhs);


    template <typename T>
    Difference<T> operator-(QuaternionQuantity<T> const& lhs, QuaternionQuantity<T> const& rhs);

    template <typename T>
    class QuaternionQuantity
    {
    protected:
        // Construct.

        /**
         * @brief Construct quaternion from Euler angles.
         * @param roll
         * @param pitch
         * @param yaw
         */
        QuaternionQuantity(float const roll, float const pitch, float const yaw) :
            QuaternionQuantity(static_cast<double>(roll),
                               static_cast<double>(pitch),
                               static_cast<double>(yaw))
        {
            ;
        }

        /**
         * @brief Construct quaternion from Euler angles.
         * @param roll
         * @param pitch
         * @param yaw
         */
        QuaternionQuantity(double const roll, double const pitch, double const yaw) :
            representation_(Eigen::AngleAxisd(roll, Eigen::Vector3d::UnitX()) *
                            Eigen::AngleAxisd(pitch, Eigen::Vector3d::UnitY()) *
                            Eigen::AngleAxisd(yaw, Eigen::Vector3d::UnitZ()))
        {
            ;
        }

        QuaternionQuantity(AxisAngle const& aa) : QuaternionQuantity(aa.toEigen())
        {
            ;
        }

        /**
         * @brief Construct quaternion from Euler angles.
         * @param p
         */
        QuaternionQuantity(Eigen::Vector3f const& p) : QuaternionQuantity(p.cast<double>().eval())
        {
            ;
        }

        /**
         * @brief Construct quaternion from Euler angles.
         * @param p
         */
        QuaternionQuantity(Eigen::Vector3d const& p) : QuaternionQuantity(p.x(), p.y(), p.z())
        {
            ;
        }

        /**
         * @brief Construct quaternion from rotation matrix.
         * @param r
         */
        QuaternionQuantity(Eigen::Matrix3f const& r) : representation_(r.cast<double>().eval())
        {
            ;
        }

        /**
         * @brief Construct quaternion from rotation matrix.
         * @param r
         */
        QuaternionQuantity(Eigen::Matrix3d const& r) : representation_(r)
        {
            ;
        }

        /**
         * @brief Construct quaternion from angle axis.
         * @param r
         */
        QuaternionQuantity(Eigen::AngleAxisd const& r) : representation_(r)
        {
            ;
        }

        /**
         * @brief Construct quaternion from Eigen quaternion.
         * @param r
         */
        QuaternionQuantity(Eigen::Quaterniond const& r) : representation_(r)
        {
            ;
        }

    public:
        // Construct.

        /**
         * @brief Default constructed quaternion.
         */
        QuaternionQuantity() : representation_(1, 0, 0, 0)
        {
            ;
        }

        static T
        Origin()
        {
            return T();
        }

        Difference<T>
        deltaToOrigin() const
        {
            return Difference<T>(static_cast<const T&>(*this));
        }

        // Convert.

        AxisAngle
        toAngleAxis() const
        {
            return AxisAngle::FromEigen(Eigen::AngleAxisd(representation_));
        }

        std::string
        toString(std::string const& quantityName, std::string const& unit) const
        {
            std::string prefix = "";

            if (not quantityName.empty())
            {
                prefix = quantityName + " ";
            }

            const AxisAngle aa = toAngleAxis();
            std::stringstream out;
            out << "<" << prefix << io::toString(aa, unit) << ">";
            return out.str();
        }

        // Transform.

        template <typename T_>
        friend T_ geometry::operator+(Difference<T_> const& lhs, QuaternionQuantity<T_> const& rhs);

        template <typename T_>
        friend Difference<T_> geometry::operator-(QuaternionQuantity<T_> const& lhs,
                                                  QuaternionQuantity<T_> const& rhs);

        // Compare.

        bool
        operator==(const T& rhs) const
        {
            // TODO(dreher): Eigen >= 3.4
            // return _representation == rhs._representation;
            return representation_.coeffs() == rhs.representation_.coeffs();
        }

        bool
        operator!=(const T& rhs) const
        {
            // TODO(dreher): Eigen >= 3.4
            // return _representation == rhs._representation;
            return not((*this) == rhs);
        }

        bool
        isApprox(const T& rhs, double const precision) const
        {
            return representation_.isApprox(rhs.representation_, precision);
        }

    protected:
        Eigen::Quaterniond representation_;
    };

}  // namespace quant::geometry

namespace quant
{

    template <typename T>
    T
    geometry::operator+(Difference<T> const& lhs, QuaternionQuantity<T> const& rhs)
    {
        return T(lhs.pointFromOrigin().representation_ * rhs.representation_);
    }

    template <typename T>
    Difference<T>
    geometry::operator-(QuaternionQuantity<T> const& lhs, QuaternionQuantity<T> const& rhs)
    {
        // TODO(dreher): Figure out return T(representation_ - rhs.representation_);
        return T();  // Delta<T>(T(lhs.representation_ - rhs.representation_));
    }

}  // namespace quant
