#pragma once

#include <quant/geometry/Vector.h>
#include <quant/geometry/constants.h>
#include <quant/geometry/detail/QuantityAccessor.h>

#include <Eigen/Geometry>

#include <compare>
#include <string>

namespace quant::geometry
{

    /**
     * @brief Represents a linear state in 3D space.
     *
     * @tparam StateType The type of the state.
     */
    template <typename StateType>
    class LinearState
    {
    public:
        // Construct.

        /**
         * @brief Default constructor initializing the linear state to (0, 0, 0).
         */
        LinearState() : _representation(0, 0, 0)
        {
            ;
        }

        /**
         * @brief Returns a zero-initialized state.
         *
         * @return A zero-initialized state.
         */
        static StateType
        zero()
        {
            return StateType({.x = 0, .y = 0, .z = 0});
        }

        // Compare.

        /**
         * @brief Equality operator.
         *
         * @param rhs The right-hand side state to compare with.
         * @return True if the states are equal, false otherwise.
         */
        bool
        operator==(StateType const& rhs) const
        {
            return _representation == rhs._representation;
        }

        /**
         * @brief Inequality operator.
         *
         * @param rhs The right-hand side state to compare with.
         * @return True if the states are not equal, false otherwise.
         */
        bool
        operator!=(StateType const& rhs) const
        {
            return _representation != rhs._representation;
        }

        /**
         * @brief Three-way comparison operator.
         *
         * @param rhs The right-hand side state to compare with.
         * @return The result of the three-way comparison.
         */
        auto
        operator<=>(StateType const& rhs) const
        {
            return _representation <=> rhs._representation;
        }

        /**
         * @brief Checks if the state is approximately equal to another state within a given tolerance.
         *
         * @param rhs The right-hand side state to compare with.
         * @param tolerance The tolerance for the comparison.
         * @return True if the states are approximately equal, false otherwise.
         */
        bool
        is_approx(StateType const& rhs,
                  double tolerance = constants::floating_point_tolerance) const
        {
            return _representation.isApprox(rhs._representation, tolerance);
        }

        /**
         * @brief Unary minus operator.
         *
         * @return The negated state.
         */
        StateType
        operator-() const
        {
            return StateType{-_representation};
        }

        /**
         * @brief Division operator.
         *
         * @param rhs The right-hand side state to divide by.
         * @return The result of the division.
         */
        StateType
        operator/(StateType const& rhs) const
        {
            return StateType{_representation.cwiseQuotient(rhs._representation)};
        }

        using GeometricRepresentationType = Eigen::Vector3d;

    protected:
        // Construct.

        /**
         * @brief Constructor initializing the linear state with a given vector.
         *
         * @param xyz The vector to initialize the state with.
         */
        LinearState(Vector const& xyz) : _representation(xyz.x, xyz.y, xyz.z)
        {
            ;
        }

        /**
         * @brief Constructor initializing the linear state with a given Eigen vector.
         *
         * @param vector The Eigen vector to initialize the state with.
         */
        LinearState(Eigen::Ref<Eigen::Vector3d const> vector) : _representation(vector)
        {
            ;
        }

        // Convert.

        /**
         * @brief Converts the state to a vector.
         *
         * @return The vector representation of the state.
         */
        Vector
        to_vector() const
        {
            return Vector::from_eigen(_representation);
        }

        Eigen::Vector3d _representation; ///< The Eigen vector representing the state.

        friend class detail::StateAccessor<StateType>;
    };

}  // namespace quant::geometry