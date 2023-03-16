#pragma once


#include <cstdint>
#include <ostream>
#include <string>

#include <quant/core/time/Duration.h>


namespace quant::units::mass
{

    class Mass
    {

    public:
        Mass();

        static Mass MilliGram(std::int64_t);

        static Mass Gram(std::int64_t);

        static Mass KiloGram(std::int64_t);

        std::string toString() const;

        std::int64_t toMicroGram() const;

        // Operators.
    public:
    private:
        Mass(std::int64_t microGram);

        std::int64_t microGram_;
    };


    std::ostream& operator<<(std::ostream& out, const Mass& rhs);

} // namespace quant::units::mass


namespace quant
{
    using core::units::mass::Mass;
} // namespace quant
