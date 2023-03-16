#pragma once


#include <string>


namespace quant::position
{

    class FrameMismatch : public std::runtime_error
    {
    public:
        FrameMismatch(const std::string& msg) : std::runtime_error(msg)
        {
            ;
        }
    };

} // namespace quant::position
