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
     * @brief Maximum number of characters used for a frame identifier (name or baseFrame).
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
     * copied into own internal private members (`nameData_` and `baseFrameData_`) on the stack with
     * a maximum number of chars defined in `frameDataMaxStringSize`. The names can be accessed
     * using the public string_views `name` and `baseFrame`.
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
                         name_data_.data(), name_data_.size(), "%s", frame_data.name.data());
                     // NOLINTEND(cppcoreguidelines-pro-type-vararg)
                     return name_data_.data();
                 }()},
            base_frame{[&]() -> char const*
                       {
                           // NOLINTBEGIN(cppcoreguidelines-pro-type-vararg)
                           std::snprintf(base_frame_data_.data(),
                                         base_frame_data_.size(),
                                         "%s",
                                         frame_data.base_frame.data());
                           // NOLINTEND(cppcoreguidelines-pro-type-vararg)

                           return base_frame_data_.data();
                       }()},
            framed_object_{object_to_frame}
        {
            ;
        }

        traits::FramedTypeOf<QuantityT>
        enframe(QuantityT const& object_to_frame, std::string_view name) const
        {
            return traits::FramedTypeOf<QuantityT>(object_to_frame,
                                                   {.name = name, .base_frame = this->name});
        }

        traits::FramedTypeOf<traits::DifferenceTypeOf<QuantityT>>
        operator-(Framed<QuantityT> const& rhs) const
        {
            assert(base_frame == rhs.base_frame);
            return traits::FramedTypeOf<traits::DifferenceTypeOf<QuantityT>>(
                traits::DifferenceTypeOf<QuantityT>(), {.name = name, .base_frame = rhs.name});
        }

        const std::string_view name;
        const std::string_view base_frame;

    private:
        /**
         * @brief This member holds the actual data of `name`.
         */
        std::array<char, frame_data_max_string_size> name_data_;

        /**
         * @brief This member holds the actual data of `baseFrame`.
         */
        std::array<char, frame_data_max_string_size> base_frame_data_;

        QuantityT framed_object_;
    };

}  // namespace quant::framed_geometry
