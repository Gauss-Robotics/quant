#pragma once

#include <quant/geometry/AxisAngle.h>
#include <quant/geometry/Difference.h>

#include <Eigen/Geometry>

#include <ostream>
#include <typeinfo>

namespace quant::geometry
{

    template <typename T, typename DifferenceType>
    class QuaternionQuantity;

    template <typename T, typename DifferenceType>
    T
    operator+(Difference<T> const& lhs, QuaternionQuantity<T, DifferenceType> const& rhs);

    template <typename T, typename DifferenceType>
    Difference<T>
    operator-(QuaternionQuantity<T, DifferenceType> const& lhs,
              QuaternionQuantity<T, DifferenceType> const& rhs);

    template <typename T, typename DifferenceType = Difference<T>>
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
            return Difference<T>(static_cast<T const&>(*this));
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
            out << "<" << prefix << aa.toString(unit) << ">";
            return out.str();
        }

        // Transform.

        template <typename T_, typename DifferenceType_>
        friend T_
        geometry::operator+(Difference<T_> const& lhs,
                            QuaternionQuantity<T_, DifferenceType_> const& rhs);

        template <typename T_, typename DifferenceType_>
        friend Difference<T_>
        geometry::operator-(QuaternionQuantity<T_, DifferenceType_> const& lhs,
                            QuaternionQuantity<T_, DifferenceType_> const& rhs);

        // Compare.

        bool
        operator==(T const& rhs) const
        {
            // TODO(dreher): Eigen >= 3.4
            // return _representation == rhs._representation;
            return representation_.coeffs() == rhs.representation_.coeffs();
        }

        bool
        operator!=(T const& rhs) const
        {
            // TODO(dreher): Eigen >= 3.4
            // return _representation == rhs._representation;
            return not((*this) == rhs);
        }

        bool
        isApprox(T const& rhs, double const precision) const
        {
            return representation_.isApprox(rhs.representation_, precision);
        }

        using QuantityType = T;
        using QuantityDifferenceType = DifferenceType;

    public:
        Eigen::Quaterniond representation_;

        friend class Difference<T>;
    };

}  // namespace quant::geometry

namespace quant
{

    template <typename T, typename DifferenceType>
    T
    geometry::operator+(Difference<T> const& lhs, QuaternionQuantity<T, DifferenceType> const& rhs)
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
