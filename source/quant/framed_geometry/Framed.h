#pragma once

#include <quant/framed_geometry_fwd.h>
#include <quant/geometry/Difference.h>

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
     * @brief Template meta programming utility to define the framed type of a type via template
     * specialization.
     *
     * Default is a `Framed<Quantity>`, but the built-in units usually have `FramedQuantity`
     * specialization with convenience APIs, defined operators, etc.
     *
     * Example: `FramedLinearDisplacement` is a specialized `Framed<LinearDisplacement>`.
     */
    template <typename Quantity>
    struct DefineFramedType
    {
        using FramedType = Framed<Quantity>;
    };

    /**
     * @brief Lookup type def for semantic template resolution.
     */
    template <typename Quantity>
    using FramedTypeOf = typename DefineFramedType<Quantity>::FramedType;

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
            framedObject_{objectToFrame}
        {
            // TODO(dreher): Ensure that names are not too long.

            // snprintf guarantees null-termination (not the case for frameName.copy()).
            // NOLINTBEGIN(cppcoreguidelines-pro-type-vararg)
            std::snprintf(nameData_.data(), nameData_.size(), "%s", frameData.name.data());
            std::snprintf(
                baseFrameData_.data(), baseFrameData_.size(), "%s", frameData.baseFrame.data());
            // NOLINTEND(cppcoreguidelines-pro-type-vararg)

            name = nameData_.data();
            baseFrame = baseFrameData_.data();
        }

        FramedTypeOf<QuantityT>
        enframe(QuantityT const& objectToFrame, std::string_view name) const
        {
            return FramedTypeOf<QuantityT>(objectToFrame, {.name = name, .baseFrame = this->name});
        }

        FramedTypeOf<DifferenceTypeOf<QuantityT>>
        operator-(Framed<QuantityT> const& rhs) const
        {
            class Accessor : public QuantityT
            {
            public:
                using QuantityT::VectorQuantity;
            };

            Eigen::Vector3d res = framedObject_.representation_ - rhs.framedObject_.representation_;

            // QuantityT quantity = Accessor(res);

            assert(baseFrame == rhs.baseFrame);
            return FramedTypeOf<DifferenceTypeOf<QuantityT>>(DifferenceTypeOf<QuantityT>(),
                                                             {.name = name, .baseFrame = rhs.name});
        }

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

        QuantityT framedObject_;
    };

}  // namespace quant::framed_geometry

namespace quant
{

    using framed_geometry::Framed;
    using framed_geometry::FrameData;

}  // namespace quant
