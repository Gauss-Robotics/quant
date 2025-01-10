#include <stdexcept>
#include <string>

namespace quant::framed_geometry
{

    class FrameMismatch : public std::runtime_error
    {
    public:
        FrameMismatch(std::string const& message) : std::runtime_error("Frame mismatch: " + message)
        {
        }
    };

}  // namespace quant::framed_geometry