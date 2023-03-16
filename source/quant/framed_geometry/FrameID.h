#pragma once


#include <string>


namespace quant::position::frame
{

    struct FrameID
    {
        std::string agent = "";
        std::string frame;

        std::string
        str() const
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

} // namespace quant::position::frame


namespace quant
{
    using position::frame::FrameID;

    static const FrameID GlobalFrameID{.agent = "", .frame = "GlobalFrame"};
} // namespace quant
