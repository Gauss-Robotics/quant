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
            return agent == rhs.agent and frame == rhs.frame;
        }

        bool
        operator!=(const FrameID& rhs) const
        {
            return agent != rhs.agent or frame != rhs.frame;
        }
    };


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
    struct FrameMixin
    {
        const FrameID frame;
        const FrameID baseFrame;

    protected:
        std::string
        strTemplate() const
        {
            return "of frame '" + frame.toString() + "' with respect to base frame '" +
                   baseFrame.toString() + "'";
        }
    };

} // namespace quant::position::frame


namespace quant
{

    using framed_geometry::FrameID;
    using framed_geometry::Framed;

}
