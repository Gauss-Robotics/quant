#pragma once


#include <string>


namespace quant::framed_geometry
{

    struct FrameID
    {
        std::string agent = "";
        std::string frame;

        std::string
        toString() const
        {
            return agent + "::" + frame;
        }

        bool
        operator==(const FrameID& rhs) const
        {
            // It is more efficient to test for the frame names first, since it is less likely for
            // the user to erroneously compare frames of two different robots.
            return frame == rhs.frame and agent == rhs.agent;
        }

        bool
        operator!=(const FrameID& rhs) const
        {
            // It is more efficient to test for the frame names first, since it is less likely for
            // the user to erroneously compare frames of two different robots.
            return frame != rhs.frame or agent != rhs.agent;
        }
    };


    template <typename T>
    class Framed;


    template <typename T>
    class Frame;


    template <typename T, typename DifferenceType>
    Frame<DifferenceType> operator-(const Framed<T>& lhs,
                                    const Framed<T>& rhs);


    template <typename T>
    class Framed : public T
    {
    public:
        Framed(const FrameID& baseFrame) :
            baseFrame_{baseFrame},
            T()
        {
            ;
        }


        template <typename T_, typename DifferenceType_>
        friend Frame<DifferenceType_> operator-(const Framed<T_>& lhs,
                                                const Framed<T_>& rhs);


    protected:
        std::string
        strTemplate() const
        {
            return "in base frame '" + baseFrame_.toString() + "'";
        }

        const FrameID baseFrame_;
    };


    /**
     * @brief The FrameMixin struct
     */
    template <typename T>
    class Frame
    {
    public:
        const FrameID frame_;
        const FrameID baseFrame_;

        Frame(const FrameID& frame,
              const FrameID& baseFrame) :
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

    template <typename T, typename DifferenceType>
    framed_geometry::Frame<DifferenceType>
    framed_geometry::operator-(const framed_geometry::Framed<T>& lhs,
                               const framed_geometry::Framed<T>& rhs)
    {

        return framed_geometry::Frame();
    }

} // namespace quant


namespace quant
{

    using framed_geometry::FrameID;
    using framed_geometry::Framed;

}
