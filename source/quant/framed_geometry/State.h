#pragma once

#include <quant/framed_geometry/BaseChange.h>
#include <quant/framed_geometry/FrameMismatch.h>
#include <quant/framed_geometry/forward_declarations.h>
#include <quant/geometry/Difference.h>
#include <quant/geometry/detail/ManifoldOperators.h>
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
        using DifferenceT = traits::difference_type_of<QuantityT>;
        using FramedDifferenceT = traits::framed_type_of<DifferenceT>;
        using FramedT = traits::framed_type_of<QuantityT>;

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

        static FramedT
        zero(FrameIdentifier const& frame_data)
        {
            return FramedT{QuantityT::zero(), frame_data};
        }

        FramedDifferenceT
        lminus(State const& rhs) const
        {
            if (get_base_frame() != rhs.get_base_frame())
            {
                throw FrameMismatchException(get_base_frame(), rhs.get_base_frame());
            }
            return FramedDifferenceT{geometry::lminus(get_framed_object(), rhs.get_framed_object()),
                                     rhs.get_base_frame()};
        }

        FramedDifferenceT
        rminus(State const& rhs) const
        {
            if (get_base_frame() != rhs.get_base_frame())
            {
                throw FrameMismatchException(get_base_frame(), rhs.get_base_frame());
            }
            if constexpr (traits::on_manifold<QuantityT> and not traits::in_t3<QuantityT>)
            {
                // TODO: I don't like the inconsistency between T3 and SO3/SE3 here, but I don't
                //  know how else to solve it
                return FramedDifferenceT{
                    geometry::rminus(get_framed_object(), rhs.get_framed_object()), rhs.get_name()};
            }
            // flat space differences are always in the base frame
            return FramedDifferenceT{geometry::rminus(get_framed_object(), rhs.get_framed_object()),
                                     rhs.get_base_frame()};
        }

        FramedT
        lplus(FramedDifferenceT const& rhs) const
        {
            if (get_base_frame() != rhs.get_base_frame())
            {
                throw FrameMismatchException(get_name(), rhs.get_base_frame());
            }
            return FramedT{geometry::lplus(get_framed_object(), rhs.get_framed_object()),
                           {.name = get_name(), .base_frame = get_base_frame()}};
        }

        FramedT
        rplus(FramedDifferenceT const& rhs) const
        {
            if (get_name() != rhs.get_base_frame())
            {
                throw FrameMismatchException(get_name(), rhs.get_base_frame());
            }
            return FramedT{geometry::rplus(get_framed_object(), rhs.get_framed_object()),
                           {.name = get_name(), .base_frame = get_base_frame()}};
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
        if (transform.from_frame != quantity.get_base_frame())
        {
            throw FrameMismatchException(transform.from_frame, quantity.get_base_frame());
        }

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

    template <typename FramedStateType>
        requires traits::framed_state<FramedStateType> and
                 traits::on_tangent_space<typename FramedStateType::FramedGeometricObject>
    FramedStateType
    operator+(FramedStateType const& lhs, FramedStateType const& rhs)
    {
        if (lhs.get_base_frame() != rhs.get_base_frame())
        {
            throw FrameMismatchException(lhs.get_base_frame(), rhs.get_base_frame());
        }
        /**
         * This is for flat space, where two states can be added, e.g. to forces, wrenches,
         *velocities, etc.
         * TODO: overthink if this is correct and necessary, because there should not be such a
         *  difference between flat and curved states
         **/
        auto const diff = traits::framed_difference_of<FramedStateType>(
            static_cast<traits::difference_type_of<traits::unframed_type_of<FramedStateType>>>(
                rhs.get_framed_object()),
            lhs.get_name());
        return lhs + diff;
    }

    /**
     * @brief Difference of two framed states, expressed in the base frame of the subtracted state.
     *
     *  The difference of two states is expressed in the global/base frame of the subtracted
     * (i.e., starting) state. This is due to the convention of using the left plus and minus
     * operators for framed units.
     *
     * This convention was chosen because it leads to consistent behavior for flat and curved
     * spaces. Using local frames leads to inconsistent and/or dangerous behavior for flat
     * spaces, as these are always expressed in the global frame. From Appendix E, of
     * https://arxiv.org/pdf/1812.01537, it becomes apparent that for Rn right and left
     * operators are the same. This means that there is no distinction between local and global
     * frames for flat space. However, if we would follow the convention for curved space and
     * have the difference in the local frame, this would lead to inconsistent behavior in frame
     * changes, as e.g., the difference of two positions does indeed change from one frame to
     * the other.
     *
     * Therefore, we opt for the consistent treatment of flat and curved spaces and express
     * differences always in the global space. If this is not wanted, the explicit rminus
     * operator can be chosen
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
        if (lhs.get_base_frame() != rhs.get_base_frame())
        {
            throw FrameMismatchException(lhs.get_base_frame(), rhs.get_base_frame());
        }
        return lhs.lminus(rhs);
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
        if (state.get_name() == difference.get_base_frame())
        {
            return state.rplus(difference);
        }
        if (state.get_base_frame() == difference.get_base_frame())
        {
            return state.lplus(difference);
        }
        throw FrameMismatchException(state.get_name(), difference.get_base_frame());
    }

    template <typename FramedT>
        requires traits::framed_state<FramedT>
    std::ostream&
    operator<<(std::ostream& os, FramedT const& rhs)
    {
        return os << rhs.to_string();
    }
}  // namespace quant::framed_geometry
