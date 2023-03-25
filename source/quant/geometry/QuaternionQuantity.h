#pragma once

#include <quant/geometry/AxisAngle.h>
#include <quant/geometry/detail/Accessors.h>
#include <quant/geometry_fwd.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <ostream>
#include <typeinfo>

namespace quant::geometry
{

    template <typename Domain>
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

        static typename Domain::AngularState
        Zero()
        {
            return typename Domain::AngularState();
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

        // Compare.

        bool
        operator==(typename Domain::AngularState const& rhs) const
        {
            // TODO(dreher): Eigen >= 3.4
            // return _representation == rhs._representation;
            return representation_.coeffs() == rhs.representation_.coeffs();
        }

        bool
        operator!=(typename Domain::AngularState const& rhs) const
        {
            // TODO(dreher): Eigen >= 3.4
            // return _representation == rhs._representation;
            return representation_.coeffs() != rhs.representation_.coeffs();
        }

        bool
        isApprox(typename Domain::AngularState const& rhs, double const precision) const
        {
            return representation_.isApprox(rhs.representation_, precision);
        }

        using GeometricRepresentationType = Eigen::Quaterniond const&;
        using GeometricType = AngularStateType;
        using DomainType = Domain;

    public:
        Eigen::Quaterniond representation_;

        friend class detail::QuantityAccessor<typename Domain::AngularState>;
    };

}  // namespace quant::geometry
