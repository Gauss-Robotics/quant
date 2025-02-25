#pragma once
#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/geometry/forward_declarations.h>

namespace quant::geometry
{
    /**
     * @brief Inverse of a difference.
     *
     * @tparam DifferenceType The type of the scalar difference.
     * @param object The scalar difference to negate.
     * @return The negated scalar difference.
     */
    template <typename DifferenceType>
        requires traits::difference<DifferenceType> and traits::on_tangent_space<DifferenceType>
    DifferenceType
    inverse(DifferenceType const& object)
    {
        using ScalarDifference = detail::DifferenceAccessor<DifferenceType>;

        return ScalarDifference::make(-ScalarDifference::representation(object));
    }

    template <typename DifferenceType>
        requires traits::difference<DifferenceType> and traits::on_manifold<DifferenceType>
    DifferenceType
    inverse(DifferenceType const& object)
    {
        using ScalarDifference = detail::DifferenceAccessor<DifferenceType>;

        return ScalarDifference::make(ScalarDifference::representation(object).inverse());
    }

    /**
     * @brief Right $\ominus$ operator for subtracting two states
     * @note Eq. 26 in https://arxiv.org/pdf/1812.01537
     * @tparam StateType
     * @param lhs
     * @param rhs
     * @return
     */
    template <typename StateType>
        requires traits::state<StateType> and traits::on_tangent_space<StateType>
    traits::difference_type_of<StateType>
    rminus(StateType const& lhs, StateType const& rhs)
    {
        using State = detail::StateAccessor<StateType>;
        using Difference = detail::DifferenceAccessor<traits::difference_type_of<StateType>>;

        return Difference::make(State::representation(lhs) - State::representation(rhs));
    }

    template <typename StateType>
        requires traits::state<StateType> and traits::on_manifold<StateType>
    traits::difference_type_of<StateType>
    rminus(StateType const& lhs, StateType const& rhs)
    {
        using State = detail::StateAccessor<StateType>;
        using Difference = detail::DifferenceAccessor<traits::difference_type_of<StateType>>;

        return Difference::make(static_cast<typename StateType::GeometricRepresentationType>(
            State::representation(rhs).inverse() * State::representation(lhs)));
    }

    /**
     * @brief Left $\ominus$ operator for subtracting two states
     * @note Eq. 28 in https://arxiv.org/pdf/1812.01537
     * @tparam StateType
     * @param lhs
     * @param rhs
     * @return
     */
    template <typename StateType>
        requires traits::state<StateType> and traits::on_tangent_space<StateType>
    traits::difference_type_of<StateType>
    lminus(StateType const& lhs, StateType const& rhs)
    {
        return rminus(lhs, rhs);
    }

    template <typename StateType>
        requires traits::state<StateType> and traits::on_manifold<StateType>
    traits::difference_type_of<StateType>
    lminus(StateType const& lhs, StateType const& rhs)
    {
        using State = detail::StateAccessor<StateType>;
        using Difference = detail::DifferenceAccessor<traits::difference_type_of<StateType>>;

        return Difference::make(static_cast<typename StateType::GeometricRepresentationType>(
            State::representation(lhs) * State::representation(rhs).inverse()));
    }

    /**
     * @brief Right $\oplus$ operator for adding a state and a difference
     * @note Eq. 25 in https://arxiv.org/pdf/1812.01537
     * @tparam StateType
     * @tparam DifferenceType
     * @param lhs
     * @param rhs
     * @return
     */
    template <typename StateType, typename DifferenceType>
        requires traits::difference<DifferenceType> and traits::state<StateType> and
                 traits::same_domain<DifferenceType, StateType> and
                 traits::same_group<StateType, DifferenceType> and traits::on_tangent_space<StateType>
    StateType
    rplus(StateType const& lhs, DifferenceType const& rhs)
    {
        using State = detail::StateAccessor<StateType>;
        using Difference = detail::DifferenceAccessor<DifferenceType>;

        return State::make(State::representation(lhs) + Difference::representation(rhs));
    }

    template <typename StateType, typename DifferenceType>
        requires traits::difference<DifferenceType> and traits::state<StateType> and
                 traits::same_domain<DifferenceType, StateType> and
                 traits::same_group<StateType, DifferenceType> and
                 traits::on_manifold<StateType>
    StateType
    rplus(StateType const& lhs, DifferenceType const& rhs)
    {
        using State = detail::StateAccessor<StateType>;
        using Difference = detail::DifferenceAccessor<DifferenceType>;

        // Manifold Right Plus
        return State::make(static_cast<typename StateType::GeometricRepresentationType>(
            State::representation(lhs) * Difference::representation(rhs)));
    }

    /**
     * @brief Left $\oplus$ operator for adding a state and a difference
     * @note Eq. 27 in https://arxiv.org/pdf/1812.01537
     * @tparam StateType
     * @tparam DifferenceType
     * @param lhs
     * @param rhs
     * @return
     */
    template <typename StateType, typename DifferenceType>
        requires traits::difference<DifferenceType> and traits::state<StateType> and
                 traits::same_domain<DifferenceType, StateType> and
                 traits::same_group<StateType, DifferenceType> and traits::on_tangent_space<StateType>
    StateType
    lplus(StateType const& lhs, DifferenceType const& rhs)
    {
        return rplus(lhs, rhs);
    }

    template <typename StateType, typename DifferenceType>
        requires traits::difference<DifferenceType> and traits::state<StateType> and
                 traits::same_domain<DifferenceType, StateType> and
                 traits::same_group<StateType, DifferenceType> and
                 traits::on_manifold<StateType>
    StateType
    lplus(StateType const& lhs, DifferenceType const& rhs)
    {
        using State = detail::StateAccessor<StateType>;
        using Difference = detail::DifferenceAccessor<DifferenceType>;

        // Manifold Right Plus
        return State::make(static_cast<typename StateType::GeometricRepresentationType>(
            Difference::representation(rhs) * State::representation(lhs)));
    }
}  // namespace quant::geometry
