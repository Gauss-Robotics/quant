#pragma once

#include <quant/units/time/Duration.h>

#include <cstdint>
#include <ostream>
#include <string>

namespace quant::units::mass
{

    class Mass
    {

    public:
        Mass();

        static Mass milliGram(std::int64_t);

        static Mass gram(std::int64_t);

        static Mass kiloGram(std::int64_t);

        std::string
        toString() const;

        std::int64_t
        toMicroGram() const;

        // Operators.

    private:
        Mass(std::int64_t microGram);

        std::int64_t microGram_;
    };

    std::ostream&
    operator<<(std::ostream& out, Mass const& rhs);

}  // namespace quant::units::mass
