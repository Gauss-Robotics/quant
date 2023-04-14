#pragma once

#include <quant/framed_geometry_fwd.h>
#include <quant/geometry/Difference.h>
#include <quant/geometry/LinearDifference.h>
#include <quant/geometry_fwd.h>

#include <Eigen/Core>

#include <array>
#include <cassert>
#include <cstdio>
#include <ostream>
#include <string_view>

namespace quant::framed_geometry
{

    /**
     * @brief Maximum number of characters used for a frame identifier (name or base_frame).
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
     * On construction, the name and baseFrame strings referred to the string_views in a `Frame` are
     * copied into own internal private members (`_name_data` and `_base_frame_data`) on the stack
     * with a maximum number of chars defined in `frame_data_max_string_size`. The names can be
     * accessed using the public string_views `name` and `base_frame`.
     */
    template <typename QuantityT>
    class Framed
    {
    public:
        Framed(QuantityT const& object_to_frame, FrameData const& frame_data) :
            name{[&]() -> char const*
                 {
                     // NOLINTBEGIN(cppcoreguidelines-pro-type-vararg)
                     std::snprintf(
                         _name_data.data(), _name_data.size(), "%s", frame_data.name.data());
                     // NOLINTEND(cppcoreguidelines-pro-type-vararg)
                     return _name_data.data();
                 }()},
            base_frame{[&]() -> char const*
                       {
                           // NOLINTBEGIN(cppcoreguidelines-pro-type-vararg)
                           std::snprintf(_base_frame_data.data(),
                                         _base_frame_data.size(),
                                         "%s",
                                         frame_data.base_frame.data());
                           // NOLINTEND(cppcoreguidelines-pro-type-vararg)
                           return _base_frame_data.data();
                       }()},
            _framed_object{object_to_frame}
        {
            ;
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
        std::enable_if_t<traits::is_difference<QuantityT>, traits::FramedTypeOf<Type>>
        enframe(Type const& object_to_frame, std::string_view name) const
        {
            return traits::FramedTypeOf<Type>(object_to_frame,
                                              {.name = name, .base_frame = this->name});
        }

        traits::FramedTypeOf<traits::DifferenceTypeOf<QuantityT>>
        operator-(Framed<QuantityT> const& rhs) const
        {
            assert(base_frame == rhs.base_frame);
            return traits::FramedTypeOf<traits::DifferenceTypeOf<QuantityT>>(
                traits::DifferenceTypeOf<QuantityT>(), {.name = name, .base_frame = rhs.name});
        }

        Framed<QuantityT>&
        operator=(Framed<QuantityT> const& t)
        {
            return *this;
        }

        const std::string_view name;
        const std::string_view base_frame;

    private:
        /**
         * @brief This member holds the actual data of `name`.
         */
        std::array<char, frame_data_max_string_size> _name_data;

        /**
         * @brief This member holds the actual data of `baseFrame`.
         */
        std::array<char, frame_data_max_string_size> _base_frame_data;

        QuantityT _framed_object;
    };

}  // namespace quant::framed_geometry
