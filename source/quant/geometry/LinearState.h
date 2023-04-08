#pragma once

#include <quant/geometry/Vector.h>
#include <quant/geometry/constants.h>
#include <quant/geometry/detail/QuantityAccessor.h>

#include <Eigen/Geometry>

#include <string>

namespace quant::geometry
{

    template <typename Domain>
    class LinearState
    {
    public:
        // Construct.

        /**
         * @brief VectorQuantity
         */
        LinearState() : _representation(0, 0, 0)
        {
            ;
        }

        /**
         * @brief Zero
         * @return
         */
        static typename Domain::LinearState
        zero()
        {
            return typename Domain::LinearState({.x = 0, .y = 0, .z = 0});
        }

        // Compare.

        bool
        operator==(typename Domain::LinearState const& rhs) const
        {
            return _representation == rhs._representation;
        }

        bool
        operator!=(typename Domain::LinearState const& rhs) const
        {
            return _representation != rhs._representation;
        }

        bool
        is_approx(typename Domain::LinearState const& rhs,
                  double tolerance = constants::floating_point_tolerance) const
        {
            return _representation.isApprox(rhs._representation, tolerance);
        }

        using GeometricRepresentationType = Eigen::Ref<Eigen::Vector3d const>;
        using GeometricType = traits::StateType;

    protected:
        // Construct.

        LinearState(Vector const& xyz) : _representation(xyz.x, xyz.y, xyz.z)
        {
            ;
        }

        LinearState(Eigen::Ref<Eigen::Vector3d const> vector) : _representation(vector)
        {
            ;
        }

        // Convert.

        Vector
        to_vector() const
        {
            return Vector::from_eigen(_representation);
        }

        Eigen::Vector3d _representation;

        friend class detail::QuantityAccessor<typename Domain::LinearState>;
    };

}  // namespace quant::geometry
