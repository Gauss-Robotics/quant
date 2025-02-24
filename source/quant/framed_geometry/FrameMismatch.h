#pragma once
#include <stdexcept>

namespace quant::framed_geometry
{
    class FrameMismatchException : public std::runtime_error
    {
    public:
    FrameMismatchException(const std::string_view& frame1, const std::string_view& frame2)
        : std::runtime_error("Frame mismatch: " + std::string(frame1) + " vs " + std::string(frame2))
        {
        }
    };
}