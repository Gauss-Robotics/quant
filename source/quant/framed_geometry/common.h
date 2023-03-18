#pragma once


#include <array>
#include <cassert>
#include <cstdio>
#include <ostream>
#include <string_view>

namespace quant::framed_geometry
{

    constexpr std::uint32_t frameDataMaxStringSize = 128;

    struct Frame
    {
        std::string_view name;
        std::string_view baseFrame;
    };


    template <typename T>
    class Framed;


    template <typename T>
    Framed<typename T::QuantityDifferenceType> operator-(Framed<T> const& lhs,
                                                         Framed<T> const& rhs);

    /**
     * @brief Wrapper to associate a quantity with a base frame.
     */
    template <typename T>
    class Framed
    {
    public:
        Framed(Frame const& frameData)
        {
            // snprintf guarantees null-termination (not the case for frameName.copy()).
            std::snprintf(nameData_.data(), nameData_.size(), "%s", frameData.name.data());
            name = frameData.name.data();

            std::snprintf(
                baseFrameData_.data(), baseFrameData_.size(), "%s", frameData.baseFrame.data());
            baseFrame = baseFrameData_.data();
        }

        template <typename T_>
        friend Framed<typename T_::QuantityDifferenceType> operator-(Framed<T_> const& lhs,
                                                                     Framed<T_> const& rhs);

        std::string_view name;
        std::string_view baseFrame;

    private:
        /**
         * @brief This member holds the actual data of `name`.
         */
        std::array<char, frameDataMaxStringSize> nameData_;

        /**
         * @brief This member holds the actual data of `baseFrame`.
         */
        std::array<char, frameDataMaxStringSize> baseFrameData_;

        T framedObject_;
    };

}  // namespace quant::framed_geometry

namespace quant
{

    template <typename T>
    framed_geometry::Framed<typename T::QuantityDifferenceType>
    framed_geometry::operator-(Framed<T> const& lhs, Framed<T> const& rhs)
    {
        // TODO(dreher): Exceptions and no-excpt alternative.
        assert(lhs.baseFrame == rhs.baseFrame);
        return Framed<typename T::QuantityDifferenceType>(
            {.name = lhs.name, .baseFrame = rhs.name});
    }

}  // namespace quant

namespace quant
{

    using framed_geometry::Frame;
    using framed_geometry::Framed;

}  // namespace quant
