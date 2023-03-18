#pragma once


#include <array>
#include <cstdio>
#include <ostream>
#include <string_view>


namespace quant::framed_geometry
{

    constexpr std::uint32_t MAX_FRAME_SIZE = 128;


    /**
     * @brief An object of this class uniquely identifies a frame.
     */
    struct FrameID
    {

        FrameID(std::string_view frameName)
        {
            // snprintf guarantees null-termination (not the case for frameName.copy()).
            std::snprintf(frameData_.data(), frameData_.size(), "%s", frameName.data());
            name = frameData_.data();
        }

        bool
        operator==(std::string_view rhs) const
        {
            return name == rhs;
        }

        bool
        operator==(const FrameID& rhs) const
        {
            return name == rhs.name;
        }

        bool
        operator!=(std::string_view rhs) const
        {
            return name != rhs;
        }

        bool
        operator!=(const FrameID& rhs) const
        {
            return name != rhs.name;
        }

    private:
        /**
         * @brief This member holds the actual data of the frame name, which is just referenced
         * by frame.
         */
        std::array<char, MAX_FRAME_SIZE> frameData_;

    public:
        std::string_view name;
    };


    template <typename T>
    class Framed;


    template <typename T>
    class Frame;


    template <typename T>
    Frame<typename T::QuantityDifferenceType> operator-(
        const Framed<T>& lhs,
        const Framed<T>& rhs);


    /**
     * @brief Wrapper to associate a quantity with a base frame.
     */
    template <typename T>
    class Framed : public T
    {
    public:
        Framed(const FrameID& baseFrame) :
            baseFrame{baseFrame},
            T()
        {
            ;
        }


        template <typename T_>
        friend Frame<typename T_::QuantityDifferenceType> operator-(
            const Framed<T_>& lhs,
            const Framed<T_>& rhs);

        const FrameID baseFrame;

    protected:
        std::string
        strTemplate() const
        {
            return "in base frame '" + std::string(baseFrame.name) + "'";
        }

    };


    /**
     * @brief Wrapper to associate an operation to a frame with a base frame.
     */
    template <typename T>
    class Frame : public T
    {
    public:
        const FrameID frame;
        const FrameID baseFrame;

        Frame(
                const FrameID& frame,
                const FrameID& baseFrame
        ) :
            frame{frame},
            baseFrame{baseFrame},
            T()
        {
            ;
        }

    protected:
        std::string
        strTemplate() const
        {
            return "of frame '" + std::string(frame.name) + "' with respect to base frame '" +
                   std::string(baseFrame.name) + "'";
        }
    };


    std::ostream& operator<<(std::ostream& out, const FrameID& rhs)
    {
        out << "<FrameID frame=" << rhs.name << ">";
        return out;
    }

} // namespace quant::position::frame


namespace quant
{

    template <typename T>
    framed_geometry::Frame<typename T::QuantityDifferenceType>
    framed_geometry::operator-(
    const Framed<T>& lhs,
    const Framed<T>& rhs)
    {
        FrameID baseFrame{""};
        FrameID frame{""};
        return Frame<typename T::QuantityDifferenceType>(frame, baseFrame);
    }

} // namespace quant


namespace quant
{

    using framed_geometry::FrameID;
    using framed_geometry::Framed;
    using framed_geometry::Frame;

}
