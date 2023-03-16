#pragma once


#include <ostream>
#include <typeinfo>

#include <Eigen/Geometry>

#include <quant/geometry/common.h>


namespace quant::geometry
{

    template <typename T>
    class QuaternionQuantity;


    template <typename T>
    T operator+(const Difference<T>& lhs, const QuaternionQuantity<T>& rhs);


    template <typename T>
    Difference<T> operator-(const QuaternionQuantity<T>& lhs, const QuaternionQuantity<T>& rhs);


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
        QuaternionQuantity(const float roll, const float pitch, const float yaw) :
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
        QuaternionQuantity(const double roll, const double pitch, const double yaw) :
            representation_(Eigen::AngleAxisd(roll, Eigen::Vector3d::UnitX()) *
                            Eigen::AngleAxisd(pitch, Eigen::Vector3d::UnitY()) *
                            Eigen::AngleAxisd(yaw, Eigen::Vector3d::UnitZ()))
        {
            ;
        }

        QuaternionQuantity(const AxisAngle& aa) : QuaternionQuantity(aa.toEigen())
        {
            ;
        }

        /**
         * @brief Construct quaternion from Euler angles.
         * @param p
         */
        QuaternionQuantity(const Eigen::Vector3f& p) : QuaternionQuantity(p.cast<double>().eval())
        {
            ;
        }

        /**
         * @brief Construct quaternion from Euler angles.
         * @param p
         */
        QuaternionQuantity(const Eigen::Vector3d& p) : QuaternionQuantity(p.x(), p.y(), p.z())
        {
            ;
        }

        /**
         * @brief Construct quaternion from rotation matrix.
         * @param r
         */
        QuaternionQuantity(const Eigen::Matrix3f& r) : representation_(r.cast<double>().eval())
        {
            ;
        }

        /**
         * @brief Construct quaternion from rotation matrix.
         * @param r
         */
        QuaternionQuantity(const Eigen::Matrix3d& r) : representation_(r)
        {
            ;
        }

        /**
         * @brief Construct quaternion from angle axis.
         * @param r
         */
        QuaternionQuantity(const Eigen::AngleAxisd& r) : representation_(r)
        {
            ;
        }

        /**
         * @brief Construct quaternion from Eigen quaternion.
         * @param r
         */
        QuaternionQuantity(const Eigen::Quaterniond& r) : representation_(r)
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
        toString(const std::string& quantityName, const std::string& unit) const
        {
            std::string prefix = "";

            if (quantityName.size() > 0)
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
        friend T_ geometry::operator+(const Difference<T_>& lhs, const QuaternionQuantity<T_>& rhs);

        template <typename T_>
        friend Difference<T_> geometry::operator-(const QuaternionQuantity<T_>& lhs,
                                             const QuaternionQuantity<T_>& rhs);

        // Compare.

        bool
        operator==(const T& rhs) const
        {
            // TODO: Eigen >= 3.4
            // return _representation == rhs._representation;
            return representation_.coeffs() == rhs.representation_.coeffs();
        }

        bool
        operator!=(const T& rhs) const
        {
            // TODO: Eigen >= 3.4
            // return _representation == rhs._representation;
            return not((*this) == rhs);
        }

        bool
        isApprox(const T& rhs, const double precision) const
        {
            return representation_.isApprox(rhs.representation_, precision);
        }

    protected:
        Eigen::Quaterniond representation_;
    };

} // namespace quant::geometry


namespace quant
{

    template <typename T>
    T
    geometry::operator+(const Difference<T>& lhs, const QuaternionQuantity<T>& rhs)
    {
        return T(lhs.pointFromOrigin().representation_ * rhs.representation_);
    }

    template <typename T>
    Difference<T>
    geometry::operator-(const QuaternionQuantity<T>& lhs, const QuaternionQuantity<T>& rhs)
    {
        // TODO: Figure out return T(representation_ - rhs.representation_);
        return T(); //Delta<T>(T(lhs.representation_ - rhs.representation_));
    }

} // namespace quant
