#pragma once

#include <quant/geometry/detail/ManifoldOperators.h>
#include <Eigen/Core>
#include <quant/geometry/AxisAngle.h>

namespace quant::geometry
{
    /**
     * @brief Computes the difference between two states.
     *
     * This operator returns the difference between the left-hand-side and right-hand-side states.
     * The result is either the defined difference type of the template type `StateType`, or
     * generally as `Difference<StateType>` if and only if `StateType` is a state.
     *
     * @tparam StateType The type of the states being subtracted.
     * @param lhs The left-hand-side state.
     * @param rhs The right-hand-side state.
     * @return The difference between the two states.
     */
    template <typename StateType>
        requires traits::state<StateType>
    traits::difference_type_of<StateType>
    operator-(StateType const& lhs, StateType const& rhs)
    {
        return rminus(lhs, rhs);
    }

    /**
     * @brief Subtract a difference from a state.
     *
     * @param lhs The state to subtract from.
     * @param rhs The difference to subtract.
     * @return The resulting state after subtraction.
     */
    template <typename StateType, typename DifferenceType>
        requires traits::difference<DifferenceType> and traits::state<StateType> and
                 traits::same_domain<DifferenceType, StateType> and
                 traits::same_group<StateType, DifferenceType>
    StateType
    operator-(StateType const& lhs, DifferenceType const& rhs)
    {
        return rplus(lhs, inverse(rhs));
    }

    /**.inverse()
     * @brief Adds a difference to a state.
     *
     * This operator returns the sum of the left-hand-side state and the right-hand-side difference.
     *
     * @tparam StateType The type of the state.
     * @tparam DifferenceType The type of the difference.
     * @param lhs The state to which the difference is added.
     * @param rhs The difference to add to the state.
     * @return The resulting state after addition.
     */
    template <typename StateType, typename DifferenceType>
        requires traits::difference<DifferenceType> and traits::state<StateType> and
                 traits::same_domain<DifferenceType, StateType> and
                 traits::same_group<StateType, DifferenceType>
    StateType
    operator+(StateType const& lhs, DifferenceType const& rhs)
    {
        return rplus(lhs, rhs);
    }

    /**
     * @brief Inplace addition of a difference to a state.
     *
     * This operator modifies the left-hand-side state by adding the given difference to it.
     *
     * @tparam DifferenceType The type of the difference.
     * @tparam StateType The type of the state.
     * @param lhs The state to which the difference is added.
     * @param rhs The difference to add to the state.
     * @return A reference to the modified state.
     */
    template <typename DifferenceType, typename StateType>
        requires traits::difference<DifferenceType> and traits::state<StateType> and
                 traits::same_domain<DifferenceType, StateType> and
                 traits::same_group<StateType, DifferenceType> and traits::in_flat_space<StateType>
    StateType&
    operator+=(StateType& lhs, DifferenceType const& rhs)
    {
        using State = detail::StateAccessor<StateType>;
        using Difference = detail::DifferenceAccessor<DifferenceType>;
        State::representation(lhs) += Difference::representation(rhs);

        return lhs;
    }

    template <typename DifferenceType, typename StateType>
        requires traits::difference<DifferenceType> and traits::state<StateType> and
                 traits::same_domain<DifferenceType, StateType> and
                 traits::same_group<StateType, DifferenceType> and
                 traits::in_curved_space<StateType>
    StateType&
    operator+=(StateType& lhs, DifferenceType const& rhs)
    {
        using State = detail::StateAccessor<StateType>;
        using Difference = detail::DifferenceAccessor<DifferenceType>;
        State::representation(lhs) = State::representation(lhs) * Difference::representation(rhs);

        return lhs;
    }

