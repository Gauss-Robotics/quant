#pragma once

#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/geometry/forward_declarations.h>
#include <quant/geometry/detail/ArithmeticOperators.h>
#include <quant/geometry/detail/ManifoldOperators.h>
#include <Eigen/Core>
#include <string>

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

        traits::difference_type_of<StateType> const
        inverse()
        {
            return inverse(*this);
        }

    protected:
        StateType _difference_object;  ///< The state representing the difference.

    public:
        using DifferenceObjectType = StateType;
        using GeometricRepresentationType = typename StateType::GeometricRepresentationType;

        friend class detail::DifferenceAccessor<Difference<StateType>>;
        friend class detail::DifferenceAccessor<traits::difference_type_of<StateType>>;
    };
}  // namespace quant::geometry
