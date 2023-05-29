#pragma once

#include <quant/framed_geometry_fwd.h>
#include <quant/geometry/Difference.h>
#include <quant/geometry_fwd.h>

#include <Eigen/Core>

#include <array>
#include <cassert>
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
        std::string_view name;
        std::string_view base_frame;
    };

    /**
     * @brief Wrapper to associate a named geometric object with a base frame.
     *
     * On construction, the name and base frame strings referred to the string_views in a `Frame`
     * are copied into own internal private members (`_name_data` and `_base_frame_data`) on the
     * stack with a maximum number of chars defined in `frame_data_max_string_size`. The names can
     * be accessed using the accessors `name()` and `base_frame()`.
     */
    template <typename QuantityT>
    class Framed
    {
    public:
        Framed() : Framed(QuantityT::zero(), {.name = "::", .base_frame = "::"})
        {
            ;
        }

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
         * @brief Enframe a geometric object in this framed object.
         *
         * Allows to easily construct a framed geometric object by enframing it in this object.
         *
         * @param object_to_frame Object that should be framed in this object.
         * @param name Name of the object.
         *
         * @return Framed type of object_to_frame.
         */
        template <typename Type>
            requires traits::difference<QuantityT>
        traits::framed_type_of<Type>
        enframe(Type const& object_to_frame, std::string_view name) const
        {
            return traits::framed_type_of<Type>(object_to_frame,
                                                {.name = name, .base_frame = this->name()});
        }

        Framed<QuantityT>&
        operator=(Framed<QuantityT> const& t)
        {
            _name_data = t._name_data;
            _base_frame_data = t._base_frame_data;
            _framed_object = t._framed_object;
            return *this;
        }

        std::string_view
        name() const
        {
            return _name_data.data();
        }

        std::string_view
        base_frame() const
        {
            return _base_frame_data.data();
        }

        std::string
        to_string() const
        {
            std::string named_entity{name()};
            named_entity += " ";
            std::string in_frame{base_frame()};  // base frame might be empty for global frame.
            if (not in_frame.empty())
            {
                in_frame = " in frame " + in_frame;
            }
            return named_entity + _framed_object.to_string() + in_frame;
        }

    private:
        /**
         * @brief The name of the held geometric object.
         */
        std::array<char, frame_data_max_string_size> _name_data;

        /**
         * @brief The name of the base frame of the held geometric object.
         */
        std::array<char, frame_data_max_string_size> _base_frame_data;

        QuantityT _framed_object;
    };

    template <typename StateType>
        requires traits::state<StateType>
    traits::framed_type_of<traits::difference_type_of<StateType>>
    operator-(Framed<StateType> const& lhs, Framed<StateType> const& rhs)
    {
        assert(lhs.base_frame() == rhs.base_frame());
        return traits::framed_type_of<traits::difference_type_of<StateType>>(
            traits::difference_type_of<StateType>(),
            {.name = lhs.name(), .base_frame = rhs.name()});
    }

}  // namespace quant::framed_geometry
