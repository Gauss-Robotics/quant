#pragma once


#include <string>

#include <simox/core/length/frame/FrameID.h>


namespace simox::core::position::frame
{

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
            return "of frame '" + frame.str() + "' with respect to base frame '" + baseFrame.str() +
                   "'";
        }
    };

} // namespace simox::core::position::frame
