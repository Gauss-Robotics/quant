#pragma once

#include <quant/framed_geometry/BaseChange.h>
#include <quant/framed_geometry/FrameMismatch.h>
#include <quant/framed_geometry/forward_declarations.h>
#include <quant/geometry/Difference.h>
#include <quant/geometry/forward_declarations.h>

#include <Eigen/Core>

#include <array>
#include <cassert>
#include <compare>
#include <cstdio>
#include <string>
#include <string_view>

namespace quant::framed_geometry
{

    /**
     * @brief Uniquely identifies a frame.
     */
    struct FrameIdentifier
    {
        std::string_view name = "";
        std::string_view base_frame = "";
    };

    /**
     * @brief Wrapper to associate a named geometric object with a base frame.
     *
     * On construction, the name and base frame strings referred to the string_views in a `Frame`
     * are copied into own internal private members (`_name_data` and `_base_frame_data`) on the
     * stack with a maximum number of chars defined in `frame_data_max_string_size`. The names can
     * be accessed using the accessors `name()` and `base_frame()`.
     *
     * @tparam QuantityT Geometric State or difference object type.
     */
    template <typename QuantityT>
        requires traits::is_frameable<QuantityT> and traits::state<QuantityT>
    class State
    {
    public:
        using FramedGeometricObject = QuantityT;

        /**
         * @brief Constructs a framed geometric object given a geometric object and a frame header
         * consisting of a base frame and name.
         *
         * @param object_to_frame Geometric object to frame.
         * @param frame_data Frame header.
         */
        State(QuantityT const& object_to_frame, FrameIdentifier const& frame_data) :
            _framed_object{object_to_frame}
        {
            // NOLINTBEGIN(cppcoreguidelines-pro-type-vararg)
            std::snprintf(_frame_name.data(), _frame_name.size(), "%s", frame_data.name.data());
            std::snprintf(_base_frame_name.data(),
                          _base_frame_name.size(),
                          "%s",
                          frame_data.base_frame.data());
            // NOLINTEND(cppcoreguidelines-pro-type-vararg)
        }

        /**
         * @brief Enframe a state object in the frame of this framed object.
         *
         * Allows to easily construct a framed state object by enframing it in this object.
         *
         * For state objects, a name is optional.  If the type of object_to_frame is a state type,
         * this additional overload of enframe() without the name parameter is offered.
         *
         * @param object_to_frame Object that should be framed in this object.
         * @return Framed type of object_to_frame.
         */
        template <typename DifferenceT>
            requires traits::difference<DifferenceT>
        traits::framed_type_of<DifferenceT>
        enframe(DifferenceT const& object_to_frame) const
        {
            return {object_to_frame, get_name()};
        }

        /**
         * @brief Enframe a geometric object in the frame of this framed object.
         *
         * Allows to easily construct a framed geometric object by enframing it in this object and
         * giving it a name.
         *
         * @param object_to_frame Object that should be framed in this object.
         * @param name Name of the object.
         * @return Framed type of object_to_frame.
         */
        template <typename Type>
            requires traits::state<Type>
        traits::framed_type_of<Type>
        enframe(Type const& object_to_frame, std::string_view name) const
        {
            return traits::framed_type_of<Type>(object_to_frame,
                                                {.name = name, .base_frame = get_name()});
        }

        std::string_view
        get_name() const
        {
            return _frame_name.data();
        }

        std::string_view
        get_base_frame() const
        {
            return _base_frame_name.data();
        }

        QuantityT const&
        get_framed_object() const
        {
            return _framed_object;
        }

        std::string
        to_string() const
        {
            std::string named_entity{get_name()};
            std::string in_frame{get_base_frame()};  // Base frame might be empty for global frame.

            if (not in_frame.empty())
            {
                in_frame = "w.r.t. " + in_frame;
            }
            else
            {
                in_frame = "global";
            }

            return named_entity + " (" + in_frame + ") at " + _framed_object.to_string();
        }

