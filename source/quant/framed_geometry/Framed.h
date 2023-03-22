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

    /**
     * Template meta programming utility to define the framed type of a type via template
     * specialization.
     */
    template <typename Type>
    struct DefineFramedType
    {
        using FramedType = Framed<Type>;
    };

    template <typename T>
    Framed<typename T::QuantityDifferenceType> operator-(Framed<T> const& lhs,
                                                         Framed<T> const& rhs);

    /**
     * @brief Wrapper to associate a named geometric object with a base frame.
     */
    template <typename T>
    class Framed
    {
    public:
        Framed(T const& objectToFrame, Frame const& frameData) : framedObject_{objectToFrame}
        {
            // TODO(dreher): Ensure that names are not too long.

            // snprintf guarantees null-termination (not the case for frameName.copy()).
            std::snprintf(nameData_.data(), nameData_.size(), "%s", frameData.name.data());
            name = nameData_.data();

            std::snprintf(
                baseFrameData_.data(), baseFrameData_.size(), "%s", frameData.baseFrame.data());
            baseFrame = baseFrameData_.data();
        }

        typename DefineFramedType<T>::FramedType
        enframe(T const& objectToFrame, std::string_view name) const
        {
            using FramedT = typename DefineFramedType<T>::FramedType;
            return FramedT(objectToFrame, {.name = name, .baseFrame = this->name});
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
            lhs.framedObject_ - rhs.framedObject_, {.name = lhs.name, .baseFrame = rhs.name});
    }

}  // namespace quant

namespace quant
{

    using framed_geometry::Frame;
    using framed_geometry::Framed;

}  // namespace quant
