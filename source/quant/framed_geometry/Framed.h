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
    constexpr std::uint32_t frameDataMaxStringSize = 128;

    /**
     * @brief Uniquely identifies a frame.
     */
    struct FrameData
    {
        std::string_view name;
        std::string_view baseFrame;
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
        Framed(QuantityT const& objectToFrame, FrameData const& frameData) :
            name{[&]() -> char const*
                 {
                     // NOLINTBEGIN(cppcoreguidelines-pro-type-vararg)
                     std::snprintf(nameData_.data(), nameData_.size(), "%s", frameData.name.data());
                     // NOLINTEND(cppcoreguidelines-pro-type-vararg)
                     return nameData_.data();
                 }()},
            baseFrame{[&]() -> char const*
                      {
                          // NOLINTBEGIN(cppcoreguidelines-pro-type-vararg)
                          std::snprintf(baseFrameData_.data(),
                                        baseFrameData_.size(),
                                        "%s",
                                        frameData.baseFrame.data());
                          // NOLINTEND(cppcoreguidelines-pro-type-vararg)

                          return baseFrameData_.data();
                      }()},
            framedObject_{objectToFrame}
        {
            ;
        }

        traits::FramedTypeOf<QuantityT>
        enframe(QuantityT const& objectToFrame, std::string_view name) const
        {
            return traits::FramedTypeOf<QuantityT>(objectToFrame,
                                                   {.name = name, .baseFrame = this->name});
        }

        traits::FramedTypeOf<geometry::DifferenceTypeOf<QuantityT>>
        operator-(Framed<QuantityT> const& rhs) const
        {
            assert(baseFrame == rhs.baseFrame);
            return traits::FramedTypeOf<geometry::DifferenceTypeOf<QuantityT>>(
                geometry::DifferenceTypeOf<QuantityT>(), {.name = name, .baseFrame = rhs.name});
        }

        const std::string_view name;
        const std::string_view baseFrame;

    private:
        /**
         * @brief This member holds the actual data of `name`.
         */
        std::array<char, frameDataMaxStringSize> nameData_;

        /**
         * @brief This member holds the actual data of `baseFrame`.
         */
        std::array<char, frameDataMaxStringSize> baseFrameData_;

        QuantityT framedObject_;
    };

}  // namespace quant::framed_geometry
