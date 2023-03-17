#pragma once


#include <string>
#include <sstream>


namespace quant::framed_geometry
{

    template <typename IDType = std::string>
    struct FrameID
    {
        IDType frame;

        std::string
        toString() const
        {
            std::stringstream out;
            out << frame;
            return out.str();
        }

        bool
        operator==(const FrameID& rhs) const
        {
            return frame == rhs.frame;
        }

        bool
        operator!=(const FrameID& rhs) const
        {
            return frame != rhs.frame;
        }
    };


    template <typename T>
    class Framed;


    template <typename T>
    class Frame;


    template <typename T>
    Frame<typename T::QuantityDifferenceType> operator-(
        const Framed<T>& lhs,
        const Framed<T>& rhs);


    template <typename T>
    class Framed : public T
    {
    public:
        Framed(const FrameID<>& baseFrame) :
            baseFrame_{baseFrame},
            T()
        {
            ;
        }


        template <typename T_>
        friend Frame<typename T_::QuantityDifferenceType> operator-(
            const Framed<T_>& lhs,
            const Framed<T_>& rhs);


    protected:
        std::string
        strTemplate() const
        {
            return "in base frame '" + baseFrame_.toString() + "'";
        }

        const FrameID<> baseFrame_;
    };


    template <typename T>
    class Frame : public T
    {
    public:
        const FrameID<> frame_;
        const FrameID<> baseFrame_;

        Frame(
                const FrameID<>& frame,
                const FrameID<>& baseFrame
        ) :
            frame_{frame},
            baseFrame_{baseFrame},
            T()
        {
            ;
        }

    protected:
        std::string
        strTemplate() const
        {
            return "of frame '" + frame_.toString() + "' with respect to base frame '" +
                   baseFrame_.toString() + "'";
        }
    };

} // namespace quant::position::frame


namespace quant
{

    template <typename T>
    framed_geometry::Frame<typename T::QuantityDifferenceType>
    framed_geometry::operator-(
    const Framed<T>& lhs,
    const Framed<T>& rhs)
    {
        FrameID<> baseFrame;
        FrameID<> frame;
        return Frame<typename T::QuantityDifferenceType>(frame, baseFrame);
    }

} // namespace quant


namespace quant
{

    using framed_geometry::FrameID;
    using framed_geometry::Framed;
    using framed_geometry::Frame;

}