        bool
        is_approx(State const& rhs,
                  double const tolerance = geometry::constants::floating_point_tolerance) const
        {
            return get_base_frame() == rhs.get_base_frame() and get_name() == rhs.get_name() and
                   _framed_object.is_approx(rhs._framed_object, tolerance);
        }

        static traits::framed_type_of<QuantityT>
        zero(FrameIdentifier const& frame_data)
        {
            return traits::framed_type_of<QuantityT>{QuantityT::zero(), frame_data};
        }

        /**
         * @brief Default constructs a framed geometric object.
         */
        State() = delete;

    private:
        /**
         * @brief Name of the held geometric object.
         */
        const_size_string _frame_name;

        /**
         * @brief Name of the base frame of the held geometric object.
         */
        const_size_string _base_frame_name;

        /**
         * @brief Framed geometric object.
         */
        QuantityT _framed_object;
    };

    template <typename FramedT>
        requires traits::framed_state<FramedT>
    FramedT
    operator*(BaseChange const& transform, FramedT const& quantity)
    {
        using Traits = traits::framed_traits_of<traits::unframed_type_of<FramedT>>;
#ifdef QUANT_ENABLE_EXCEPTIONS
        if (transform.from_frame != quantity.get_base_frame())
        {
            throw FrameMismatchException(transform.from_frame, quantity.get_base_frame());
        }
#endif

        return FramedT{Traits::basis_change_function(quantity.get_framed_object(), transform),
                       {.name = quantity.get_name(), .base_frame = transform.to_frame}};
    }

    /**
     * @brief State difference operator.
     *
     * Note that this behaves inconsistent between flat and curved space. In flat space,
     *
     * @param lhs
     * @param rhs
     * @return
     */

    template <typename StateType>
        requires traits::state<StateType>
    traits::framed_type_of<traits::difference_type_of<StateType>>
    operator-(State<StateType> const& lhs, State<StateType> const& rhs)
    {
#ifdef QUANT_ENABLE_EXCEPTIONS
        if (lhs.get_base_frame() != rhs.get_base_frame())
        {
            throw FrameMismatchException(lhs.get_base_frame(), rhs.get_base_frame());
        }
#endif
        /**
         * This is actually not entirely true: The difference of two states (at least in curved
         *space) is always expressed in the local frame of the state that is subtracted (i.e., rhs).
         *This is due to the convention of using the right plus and minus operators.
         *
         * However, the base frame of a difference is not the same "type of frame" as mentioned
         *above. It is simply a check, whether a state and difference can be combined. For
         *orientations and poses, this doesn't matter because the difference does not change with a
         *frame change, however, for positions it does indeed change.
         *
         * Therefore, here we go with the conservative approach and only allow differences to be
         *added to states, if they are in the same frame (in the sense of the base frame name).
         **/
        return traits::framed_type_of<traits::difference_type_of<StateType>>(
            lhs.get_framed_object() - rhs.get_framed_object(), rhs.get_base_frame());
    }

    /**
     * @brief Translation application operator.
     *
     * @param state
     * @param difference
     * @return
     */
    template <typename FramedDifferenceType, typename FramedStateType>
        requires traits::framed_difference<FramedDifferenceType> and
                 traits::framed_state<FramedStateType> and
                 traits::same_framed_domain<FramedDifferenceType, FramedStateType>
    FramedStateType
    operator+(FramedStateType const& state, FramedDifferenceType const& difference)
    {
        using StateType = typename FramedStateType::FramedGeometricObject;

#ifdef QUANT_ENABLE_EXCEPTIONS
        if (state.get_base_frame() != difference.get_base_frame())
        {
            throw FrameMismatchException(state.get_base_frame(), difference.get_base_frame());
        }
#endif
        return traits::framed_type_of<StateType>(
            state.get_framed_object() + difference.get_framed_object(),
            {.name = state.get_name(), .base_frame = state.get_base_frame()});
    }

    template <typename FramedT>
        requires traits::framed_state<FramedT>
    std::ostream&
    operator<<(std::ostream& os, FramedT const& rhs)
    {
        return os << rhs.to_string();
    }
}  // namespace quant::framed_geometry
