#pragma once

#include <quant/geometry/Vector.h>
#include <quant/geometry/constants.h>
#include <quant/geometry/detail/QuantityAccessor.h>

#include <Eigen/Geometry>

namespace quant::geometry
{

    /**
     * @brief Represents a linear state in 3D space.
     *
     * @tparam StateType The type of the state.
     */
    template <typename StateType>
    class T3State
    {
    public:
        // Construct.
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
            return _representation.translation() == rhs._representation.translation();
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
            return _representation.translation() != rhs._representation.translation();
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
            return _representation.translation() <=> rhs._representation.translation();
        }

        /**
         * @brief Checks if the state is approximately equal to another state within a given
         * tolerance.
         *
         * @param rhs The right-hand side state to compare with.
         * @param tolerance The tolerance for the comparison.
         * @return True if the states are approximately equal, false otherwise.
         */
        bool
        is_approx(StateType const& rhs,
                  double tolerance = constants::floating_point_tolerance) const
        {
            return _representation.translation().isApprox(rhs._representation.translation(),
                                                          tolerance);
        }

        /**
         * @brief Unary minus operator.
         *
         * @return The negated state.
         */
        StateType
        operator-() const
        {
            return StateType{_representation.inverse()};
        }

        StateType inverse() const
        {
            return StateType{_representation.inverse()};
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
            return StateType{_representation.translation().cwiseQuotient(rhs._representation)};
        }

        using GeometricRepresentationType = Eigen::Translation3d;

    protected:
        // Construct.

        /**
         * @brief Constructor initializing the linear state with a given vector.
         *
         * @param xyz The vector to initialize the state with.
         */
        T3State(Vector const& xyz) :
            _representation(xyz.x, xyz.y, xyz.z)
        {
            ;
        }

        /**
         * @brief Default constructor initializing the linear state to (0, 0, 0).
         */
        T3State() : _representation(GeometricRepresentationType(0, 0, 0))
        {
            ;
        }

        /**
         * @brief Constructor initializing the linear state with a given Eigen vector.
         *
         * @param representation
         */
        T3State(GeometricRepresentationType const& representation) : _representation(representation)
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
            return Vector::from_eigen(_representation.translation());
        }

        GeometricRepresentationType
            _representation;  ///< The element of the translation manifold T (see
                              ///< Appendix E from https://arxiv.org/pdf/1812.01537)

        friend class detail::StateAccessor<StateType>;
    };

}  // namespace quant::geometry