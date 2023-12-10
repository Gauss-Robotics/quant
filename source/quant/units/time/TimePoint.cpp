#include "TimePoint.h"

#include <quant/units/Scalar.h>

#include <boost/algorithm/string/replace.hpp>

#include <iomanip>
#include <sstream>

namespace quant::units::time
{

    std::string
    TimePoint::to_string(std::string const& format) const
    {
        constexpr std::size_t string_buffer_size = 32;

        std::int64_t const usec = _representation;
        std::int64_t const usec_remainder = usec % 1'000'000;
        std::int64_t const msec_remainder = static_cast<std::int64_t>(
            (static_cast<double>(usec_remainder) * constants::us2ms) + 0.5);
        time_t const time = static_cast<time_t>(static_cast<double>(usec) / 1'000'000);

        struct tm tr;
        localtime_r(&time, &tr);

        char buf[string_buffer_size];
        if (strftime(buf, sizeof(buf), format.c_str(), &tr) == 0)
        {
            return "";
        }
        std::string postformat = buf;

        {
            std::stringstream msec_ss;
            msec_ss << std::setw(3) << std::setfill('0') << msec_remainder;
            postformat = boost::replace_all_copy(postformat, "%msec", msec_ss.str());
        }
        {
            std::stringstream usec_ss;
            usec_ss << std::setw(6) << std::setfill('0') << usec_remainder;
            postformat = boost::replace_all_copy(postformat, "%usec", usec_ss.str());
        }

        return postformat;
    }

}  // namespace quant::units::time
