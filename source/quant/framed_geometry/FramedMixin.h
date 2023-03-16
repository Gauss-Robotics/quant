#pragma once


#include <string>

#include <simox/core/length/frame/FrameID.h>


namespace simox::core::position::frame
{

    struct FramedMixin
    {
        const FrameID baseFrame;

    protected:
        std::string
        strTemplate() const
        {
            return "in base frame '" + baseFrame.str() + "'";
        }
    };

} // namespace simox::core::position::frame
