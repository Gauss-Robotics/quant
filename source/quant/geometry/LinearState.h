#pragma once

#include <quant/geometry/Vector.h>
#include <quant/geometry/constants.h>
#include <quant/geometry/detail/QuantityAccessor.h>

#include <Eigen/Geometry>

#include <compare>
#include <string>

namespace quant::geometry
{

    template <typename StateType>
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
        static StateType
        zero()
        {
            return StateType({.x = 0, .y = 0, .z = 0});
        }

        // Compare.

        bool
        operator==(StateType const& rhs) const
        {
            return _representation == rhs._representation;
        }

        bool
        operator!=(StateType const& rhs) const
        {
            return _representation != rhs._representation;
        }

        auto
        operator<=>(StateType const& rhs) const
        {
            return _representation <=> rhs._representation;
        }

        bool
        is_approx(StateType const& rhs,
                  double tolerance = constants::floating_point_tolerance) const
        {
            return _representation.isApprox(rhs._representation, tolerance);
        }

        using GeometricRepresentationType = Eigen::Ref<Eigen::Vector3d const>;

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

        friend class detail::StateAccessor<StateType>;
    };

}  // namespace quant::geometry
