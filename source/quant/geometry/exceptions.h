#pragma once


#include <string>


namespace simox::core::position
{

    class FrameMismatch : public std::runtime_error
    {
    public:
        FrameMismatch(const std::string& msg) : std::runtime_error(msg)
        {
            ;
        }
    };

} // namespace simox::core::position
