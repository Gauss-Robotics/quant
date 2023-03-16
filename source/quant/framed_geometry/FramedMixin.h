#pragma once


#include <string>

#include <quant/framed_geometry/FrameID.h>


namespace quant::position::frame
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

} // namespace quant::position::frame
