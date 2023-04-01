#pragma once

#include <quant/geometry/AxisAngle.h>
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/geometry_fwd.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <ostream>
#include <typeinfo>

namespace quant::geometry
{

    template <typename Domain>
    class AngularState
    {
    protected:
        // Construct.

        /**
         * @brief Construct quaternion from Euler angles.
         * @param roll
         * @param pitch
         * @param yaw
         */
        AngularState(float const roll, float const pitch, float const yaw) :
            AngularState(static_cast<double>(roll),
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
        AngularState(double const roll, double const pitch, double const yaw) :
            representation_(Eigen::AngleAxisd(roll, Eigen::Vector3d::UnitX()) *
                            Eigen::AngleAxisd(pitch, Eigen::Vector3d::UnitY()) *
                            Eigen::AngleAxisd(yaw, Eigen::Vector3d::UnitZ()))
        {
            ;
        }

        AngularState(AxisAngle const& aa) : AngularState(aa.toEigen())
        {
            ;
        }

        /**
         * @brief Construct quaternion from Euler angles.
         * @param p
         */
        AngularState(Eigen::Vector3f const& p) : AngularState(p.cast<double>().eval())
        {
            ;
        }

        /**
         * @brief Construct quaternion from Euler angles.
         * @param p
         */
        AngularState(Eigen::Vector3d const& p) : AngularState(p.x(), p.y(), p.z())
        {
            ;
        }

        /**
         * @brief Construct quaternion from rotation matrix.
         * @param r
         */
        AngularState(Eigen::Matrix3f const& r) : representation_(r.cast<double>().eval())
        {
            ;
        }

        /**
         * @brief Construct quaternion from rotation matrix.
         * @param r
         */
        AngularState(Eigen::Matrix3d const& r) : representation_(r)
        {
            ;
        }

        /**
         * @brief Construct quaternion from angle axis.
         * @param r
         */
        AngularState(Eigen::AngleAxisd const& r) : representation_(r)
        {
            ;
        }

        /**
         * @brief Construct quaternion from Eigen quaternion.
         * @param r
         */
        AngularState(Eigen::Quaterniond const& r) : representation_(r)
        {
            ;
        }

    public:
        // Construct.

        /**
         * @brief Default constructed quaternion.
         */
        AngularState() : representation_(1, 0, 0, 0)
        {
            ;
        }

        static typename Domain::AngularState
        zero()
        {
            return typename Domain::AngularState();
        }

        // Convert.

        AxisAngle
        toAngleAxis() const
        {
            return AxisAngle::fromEigen(Eigen::AngleAxisd(representation_));
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
        using GeometricType = StateType;
        using DomainType = Domain;

    protected:
        Eigen::Quaterniond representation_;

        friend class detail::QuantityAccessor<typename Domain::AngularState>;
    };

}  // namespace quant::geometry
