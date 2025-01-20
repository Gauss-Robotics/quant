#pragma once

#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/geometry/forward_declarations.h>

#include <Eigen/Core>

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
         * @brief Conversion operator to cast Difference to its StateType.
         *
         * @return The state representing the difference.
         */
        explicit
        operator StateType() const
        {
            return _difference_object;
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

        bool
        is_approx(Difference<StateType> const& rhs,
                  double const tolerance = Eigen::NumTraits<double>::dummy_precision()) const
        {
            return _difference_object.is_approx(rhs._difference_object, tolerance);
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
        requires traits::state<StateType> and traits::in_flat_space<StateType>
    traits::difference_type_of<StateType>
    operator-(StateType const& lhs, StateType const& rhs)
    {
        using State = detail::StateAccessor<StateType>;
        using Difference = detail::DifferenceAccessor<traits::difference_type_of<StateType>>;

        return Difference::make(State::representation(lhs) - State::representation(rhs));
    }

    template <typename StateType>
        requires traits::state<StateType> and traits::in_curved_space<StateType>
    traits::difference_type_of<StateType>
    operator-(StateType const& lhs, StateType const& rhs)
    {
        using State = detail::StateAccessor<StateType>;
        using Difference = detail::DifferenceAccessor<traits::difference_type_of<StateType>>;

        return Difference::make(State::representation(rhs).inverse() * State::representation(lhs));
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
                 traits::same_group<StateType, DifferenceType> and
                 traits::in_flat_space<StateType>
    StateType
    operator-(StateType const& lhs, DifferenceType const& rhs)
    {
        using State = detail::StateAccessor<StateType>;
        using Difference = detail::DifferenceAccessor<DifferenceType>;

        return State::make(State::representation(lhs) - Difference::representation(rhs));
    }

    template <typename StateType, typename DifferenceType>
        requires traits::difference<DifferenceType> and traits::state<StateType> and
                 traits::same_domain<DifferenceType, StateType> and
                 traits::same_group<StateType, DifferenceType> and
                 traits::in_curved_space<StateType>
    StateType
    operator-(StateType const& lhs, DifferenceType const& rhs)
    {
        using State = detail::StateAccessor<StateType>;
        using Difference = detail::DifferenceAccessor<DifferenceType>;

        return State::make(State::representation(lhs) * Difference::representation(rhs).inverse());
    }

    /**
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
                 traits::same_group<StateType, DifferenceType> and
                 traits::in_flat_space<StateType>
    StateType
    operator+(StateType const& lhs, DifferenceType const& rhs)
    {
        using State = detail::StateAccessor<StateType>;
        using Difference = detail::DifferenceAccessor<DifferenceType>;

        return State::make(State::representation(lhs) + Difference::representation(rhs));
    }

    template <typename StateType, typename DifferenceType>
        requires traits::difference<DifferenceType> and traits::state<StateType> and
                 traits::same_domain<DifferenceType, StateType> and
                 traits::same_group<StateType, DifferenceType> and
                 traits::in_curved_space<StateType>
    StateType
    operator+(StateType const& lhs, DifferenceType const& rhs)
    {
        using State = detail::StateAccessor<StateType>;
        using Difference = detail::DifferenceAccessor<DifferenceType>;

        // Manifold Right Plus
        return State::make(State::representation(lhs) * Difference::representation(rhs));
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
                 traits::same_group<StateType, DifferenceType> and
                 traits::in_flat_space<StateType>
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
        // TODO: test if this is correct
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
                 traits::same_group<StateType, DifferenceType> and
                 traits::in_flat_space<StateType>
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

#ifdef QUANT_ALLOW_DIFFERENCE_ADDITION
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
        requires traits::difference<DifferenceType> and traits::in_flat_space<DifferenceType>
    DifferenceType
    operator+(DifferenceType const& lhs, DifferenceType const rhs)
    {
        using Difference = detail::DifferenceAccessor<DifferenceType>;

        return Difference::make(Difference::representation(lhs) + Difference::representation(rhs));
    }

    template <typename DifferenceType>
        requires traits::difference<DifferenceType> and traits::in_curved_space<DifferenceType>
    DifferenceType
    operator+(DifferenceType const& lhs, DifferenceType const rhs)
    {
        using Difference = detail::DifferenceAccessor<DifferenceType>;

        // TODO: Test this
        // TODO: Check if this makes sense on a manifold
        return Difference::make(Difference::representation(lhs) * Difference::representation(rhs));
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
        requires traits::difference<DifferenceType> and traits::in_flat_space<DifferenceType>
    DifferenceType&
    operator+=(DifferenceType& lhs, DifferenceType const& rhs)
    {
        using Difference = detail::DifferenceAccessor<DifferenceType>;

        Difference::representation(lhs) += Difference::representation(rhs);
        return lhs;
    }

    template <typename DifferenceType>
        requires traits::difference<DifferenceType> and traits::in_curved_space<DifferenceType>
    DifferenceType&
    operator+=(DifferenceType& lhs, DifferenceType const& rhs)
    {
        using Difference = detail::DifferenceAccessor<DifferenceType>;

        Difference::representation(lhs) =
            Difference::representation(lhs) * Difference::representation(rhs);
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
        requires traits::difference<DifferenceType> and traits::in_flat_space<DifferenceType>
    DifferenceType
    operator-(DifferenceType const& lhs, DifferenceType const rhs)
    {
        using Difference = detail::DifferenceAccessor<DifferenceType>;

        return Difference::make(Difference::representation(lhs) - Difference::representation(rhs));
    }

    template <typename DifferenceType>
        requires traits::difference<DifferenceType> and traits::in_curved_space<DifferenceType>
    DifferenceType
    operator-(DifferenceType const& lhs, DifferenceType const rhs)
    {
        using Difference = detail::DifferenceAccessor<DifferenceType>;

        return Difference::make(Difference::representation(lhs) *
                                Difference::representation(rhs).inverse());
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
        requires traits::difference<DifferenceType> and traits::in_flat_space<DifferenceType>
    DifferenceType&
    operator-=(DifferenceType& lhs, DifferenceType const& rhs)
    {
        using ScalarDifference = detail::DifferenceAccessor<DifferenceType>;

        ScalarDifference::representation(lhs) -= ScalarDifference::representation(rhs);
        return lhs;
    }

    template <typename DifferenceType>
        requires traits::difference<DifferenceType> and traits::in_curved_space<DifferenceType>
    DifferenceType&
    operator-=(DifferenceType& lhs, DifferenceType const& rhs)
    {
        using ScalarDifference = detail::DifferenceAccessor<DifferenceType>;

        ScalarDifference::representation(lhs) =
            ScalarDifference::representation(lhs) * ScalarDifference::representation(rhs).inverse();
        return lhs;
    }
#endif

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
        requires traits::difference<DifferenceType> and traits::in_flat_space<DifferenceType>
    DifferenceType
    operator-(DifferenceType const& object)
    {
        using ScalarDifference = detail::DifferenceAccessor<DifferenceType>;

        return ScalarDifference::make(-ScalarDifference::representation(object));
    }

    template <typename DifferenceType>
        requires traits::difference<DifferenceType> and traits::in_curved_space<DifferenceType>
    DifferenceType
    operator-(DifferenceType const& object)
    {
        using ScalarDifference = detail::DifferenceAccessor<DifferenceType>;

        return ScalarDifference::make(ScalarDifference::representation(object).inverse());
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

}  // namespace quant::geometry
