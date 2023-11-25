#pragma once

#include <quant/framed_geometry_fwd.h>
#include <quant/geometry/Difference.h>
#include <quant/geometry_fwd.h>

#include <Eigen/Core>

#include <array>
#include <cassert>
#include <compare>
#include <cstdio>
#include <ostream>
#include <string>
#include <string_view>

namespace quant::framed_geometry
{

    /**
     * @brief Maximum number of characters or byte used for a frame identifier (name or base_frame).
     */
    constexpr std::uint32_t frame_data_max_string_size = 128;

    /**
     * @brief Uniquely identifies a frame.
     */
    struct FrameData
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
    class Framed
    {
    public:
        using FramedGeometricObject = QuantityT;

        /**
         * @brief Default constructs a framed geometric object.
         */
        Framed() : Framed(QuantityT::zero(), {.name = "::", .base_frame = "::"})
        {
            ;
        }

        /**
         * @brief Constructs a framed geometric object given a geometric object and a frame header
         * consisting of a base frame and name.
         *
         * @param object_to_frame Geometric object to frame.
         * @param frame_data Frame header.
         */
        Framed(QuantityT const& object_to_frame, FrameData const& frame_data) :
            _framed_object{object_to_frame}
        {
            // NOLINTBEGIN(cppcoreguidelines-pro-type-vararg)
            std::snprintf(_name_data.data(), _name_data.size(), "%s", frame_data.name.data());
            std::snprintf(_base_frame_data.data(),
                          _base_frame_data.size(),
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
        template <typename StateType>
            requires traits::difference<QuantityT> and traits::state<StateType>
        traits::framed_type_of<StateType>
        enframe(StateType const& object_to_frame) const
        {
            return enframe(object_to_frame, "");
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
            requires traits::difference<QuantityT>
        traits::framed_type_of<Type>
        enframe(Type const& object_to_frame, std::string_view name) const
        {
            return traits::framed_type_of<Type>(object_to_frame,
                                                {.name = name, .base_frame = get_name()});
        }

        std::string_view
        get_name() const
        {
            return _name_data.data();
        }

        std::string_view
        get_base_frame() const
        {
            return _base_frame_data.data();
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

    private:
        /**
         * @brief Name of the held geometric object.
         */
        std::array<char, frame_data_max_string_size> _name_data;

        /**
         * @brief Name of the base frame of the held geometric object.
         */
        std::array<char, frame_data_max_string_size> _base_frame_data;

        /**
         * @brief Framed geometric object.
         */
        QuantityT _framed_object;
    };

    /**
     * @brief Three-way comparison operator of framed types.
     *
     * @param lhs
     * @param rhs
     * @return
     */
    template <typename StateType>
        requires traits::scalar_state<StateType> or traits::scalar_difference<StateType>
    std::strong_ordering
    operator<=>(Framed<StateType> const& lhs, Framed<StateType> const& rhs)
    {
        return lhs.get_framed_object() <=> rhs.get_framed_object();
    }

    /**
     * @brief State difference operator.
     *
     * @param lhs
     * @param rhs
     * @return
     */
    template <typename StateType>
        requires traits::state<StateType>
    traits::framed_type_of<traits::difference_type_of<StateType>>
    operator-(Framed<StateType> const& lhs, Framed<StateType> const& rhs)
    {
        // TODO: Custom exception etc.
        assert(lhs.get_base_frame() == rhs.get_base_frame());

        return traits::framed_type_of<traits::difference_type_of<StateType>>(
            lhs.get_framed_object() - rhs.get_framed_object(),
            {.name = lhs.get_name(), .base_frame = rhs.get_base_frame()});
    }

    /**
     * @brief Translation application operator.
     *
     * This operator drops the framed domain, since no framed guarantees can be enforced.  Use a
     * framed difference instead if you want frame checks to be preformed.
     *
     * @param lhs
     * @param rhs
     * @return
     */
    template <typename DifferenceType, typename FramedStateType>
        requires traits::scalar_difference<DifferenceType> and
                 traits::framed_scalar_state<FramedStateType>
    typename FramedStateType::FramedGeometricObject
    operator+(DifferenceType const& lhs, FramedStateType const& rhs)
    {
        return lhs + rhs.get_framed_object();
    }

    /**
     * @brief Translation application operator.
     *
     * @param lhs
     * @param rhs
     * @return
     */
    template <typename FramedDifferenceType, typename FramedStateType>
        requires traits::framed_scalar_difference<FramedDifferenceType> and
                 traits::framed_scalar_state<FramedStateType> and
                 traits::same_framed_domain<FramedDifferenceType, FramedStateType>
    FramedStateType
    operator+(FramedDifferenceType const& lhs, FramedStateType const& rhs)
    {
        using StateType = typename FramedStateType::FramedGeometricObject;

        // TODO: Custom exception etc.
        assert(lhs.get_base_frame() == rhs.get_base_frame());

        return traits::framed_type_of<StateType>(lhs.get_framed_object() + rhs.get_framed_object(),
                                                 {.name = "", .base_frame = lhs.get_base_frame()});
    }

}  // namespace quant::framed_geometry