    /**
     * @brief Subtracts a difference from a state and assigns the result to the state.
     *
     * This operator modifies the left-hand-side state by subtracting the given difference from it.
     *
     * @tparam DifferenceType The type of the difference.
     * @tparam StateType The type of the state.
     * @param lhs The state from which the difference is subtracted.
     * @param rhs The difference to subtract from the state.
     * @return A reference to the modified state.
     */
    template <typename DifferenceType, typename StateType>
        requires traits::difference<DifferenceType> and traits::state<StateType> and
                 traits::same_domain<DifferenceType, StateType> and
                 traits::same_group<StateType, DifferenceType> and traits::in_flat_space<StateType>
    StateType&
    operator-=(StateType& lhs, DifferenceType const& rhs)
    {
        using State = detail::StateAccessor<StateType>;
        using Difference = detail::DifferenceAccessor<DifferenceType>;
        State::representation(lhs) -= Difference::representation(rhs);

        return lhs;
    }

    template <typename DifferenceType, typename StateType>
        requires traits::difference<DifferenceType> and traits::state<StateType> and
                 traits::same_domain<DifferenceType, StateType> and
                 traits::same_group<StateType, DifferenceType> and
                 traits::in_curved_space<StateType>
    StateType&
    operator-=(StateType& lhs, DifferenceType const& rhs)
    {
        using State = detail::StateAccessor<StateType>;
        using Difference = detail::DifferenceAccessor<DifferenceType>;
        State::representation(lhs) =
            State::representation(lhs) * Difference::representation(rhs).inverse();

        return lhs;
    }



    template <typename DifferenceType>
        requires traits::difference<DifferenceType>
    DifferenceType
    operator-(DifferenceType const& object)
    {
        return inverse(object);
    }

    /**
     * @brief Scale the difference with a given scalar.
     *
     * @param lhs Difference type to be scaled.
     * @param rhs Scalar the difference should be scaled with.
     * @return Scaled difference.
     */
    template <typename DifferenceType>
        requires traits::difference<DifferenceType> and traits::in_flat_space<DifferenceType>
    DifferenceType
    operator*(DifferenceType const& lhs, long const rhs)
    {
        using ScalarDifference = detail::DifferenceAccessor<DifferenceType>;

        return ScalarDifference::make(ScalarDifference::representation(lhs) * rhs);
    }

    template <typename DifferenceType>
        requires traits::angular_difference<DifferenceType>
    DifferenceType
    operator*(DifferenceType const& lhs, long const rhs)
    {
        using AngularDifference = detail::DifferenceAccessor<DifferenceType>;

        auto const aa =
            geometry::AxisAngle::from_eigen(AngularDifference::representation(lhs)) * rhs;

        return AngularDifference::make(Eigen::Quaterniond(aa.to_eigen()));
    }

    /**
     * @brief Scale the difference with a given scalar.
     *
     * @param lhs Scalar the difference should be scaled with.
     * @param rhs Difference type to be scaled.
     * @return Scaled difference.
     */
    template <typename DifferenceType>
        requires traits::difference<DifferenceType>
    DifferenceType
    operator*(long const lhs, DifferenceType const& rhs)
    {
        using ScalarDifference = detail::DifferenceAccessor<DifferenceType>;

        return ScalarDifference::make(ScalarDifference::representation(rhs) * lhs);
    }

    /**
     * @brief Scale the difference with a given scalar.
     *
     * @param lhs Difference type to be scaled.
     * @param rhs Scalar the difference should be scaled with.
     * @return Scaled difference.
     */
    template <typename DifferenceType>
        requires traits::difference<DifferenceType> and traits::in_flat_space<DifferenceType>
    DifferenceType
    operator/(DifferenceType const& lhs, long const rhs)
    {
        using FlatDifference = detail::DifferenceAccessor<DifferenceType>;

        return FlatDifference::make(FlatDifference::representation(lhs) / rhs);
    }

    template <typename DifferenceType>
        requires traits::angular_difference<DifferenceType>
    DifferenceType
    operator/(DifferenceType const& lhs, long const rhs)
    {
        using AngularDifference = detail::DifferenceAccessor<DifferenceType>;

        auto const aa =
            geometry::AxisAngle::from_eigen(AngularDifference::representation(lhs)) / rhs;

        return AngularDifference::make(Eigen::Quaterniond(aa.to_eigen()));
    }
}