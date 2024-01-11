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
        Difference() : _difference_object{}
        {
            ;
        }

        explicit Difference(StateType const& difference_object) :
            _difference_object{difference_object}
        {
            ;
        }

        static traits::difference_type_of<StateType>
        zero()
        {
            return traits::difference_type_of<StateType>{StateType::zero()};
        }

        bool
        operator==(Difference<StateType> const& rhs) const
        {
            return _difference_object == rhs._difference_object;
        }

        bool
        operator!=(Difference<StateType> const& rhs) const
        {
            return _difference_object != rhs._difference_object;
        }

        auto
        operator<=>(Difference<StateType> const& rhs) const
        {
            return _difference_object <=> rhs._difference_object;
        }

        std::string
        to_string() const
        {
            return _difference_object.to_string();
        }

    protected:
        StateType _difference_object;

    public:
        using DifferenceObjectType = StateType;
        using GeometricRepresentationType = typename StateType::GeometricRepresentationType;

        friend class detail::DifferenceAccessor<Difference<StateType>>;
        friend class detail::DifferenceAccessor<traits::difference_type_of<StateType>>;
    };

    /**
     * @brief Generic difference operator.
     *
     * Returns the difference of the left-hand-side and right-hand-side either as the defined
     * difference type of the template type QuantityT, or generally as `Difference<QuantityT>` if
     * and only if `QuantityT` is a state.
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

    template <typename DifferenceType, typename StateType>
        requires traits::scalar_difference<DifferenceType> and traits::scalar_state<StateType> and
                 traits::same_domain<DifferenceType, StateType>
    StateType
    operator+(DifferenceType const& lhs, StateType const& rhs)
    {
        using State = detail::StateAccessor<StateType>;
        using Difference = detail::DifferenceAccessor<DifferenceType>;

        return State::make(Difference::representation(lhs) + State::representation(rhs));
    }

    /**
     * @brief Add two differences.
     *
     * @param lhs Left-hand-side summand difference.
     * @param lhs Right-hand-side summand difference.
     * @return Sum of the two differences.
     */
    template <typename ScalarDifferenceType>
        requires traits::scalar_difference<ScalarDifferenceType>
    ScalarDifferenceType
    operator+(ScalarDifferenceType const& lhs, ScalarDifferenceType const rhs)
    {
        using ScalarDifference = detail::DifferenceAccessor<ScalarDifferenceType>;

        return ScalarDifference::make(ScalarDifference::representation(lhs) +
                                      ScalarDifference::representation(rhs));
    }

    /**
     * @brief Subtract one difference from another.
     *
     * @param lhs Diffence to subtract rhs from.
     * @param lhs Difference to subtract from lhs.
     * @return Difference resulting from subtracting rhs from lhs.
     */
    template <typename ScalarDifferenceType>
        requires traits::scalar_difference<ScalarDifferenceType>
    ScalarDifferenceType
    operator-(ScalarDifferenceType const& lhs, ScalarDifferenceType const rhs)
    {
        using ScalarDifference = detail::DifferenceAccessor<ScalarDifferenceType>;

        return ScalarDifference::make(ScalarDifference::representation(lhs) -
                                      ScalarDifference::representation(rhs));
    }

    template <typename ScalarDifferenceType>
        requires traits::scalar_difference<ScalarDifferenceType>
    ScalarDifferenceType
    operator-(ScalarDifferenceType const& object)
    {
        using ScalarDifference = detail::DifferenceAccessor<ScalarDifferenceType>;

        return ScalarDifference::make(-ScalarDifference::representation(object));
    }

    /**
     * @brief Scale the difference with a given scalar.
     *
     * @param lhs Difference type to be scaled.
     * @param rhs Scalar the difference should be scaled with.
     * @return Scaled difference.
     */
    template <typename ScalarDifferenceType>
        requires traits::scalar_difference<ScalarDifferenceType>
    ScalarDifferenceType
    operator*(ScalarDifferenceType const& lhs, long const rhs)
    {
        using ScalarDifference = detail::DifferenceAccessor<ScalarDifferenceType>;

        return ScalarDifference::make(ScalarDifference::representation(lhs) * rhs);
    }

    /**
     * @brief Scale the difference with a given scalar.
     *
     * @param lhs Scalar the difference should be scaled with.
     * @param rhs Difference type to be scaled.
     * @return Scaled difference.
     */
    template <typename ScalarDifferenceType>
        requires traits::scalar_difference<ScalarDifferenceType>
    ScalarDifferenceType
    operator*(long const lhs, ScalarDifferenceType const& rhs)
    {
        using ScalarDifference = detail::DifferenceAccessor<ScalarDifferenceType>;

        return ScalarDifference::make(ScalarDifference::representation(rhs) * lhs);
    }

    /**
     * @brief Get the ratio between two scalar differneces.
     *
     * @param lhs
     * @param rhs
     * @return Ratio of the two differences as double.
     */
    template <typename ScalarDifferenceType>
        requires traits::scalar_difference<ScalarDifferenceType>
    double
    operator/(ScalarDifferenceType const& lhs, ScalarDifferenceType const& rhs)
    {
        using ScalarDifference = detail::DifferenceAccessor<ScalarDifferenceType>;

        return ScalarDifference::representation(lhs) / ScalarDifference::representation(rhs);
    }

    /**
     * @brief State translation operator
     * @param lhs Translation as linear difference
     * @param rhs State to be translated as linear state
     * @return Translated state as linear state
     */
    template <typename LinearDifferenceType, typename LinearStateType>
        requires traits::linear_difference<LinearDifferenceType> and
                 traits::linear_state<LinearStateType> and
                 traits::same_domain<LinearDifferenceType, LinearStateType>
    LinearStateType
    operator+(LinearDifferenceType const& lhs, LinearStateType const& rhs)
    {
        using LinearState = detail::StateAccessor<LinearStateType>;
        using LinearDifference = detail::DifferenceAccessor<LinearDifferenceType>;

        return LinearState::make(LinearDifference::representation(lhs) +
                                 LinearState::representation(rhs));
    }

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
