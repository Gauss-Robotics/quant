#pragma once

#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/geometry/forward_declarations.h>

#include <compare>
#include <concepts>
#include <string>
#include <type_traits>
#include <typeinfo>

namespace quant::geometry
{

    /**
     * @brief Represents the difference of two states of type StateType.
     *
     * @tparam StateType State used for representing the difference.
     */
    template <typename StateType>
    class Difference
    {
    public:
        /**
         * @brief Default constructor initializing the difference object.
         */
        Difference() : _difference_object{}
        {
            ;
        }

        /**
         * @brief Constructor initializing the difference object with a given state.
         *
         * @param difference_object The state to initialize the difference object with.
         */
        explicit Difference(StateType const& difference_object) :
            _difference_object{difference_object}
        {
            ;
        }

        /**
         * @brief Returns a zero-initialized difference object.
         *
         * @return A zero-initialized difference object.
         */
        static traits::difference_type_of<StateType>
        zero()
        {
            return traits::difference_type_of<StateType>{StateType::zero()};
        }

        /**
         * @brief Equality operator.
         *
         * @param rhs The right-hand side difference object to compare with.
         * @return True if the difference objects are equal, false otherwise.
         */
        bool
        operator==(Difference<StateType> const& rhs) const
        {
            return _difference_object == rhs._difference_object;
        }

        /**
         * @brief Inequality operator.
         *
         * @param rhs The right-hand side difference object to compare with.
         * @return True if the difference objects are not equal, false otherwise.
         */
        bool
        operator!=(Difference<StateType> const& rhs) const
        {
            return _difference_object != rhs._difference_object;
        }

        /**
         * @brief Three-way comparison operator.
         *
         * @param rhs The right-hand side difference object to compare with.
         * @return The result of the three-way comparison.
         */
        auto
        operator<=>(Difference<StateType> const& rhs) const
        {
            return _difference_object <=> rhs._difference_object;
        }

        /**
         * @brief Converts the difference object to a string representation.
         *
         * @return A string representation of the difference object.
         */
        std::string
        to_string() const
        {
            return _difference_object.to_string();
        }

    protected:
        StateType _difference_object;  ///< The state representing the difference.

    public:
        using DifferenceObjectType = StateType;
        using GeometricRepresentationType = typename StateType::GeometricRepresentationType;

        friend class detail::DifferenceAccessor<Difference<StateType>>;
        friend class detail::DifferenceAccessor<traits::difference_type_of<StateType>>;
    };

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
        using State = detail::StateAccessor<StateType>;
        using Difference = detail::DifferenceAccessor<traits::difference_type_of<StateType>>;

        return Difference::make(State::representation(lhs) - State::representation(rhs));
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
                 traits::same_domain<DifferenceType, StateType>
    StateType
    operator-(StateType const& lhs, DifferenceType const& rhs)
    {
        using State = detail::StateAccessor<StateType>;
        using Difference = detail::DifferenceAccessor<DifferenceType>;

        return State::make(Difference::representation(rhs) - State::representation(lhs));
    }

