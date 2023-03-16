#pragma once


#include <string>


namespace simox::core::position::frame
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

} // namespace simox::core::position::frame


namespace simox
{
    using core::position::frame::FrameID;

    static const FrameID GlobalFrameID{.agent = "", .frame = "GlobalFrame"};
} // namespace simox
