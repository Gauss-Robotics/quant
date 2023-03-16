#pragma once


#include <string>

#include <quant/framed_geometry/FrameID.h>


namespace quant::position::frame
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

} // namespace quant::position::frame