    /**
     * @brief Adds a difference to a state from the right.
     *
     * This operator returns a new state resulting from adding a given difference to a state.
     *
     * @tparam StateType The type of the state.
     * @tparam DifferenceType The type of the difference.
     * @param lhs The state to which the difference is added.
     * @param rhs The difference to add.
     * @return The resulting state after adding the difference.
     */
    template <typename StateType, typename DifferenceType>
        requires traits::difference<DifferenceType> and traits::state<StateType> and
                 traits::same_domain<DifferenceType, StateType>
    StateType
    operator+(StateType const& lhs, DifferenceType const& rhs)
    {
        using State = detail::StateAccessor<StateType>;
        using Difference = detail::DifferenceAccessor<DifferenceType>;

        return State::make(Difference::representation(rhs) + State::representation(lhs));
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
                 traits::same_domain<DifferenceType, StateType>
    StateType&
    operator+=(StateType& lhs, DifferenceType const& rhs)
    {
        using State = detail::StateAccessor<StateType>;
        using Difference = detail::DifferenceAccessor<DifferenceType>;
        State::representation(lhs) + Difference::representation(rhs);
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
                 traits::same_domain<DifferenceType, StateType>
    StateType&
    operator-=(StateType& lhs, DifferenceType const& rhs)
    {
        using State = detail::StateAccessor<StateType>;
        using Difference = detail::DifferenceAccessor<DifferenceType>;
        State::representation(lhs) - Difference::representation(rhs);
        return lhs;
    }

    /**
     * @brief Adds two differences.
     *
     * This function returns the sum of two given differences.
     *
     * @param lhs The left-hand-side summand difference.
     * @param rhs The right-hand-side summand difference.
     * @return The sum of the two differences.
     */
    template <typename DifferenceType>
        requires traits::difference<DifferenceType>
    DifferenceType
    operator+(DifferenceType const& lhs, DifferenceType const rhs)
    {
        using ScalarDifference = detail::DifferenceAccessor<DifferenceType>;

        return ScalarDifference::make(ScalarDifference::representation(lhs) +
                                      ScalarDifference::representation(rhs));
    }

    /**
     * @brief Inplace addition of two differences.
     *
     * This operator modifies the left-hand-side difference by adding the right-hand-side difference
     * to it.
     *
     * @param lhs The left-hand-side difference to which the right-hand-side difference is added.
     * @param rhs The right-hand-side difference to add to the left-hand-side difference.
     * @return A reference to the modified left-hand-side difference.
     */
    template <typename DifferenceType>
        requires traits::difference<DifferenceType>
    DifferenceType&
    operator+=(DifferenceType& lhs, DifferenceType const& rhs)
    {
        using ScalarDifference = detail::DifferenceAccessor<DifferenceType>;

        ScalarDifference::representation(lhs) += ScalarDifference::representation(rhs);
        return lhs;
    }

    /**
     * @brief Subtract one difference from another.
     *
     * @param lhs Diffence to subtract rhs from.
     * @param lhs Difference to subtract from lhs.
     * @return Difference resulting from subtracting rhs from lhs.
     */
    template <typename DifferenceType>
        requires traits::difference<DifferenceType>
    DifferenceType
    operator-(DifferenceType const& lhs, DifferenceType const rhs)
    {
        using ScalarDifference = detail::DifferenceAccessor<DifferenceType>;

        return ScalarDifference::make(ScalarDifference::representation(lhs) -
                                      ScalarDifference::representation(rhs));
    }

    /**
     * @brief Inplace subtraction of two differences.
     *
     * This operator modifies the left-hand-side difference by subtracting the right-hand-side
     * difference from it.
     *
     * @param lhs The left-hand-side difference from which the right-hand-side difference is
     * subtracted.
     * @param rhs The right-hand-side difference to subtract from the left-hand-side difference.
     * @return A reference to the modified left-hand-side difference.
     */
    template <typename DifferenceType>
        requires traits::difference<DifferenceType>
    DifferenceType&
    operator-=(DifferenceType& lhs, DifferenceType const& rhs)
    {
        using ScalarDifference = detail::DifferenceAccessor<DifferenceType>;

        ScalarDifference::representation(lhs) -= ScalarDifference::representation(rhs);
        return lhs;
    }

    /**
     * @brief Negates a scalar difference.
     *
     * This operator returns the negation of the given scalar difference.
     *
     * @tparam DifferenceType The type of the scalar difference.
     * @param object The scalar difference to negate.
     * @return The negated scalar difference.
     */
    template <typename DifferenceType>
        requires traits::difference<DifferenceType>
    DifferenceType
    operator-(DifferenceType const& object)
    {
        using ScalarDifference = detail::DifferenceAccessor<DifferenceType>;

        return ScalarDifference::make(-ScalarDifference::representation(object));
    }

    /**
     * @brief Scale the difference with a given scalar.
     *
     * @param lhs Difference type to be scaled.
     * @param rhs Scalar the difference should be scaled with.
     * @return Scaled difference.
     */
    template <typename DifferenceType>
        requires traits::difference<DifferenceType>
    DifferenceType
    operator*(DifferenceType const& lhs, long const rhs)
    {
        using ScalarDifference = detail::DifferenceAccessor<DifferenceType>;

        return ScalarDifference::make(ScalarDifference::representation(lhs) * rhs);
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
        requires traits::difference<DifferenceType>
    DifferenceType
    operator/(DifferenceType const& lhs, long const rhs)
    {
        using ScalarDifference = detail::DifferenceAccessor<DifferenceType>;

        return ScalarDifference::make(ScalarDifference::representation(lhs) / rhs);
    }

    /**
     * @brief Get the ratio between two differences.
     *
     * @param lhs
     * @param rhs
     * @return Ratio of the two differences as double.
     */
    template <typename DifferenceType>
        requires traits::difference<DifferenceType>
    double
    operator/(DifferenceType const& lhs, DifferenceType const& rhs)
    {
        using ScalarDifference = detail::DifferenceAccessor<DifferenceType>;

        return ScalarDifference::representation(lhs) / ScalarDifference::representation(rhs);
    }

    /**
     * @brief Get the ratio between two differences.
     *
     * @param lhs
     * @param rhs
     * @return Ratio of the two differences as double.
     */
    template <typename DifferenceType>
        requires traits::difference<DifferenceType>
    double
    operator/=(DifferenceType& lhs, DifferenceType const& rhs)
    {
        using ScalarDifference = detail::DifferenceAccessor<DifferenceType>;

        return ScalarDifference::representation(lhs) /= ScalarDifference::representation(rhs);
    }

    /**
     * @brief Multiplies an angular difference with a linear state.
     *
     * This operator returns a new linear state resulting from multiplying a given angular
     * difference with a linear state. The multiplication is performed using the representations of
     * the angular difference and the linear state.
     *
     * @tparam AngularDifferenceType The type of the angular difference.
     * @tparam LinearStateType The type of the linear state.
     * @param lhs The angular difference to multiply.
     * @param rhs The linear state to be multiplied.
     * @return The resulting linear state after multiplication.
     */
    template <typename AngularDifferenceType, typename LinearStateType>
        requires traits::angular_difference<AngularDifferenceType> and
                 traits::linear_state<LinearStateType> and
                 traits::same_domain<AngularDifferenceType, LinearStateType>
    LinearStateType
    operator*(AngularDifferenceType const& lhs, LinearStateType const& rhs)
    {
        using LinearState = detail::StateAccessor<LinearStateType>;
        using AngularDifference = detail::DifferenceAccessor<AngularDifferenceType>;

        return LinearState::make(AngularDifference::representation(lhs) *
                                 LinearState::representation(rhs));
    }

    /**
     * @brief Multiplies an angular difference with a linear difference.
     *
     * This operator returns a new linear difference resulting from multiplying a given angular
     * difference with a linear difference. The multiplication is performed using the
     * representations of the angular difference and the linear difference.
     *
     * @tparam AngularDifferenceType The type of the angular difference.
     * @tparam LinearDifferenceType The type of the linear difference.
     * @param lhs The angular difference to multiply.
     * @param rhs The linear difference to be multiplied.
     * @return The resulting linear difference after multiplication.
     */
    template <typename AngularDifferenceType, typename LinearDifferenceType>
        requires traits::angular_difference<AngularDifferenceType> and
                 traits::linear_difference<LinearDifferenceType> and
                 traits::same_domain<AngularDifferenceType, LinearDifferenceType>
    LinearDifferenceType
    operator*(AngularDifferenceType const& lhs, LinearDifferenceType const& rhs)
    {
        using AngularDifference = detail::DifferenceAccessor<AngularDifferenceType>;
        using LinearDifference = detail::DifferenceAccessor<LinearDifferenceType>;

        return LinearDifference::make(AngularDifference::representation(lhs) *
                                      LinearDifference::representation(rhs));
    }

    /**
     * @brief Multiplies an angular difference with an angular state.
     *
     * This operator returns a new angular state resulting from multiplying a given angular
     * difference with an angular state. The multiplication is performed using the representations
     * of the angular difference and the angular state.
     *
     * @tparam AngularDifferenceType The type of the angular difference.
     * @tparam AngularStateType The type of the angular state.
     * @param lhs The angular difference to multiply.
     * @param rhs The angular state to be multiplied.
     * @return The resulting angular state after multiplication.
     */
    template <typename AngularDifferenceType, typename AngularStateType>
        requires traits::angular_difference<AngularDifferenceType> and
                 traits::angular_state<AngularStateType> and
                 traits::same_domain<AngularDifferenceType, AngularStateType>
    AngularStateType
    operator*(AngularDifferenceType const& lhs, AngularStateType const& rhs)
    {
        using AngularState = detail::StateAccessor<AngularStateType>;
        using AngularDifference = detail::DifferenceAccessor<AngularDifferenceType>;

        return AngularState::make(AngularDifference::representation(lhs) *
                                  AngularState::representation(rhs));
    }

}  // namespace quant::geometry
