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
            _representation(Eigen::AngleAxisd(roll, Eigen::Vector3d::UnitX()) *
                            Eigen::AngleAxisd(pitch, Eigen::Vector3d::UnitY()) *
                            Eigen::AngleAxisd(yaw, Eigen::Vector3d::UnitZ()))
        {
            ;
        }

        AngularState(AxisAngle const& aa) : AngularState(aa.to_eigen())
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
        AngularState(Eigen::Matrix3f const& r) : _representation(r.cast<double>().eval())
        {
            ;
        }

        /**
         * @brief Construct quaternion from rotation matrix.
         * @param r
         */
        AngularState(Eigen::Matrix3d const& r) : _representation(r)
        {
            ;
        }

        /**
         * @brief Construct quaternion from angle axis.
         * @param r
         */
        AngularState(Eigen::AngleAxisd const& r) : _representation(r)
        {
            ;
        }

        /**
         * @brief Construct quaternion from Eigen quaternion.
         * @param r
         */
        AngularState(Eigen::Quaterniond const& r) : _representation(r)
        {
            ;
        }

    public:
        // Construct.

        /**
         * @brief Default constructed quaternion.
         */
        AngularState() : _representation(1, 0, 0, 0)
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
        to_angle_axis() const
        {
            return AxisAngle::from_eigen(Eigen::AngleAxisd{_representation});
        }

        std::string
        to_string(std::string const& quantity_name, std::string const& unit) const
        {
            std::string prefix = "";

            if (not quantity_name.empty())
            {
                prefix = quantity_name + " ";
            }

            const AxisAngle aa = to_angle_axis();
            std::stringstream out;
            out << "<" << prefix << aa.to_string(unit) << ">";
            return out.str();
        }

        // Compare.

        bool
        operator==(typename Domain::AngularState const& rhs) const
        {
            // TODO(dreher): Eigen >= 3.4
            // return _representation == rhs._representation;
            return _representation.coeffs() == rhs._representation.coeffs();
        }

        bool
        operator!=(typename Domain::AngularState const& rhs) const
        {
            // TODO(dreher): Eigen >= 3.4
            // return _representation == rhs._representation;
            return _representation.coeffs() != rhs._representation.coeffs();
        }

        bool
        is_approx(typename Domain::AngularState const& rhs, double const tolerance) const
        {
            return _representation.isApprox(rhs._representation, tolerance);
        }

        using GeometricRepresentationType = Eigen::Quaterniond const&;
        using GeometricType = traits::StateType;

    protected:
        Eigen::Quaterniond _representation;

        friend class detail::QuantityAccessor<typename Domain::AngularState>;
    };

}  // namespace quant::geometry
