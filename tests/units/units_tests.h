#pragma once

#include <quant/geometry.h>
#include <quant/geometry/Circa.h>
#include <quant/units.h>

#include <doctest/doctest.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <iostream>
#include <numbers>

using namespace quant;  // NOLINT

// NOLINTBEGIN(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)

TEST_SUITE("angle")
{
    TEST_CASE("angles can be trivially constructed")
    {
        Angle const angle;
        CHECK(angle == Angle::radians(0));

        Angle const angle_zero;
        CHECK(angle == Angle::zero());
    }

    TEST_CASE("angles can be converted to other units")
    {
        CHECK(Angle::radians(0).to_degrees() == 0);
        CHECK(Angle::radians(std::numbers::pi).to_degrees() == 180);
        CHECK(Angle::degrees(360).to_radians() == 2 * std::numbers::pi);
    }
}

TEST_SUITE("time")
{
    TEST_CASE("time points can be trivially constructed")
    {
        TimePoint const t_default;
        CHECK(t_default == TimePoint::microseconds(0));

        TimePoint const t_zero = TimePoint::zero();
        CHECK(t_zero == TimePoint::microseconds(0));
    }

    TEST_CASE("time points can be converted to other units")
    {
        CHECK(TimePoint::microseconds(100).to_microseconds() == 100);
        CHECK(TimePoint::milliseconds(100).to_microseconds() == 100'000);
        CHECK(TimePoint::seconds(100).to_microseconds() == 100'000'000);
        CHECK(TimePoint::minutes(100).to_microseconds() == 6'000'000'000);
        CHECK(TimePoint::hours(100).to_microseconds() == 360'000'000'000);
        CHECK(TimePoint::days(100).to_microseconds() == 8'640'000'000'000);
        CHECK(TimePoint::microseconds(100'000).to_milliseconds() == 100);
        CHECK(TimePoint::microseconds(100'000'000).to_seconds() == 100);
        CHECK(TimePoint::microseconds(6'000'000'000).to_minutes() == 100);
        CHECK(TimePoint::microseconds(360'000'000'000).to_hours() == 100);
        CHECK(TimePoint::microseconds(8'640'000'000'000).to_days() == 100);
    }

    TEST_CASE("time points can be converted to string")
    {
        TimePoint const t = TimePoint::milliseconds(0.312);

        // String to automatic unit.
        CHECK(t.to_string() == "312 µs");

        SUBCASE("time point can be streamed as automatic unit")
        {
            std::stringstream ss;
            ss << t;

            CHECK(ss.str() == "312 µs");
        }

        // String in specific unit.
        CHECK(t.to_milliseconds().to_string() == "0.312 ms");

        SUBCASE("time point can be streamed as specific unit")
        {
            std::stringstream ss;
            ss << t.to_milliseconds();

            CHECK(ss.str() == "0.312 ms");
        }
    }

    TEST_CASE("durations can be trivially constructed")
    {
        Duration const d_default;
        CHECK(d_default == Duration::microseconds(0));

        Duration const d_zero = Duration::zero();
        CHECK(d_zero == Duration::microseconds(0));
    }

    TEST_CASE("durations can be converted to other units")
    {
        CHECK(Duration::microseconds(100).to_microseconds() == 100);
        CHECK(Duration::milliseconds(100).to_microseconds() == 100'000);
        CHECK(Duration::seconds(100).to_microseconds() == 100'000'000);
        CHECK(Duration::minutes(100).to_microseconds() == 6'000'000'000);
        CHECK(Duration::hours(100).to_microseconds() == 360'000'000'000);
        CHECK(Duration::days(100).to_microseconds() == 8'640'000'000'000);
        CHECK(Duration::microseconds(100'000).to_milliseconds() == 100);
        CHECK(Duration::microseconds(100'000'000).to_seconds() == 100);
        CHECK(Duration::microseconds(6'000'000'000).to_minutes() == 100);
        CHECK(Duration::microseconds(360'000'000'000).to_hours() == 100);
        CHECK(Duration::microseconds(8'640'000'000'000).to_days() == 100);
    }

    TEST_CASE("durations can be converted to string")
    {
        Duration const t = Duration::milliseconds(0.312);

        // String to automatic unit.
        CHECK(t.to_string() == "312 µs");

        SUBCASE("durations can be streamed as automatic unit")
        {
            std::stringstream ss;
            ss << t;

            CHECK(ss.str() == "312 µs");
        }

        // String in specific unit.
        CHECK(t.to_milliseconds().to_string() == "0.312 ms");

        SUBCASE("durations can be streamed as specific unit")
        {
            std::stringstream ss;
            ss << t.to_milliseconds();

            CHECK(ss.str() == "0.312 ms");
        }
    }

    TEST_CASE("duration is the result of a time point difference")
    {
        Duration const d1 = TimePoint::microseconds(1'000) - TimePoint::microseconds(333);
        Duration const d1_target = Duration::microseconds(667);
        CHECK(d1 == d1_target);

        Duration const d2 = TimePoint::seconds(1) - TimePoint::milliseconds(100);
        Duration const d2_target = Duration::milliseconds(900);
        CHECK(d2 == d2_target);
    }

    TEST_CASE("durations can be used to shift time points")
    {
        TimePoint const t1 = Duration::milliseconds(100) + TimePoint::seconds(1);
        TimePoint const t1_target = TimePoint::milliseconds(1'100);
        CHECK(t1 == t1_target);
    }

    TEST_CASE("duration can be added to another duration")
    {
        Duration const d1 = Duration::microseconds(1'000);
        Duration const d2 = Duration::microseconds(200);
        Duration const d3 = d1 + d2;
        CHECK(d3 == Duration::microseconds(1'200));
    }

    TEST_CASE("duration can be subtracted from another duration")
    {
        Duration const d1 = Duration::microseconds(1'000);
        Duration const d2 = Duration::microseconds(200);
        Duration const d3 = d1 - d2;
        CHECK(d3 == Duration::microseconds(800));
    }
}

TEST_SUITE("position")
{
    TEST_CASE("positions can be trivially constructed")
    {
        Position const x_default;
        CHECK(x_default == Position::millimeters({.x = 0, .y = 0, .z = 0}));

        Position const x_zero = Position::zero();
        CHECK(x_zero == Position::millimeters({.x = 0, .y = 0, .z = 0}));
    }

    TEST_CASE("positions can be converted to string")
    {
        Position const x = Position::meters({.x = 0.1, .y = 0.3, .z = 0});

        // String to automatic unit.
        CHECK(x.to_string() == "[100 300 0] mm");

        SUBCASE("positions can be streamed as automatic unit")
        {
            std::stringstream ss;
            ss << x;

            CHECK(ss.str() == "[100 300 0] mm");
        }

        // String in specific unit.
        CHECK(x.to_meters().to_string() == "[0.1 0.3 0] m");

        SUBCASE("positions can be streamed as specific unit")
        {
            std::stringstream ss;
            ss << x.to_meters();

            CHECK(ss.str() == "[0.1 0.3 0] m");
        }
    }

    TEST_CASE("positions can be compared for equality and approximate equality")
    {
        Position const x = Position::millimeters({.x = 100, .y = 200, .z = 300});
        LinearDisplacement const disturbance =
            LinearDisplacement::millimeters({.x = 1e-14, .z = 1e-15});
        Position const x_disturbed = disturbance + x;

        CHECK(x_disturbed != x);
        CHECK(x_disturbed == Circa(x));
        CHECK(x_disturbed.is_approx(x));
    }

    TEST_CASE("positions can be accessed for individiual components and unit symbols")
    {
        Position const x = Position::millimeters({.x = 100, .y = 200, .z = 300});
        CHECK(x.to_millimeters().x == 100);
        CHECK(x.to_millimeters().y == 200);
        CHECK(x.to_millimeters().z == 300);
        CHECK(x.to_millimeters().unit_symbol == "mm");
    }

    TEST_CASE("testing different operations")
    {
        AngularDisplacement const rot = AngularDisplacement::radians(AxisAngle::around_y(M_PI));
        Position const pos1 = Position::millimeters({.y = 100, .z = 200});
        Position const rot_pos = rot * pos1;
        CHECK(rot_pos.to_millimeters().x == Circa(0));
        CHECK(rot_pos.to_millimeters().y == Circa(100));
        CHECK(rot_pos.to_millimeters().z == Circa(-200));

        LinearDisplacement const trans = LinearDisplacement::millimeters({.x = 5, .z = 100});
        Position const trans_pos = trans + pos1;
        CHECK(trans_pos == Position::millimeters({.x = 5, .y = 100, .z = 300}));

        LinearDisplacement const rot_trans = rot * trans;
        CHECK(rot_trans.to_millimeters().x == Circa(-5));
        CHECK(rot_trans.to_millimeters().y == Circa(0));
        CHECK(rot_trans.to_millimeters().z == Circa(-100));

        Position const rot_trans_pos = rot_trans + pos1;
        CHECK(rot_trans_pos.to_millimeters().x == Circa(-5));
        CHECK(rot_trans_pos.to_millimeters().y == Circa(100));
        CHECK(rot_trans_pos.to_millimeters().z == Circa(100));
    }
}

TEST_SUITE("velocity")
{
    TEST_CASE("linear velocities can be trivially constructed")
    {
        LinearVelocity const v_default;
        CHECK(v_default == LinearVelocity::millimeters_per_second({.x = 0, .y = 0, .z = 0}));

        LinearVelocity const v_zero = LinearVelocity::zero();
        CHECK(v_zero == LinearVelocity::millimeters_per_second({.x = 0, .y = 0, .z = 0}));
    }

    TEST_CASE("linear velocities can be converted to string")
    {
        LinearVelocity const v = LinearVelocity::meters_per_second({.x = 0.1, .y = 0.3, .z = 0});

        // String to automatic unit.
        CHECK(v.to_string() == "[100 300 0] mm/s");

        SUBCASE("linear velocities can be streamed as automatic unit")
        {
            std::stringstream ss;
            ss << v;

            CHECK(ss.str() == "[100 300 0] mm/s");
        }

        // String in specific unit.
        CHECK(v.to_meters_per_second().to_string() == "[0.1 0.3 0] m/s");

        SUBCASE("linear velocities can be streamed as specific unit")
        {
            std::stringstream ss;
            ss << v.to_meters_per_second();

            CHECK(ss.str() == "[0.1 0.3 0] m/s");
        }
    }

    TEST_CASE("angular velocities can be constructed from Eigen")
    {
        Eigen::AngleAxisd const rad_per_sec(M_PI / 2, Eigen::Vector3d(1, 0, 1).normalized());
        AngularVelocity const av =
            AngularVelocity::radians_per_second(AxisAngle::from_eigen(rad_per_sec));
        Eigen::AngleAxisd const rad_per_sec_reconstructed = av.to_radians_per_second().to_eigen();

        CHECK(rad_per_sec_reconstructed.isApprox(rad_per_sec));
    }

    TEST_CASE("linear and angular velocities can be combined to a twist")
    {
        Twist const t1 = Twist::zero();
        LinearVelocity const vel1 = LinearVelocity::millimeters_per_second({.y = 100});
        Twist const t2 = LinearVelocityDifference(vel1) + t1;
        CHECK(t2.linear() == vel1);

        AngularVelocity const vel2 = AngularVelocity::radians_per_second({.angle = M_PI});
        Twist const t3 = AngularVelocityDifference(vel2) * t1;
        CHECK(t3.angular() == Circa(vel2));
    }

    TEST_CASE("linear velocity can be constructed from displacements divided by durations")
    {
        // First measurement.
        Position const x1 = Position::millimeters({.z = 100});
        TimePoint const t1 = TimePoint::seconds(15);

        // Second measurement.
        Position const x2 = Position::millimeters({.x = 100, .y = 100, .z = 200});
        TimePoint const t2 = TimePoint::seconds(17);

        // Calculate differences.
        LinearDisplacement const dx = x2 - x1;
        Duration const dt = t2 - t1;

        // Calculate linear velocity.
        LinearVelocity const vel = dx / dt;

        // Check velocity.
        LinearVelocity const vel_target =
            LinearVelocity::millimeters_per_second({.x = 50, .y = 50, .z = 50});
        CHECK(vel == Circa(vel_target));

        SUBCASE("speed can be derived from velocity or calculated from distance and duration")
        {
            Speed const speed_target = vel.to_speed();

            // Calculate distance and speed.
            Distance const dist = dx.to_distance();
            Speed const speed = dist / dt;

            CHECK(dist.to_millimeters() == Circa(173.205));
            CHECK(speed == speed_target);
        }
    }
}

TEST_SUITE("mass")
{
    TEST_CASE("masses can be trivially constructed")
    {
        Mass const m_default;
        CHECK(m_default == Mass::grams(0));

        Mass const m_zero = Mass::zero();
        CHECK(m_zero == Mass::grams(0));
    }

    TEST_CASE("masses can be converted to string")
    {
        Mass const m = Mass::grams(0.312);

        // String to automatic unit.
        CHECK(m.to_string() == "312 mg");

        SUBCASE("masses can be streamed as automatic unit")
        {
            std::stringstream ss;
            ss << m;

            CHECK(ss.str() == "312 mg");
        }

        // String in specific unit.
        CHECK(m.to_grams().to_string() == "0.312 g");

        SUBCASE("masses can be streamed as specific unit")
        {
            std::stringstream ss;
            ss << m.to_grams();

            CHECK(ss.str() == "0.312 g");
        }
    }

    TEST_CASE("basic constructions")
    {
        Mass const m1 = Mass::milligrams(100);
        CHECK(m1.to_milligrams() == Circa(100));

        Mass const m2 = Mass::grams(123);
        CHECK(m2.to_grams() == Circa(123));

        Mass const m3 = Mass::kilograms(321);
        CHECK(m3.to_kilograms() == Circa(321));
    }

    TEST_CASE("unit converting constructions")
    {
        Mass const m1 = Mass::milligrams(1'000);
        CHECK(m1.to_grams() == 1);

        Mass const m2 = Mass::grams(1'234);
        CHECK(m2.to_kilograms() == 1.234);
    }
}

TEST_SUITE("momentum")
{
    TEST_CASE("linear momentums can be trivially constructed")
    {
        LinearMomentum const p_default;
        CHECK(p_default == LinearMomentum::kilogram_meters_per_second({.x = 0, .y = 0, .z = 0}));

        LinearMomentum const p_zero = LinearMomentum::zero();
        CHECK(p_zero == LinearMomentum::kilogram_meters_per_second({.x = 0, .y = 0, .z = 0}));
    }

    TEST_CASE("linear momentums can be converted to string")
    {
        LinearMomentum const p =
            LinearMomentum::kilogram_meters_per_second({.x = 0.1, .y = 0.3, .z = 0});

        // String to automatic unit.
        CHECK(p.to_string() == "[0.1 0.3 0] kg⋅m/s");

        SUBCASE("linear momentums can be streamed as automatic unit")
        {
            std::stringstream ss;
            ss << p;

            CHECK(ss.str() == "[0.1 0.3 0] kg⋅m/s");
        }
    }

    TEST_CASE("basic constructions")
    {
        LinearMomentum const p = LinearMomentum::kilogram_meters_per_second({.x = 2.7});

        CHECK(p == Circa(LinearMomentum::kilogram_meters_per_second({.x = 2.7})));
    }

    TEST_CASE("linear momentum can be constructed from mass times velocity")
    {
        Mass const m = Mass::kilograms(2);
        LinearVelocity const v = LinearVelocity::meters_per_second({.y = 8});

        LinearMomentum const p = m * v;

        LinearMomentum const p_target = LinearMomentum::kilogram_meters_per_second({.y = 16});
        CHECK(p == Circa(p_target));
    }
}

TEST_SUITE("force")
{
    TEST_CASE("forces can be trivially constructed")
    {
        Force const f_default;
        CHECK(f_default == Force::newton({.x = 0, .y = 0, .z = 0}));

        Force const f_zero = Force::zero();
        CHECK(f_zero == Force::newton({.x = 0, .y = 0, .z = 0}));
    }

    TEST_CASE("forces can be converted to string")
    {
        Force const f = Force::newton({.x = 0.1, .y = 0.3, .z = 0});

        // String to automatic unit.
        CHECK(f.to_string() == "[0.1 0.3 0] N");

        SUBCASE("forces can be streamed as automatic unit")
        {
            std::stringstream ss;
            ss << f;

            CHECK(ss.str() == "[0.1 0.3 0] N");
        }
    }

    TEST_CASE("basic constructions")
    {
        Force const f = Force::newton(Vector({.y = 100}));
        ForceDifference const df{f};
        Wrench const w1 = Wrench::zero();
        Wrench const w2 = df + w1;
        CHECK(w2.linear() == f);

        Torque const t = Torque::newton_meters(AxisAngle::around_y(1));
        TorqueDifference const dt(t);
        Wrench const w3 = dt * w1;

        CHECK(w3.angular() == Circa(t));
    }

    TEST_CASE("force can be constructed from mass times acceleration")
    {
        LinearAcceleration const a = LinearAcceleration::meters_per_second_squared({.x = 2.3});
        Mass const m = Mass::kilograms(2);

        Force const f = m * a;

        Force const f_target = Force::newton({.x = 4.6});
        CHECK(f == Circa(f_target));
    }

    TEST_CASE("force can be constructed from linear impulse divided by duration")
    {
        LinearImpulse const dp = LinearImpulse::newton_seconds({.z = 17});
        Duration const dt = Duration::milliseconds(800);

        Force const f = dp / dt;

        Force const f_target = Force::newton({.z = 21.25});
        CHECK(f == Circa(f_target));
    }
}

TEST_SUITE("temperature")
{
    TEST_CASE("temperatures can be trivially constructed")
    {
        Temperature const t_default;
        CHECK(t_default == Temperature::degrees_celsius(0));

        Temperature const t_zero = Temperature::zero();
        CHECK(t_zero == Temperature::degrees_celsius(0));
    }

    TEST_CASE("temperatures can be converted to string")
    {
        Temperature const t = Temperature::degrees_celsius(15);

        // String to automatic unit.
        CHECK(t.to_string() == "15 °C");

        SUBCASE("temperatures can be streamed as automatic unit")
        {
            std::stringstream ss;
            ss << t;

            CHECK(ss.str() == "15 °C");
        }

        // String in specific unit.
        CHECK(t.to_kelvin().to_string() == "288.15 K");

        SUBCASE("temperatures can be streamed as specific unit")
        {
            std::stringstream ss;
            ss << t.to_kelvin();

            CHECK(ss.str() == "288.15 K");
        }
    }

    TEST_CASE("testing canonical zero constructions")
    {
        Temperature const zero_default;

        CHECK(zero_default.to_degrees_celsius() == 0);

        Temperature const zero_degrees_celsius = Temperature::degrees_celsius(0);

        CHECK(zero_degrees_celsius.to_degrees_celsius() == 0);

        Temperature const zero_degrees_celsius_from_kelvin = Temperature::kelvin(273.15);

        CHECK(zero_degrees_celsius_from_kelvin.to_degrees_celsius() == 0);

        Temperature const zero_degrees_celsius_from_degrees_fahrenheit =
            Temperature::degrees_fahrenheit(32);

        CHECK(zero_degrees_celsius_from_degrees_fahrenheit.to_degrees_celsius() == Circa(0));

        Temperature const zero_degrees_celsius_from_degrees_rankine =
            Temperature::degrees_rankine(491.67);

        CHECK(zero_degrees_celsius_from_degrees_rankine.to_degrees_celsius() == Circa(0));
    }

    TEST_CASE("testing unit-specific zero constructions")
    {
        Temperature const zero_degrees_celsius = Temperature::degrees_celsius(0);

        CHECK(zero_degrees_celsius.to_degrees_celsius() == 0);

        Temperature const zero_kelvin = Temperature::kelvin(0);

        CHECK(zero_kelvin.to_degrees_celsius() == -273.15);

        Temperature const zero_degrees_fahrenheit = Temperature::degrees_fahrenheit(0);

        CHECK(zero_degrees_fahrenheit.to_degrees_celsius() == Circa(-17.7778));

        Temperature const zero_degrees_rankine = Temperature::degrees_rankine(0);

        CHECK(zero_degrees_rankine.to_degrees_celsius() == Circa(-273.15));
    }

    TEST_CASE("temperatures can be converted to several fix points")
    {
        // Data for these unit tests taken from the comparison table from the German wikipedia:
        // https://de.wikipedia.org/wiki/Grad_Fahrenheit

        Temperature const water_boiling_point = Temperature::degrees_celsius(100);

        CHECK(water_boiling_point.to_degrees_celsius() == 100);
        CHECK(water_boiling_point.to_kelvin() == 373.15);
        CHECK(water_boiling_point.to_degrees_fahrenheit() == 212);
        CHECK(water_boiling_point.to_degrees_rankine() == Circa(671.67));

        // According to Fahrenheit.
        Temperature const body_temperature_human = Temperature::degrees_fahrenheit(96);

        CHECK(body_temperature_human.to_degrees_celsius() == Circa(35.5556));
        CHECK(body_temperature_human.to_degrees_fahrenheit() == Circa(96));
        CHECK(body_temperature_human.to_kelvin() == Circa(308.705));
        CHECK(body_temperature_human.to_degrees_rankine() == Circa(555.67));

        Temperature const water_triple_point = Temperature::kelvin(273.16);

        CHECK(water_triple_point.to_degrees_celsius() == Circa(0.01));
        CHECK(water_triple_point.to_kelvin() == Circa(273.16));
        CHECK(water_triple_point.to_degrees_fahrenheit() == Circa(32.018));
        CHECK(water_triple_point.to_degrees_rankine() == Circa(491.688));

        Temperature const water_freezing_point_c = Temperature::degrees_celsius(0);

        CHECK(water_freezing_point_c.to_degrees_celsius() == Circa(0));
        CHECK(water_freezing_point_c.to_kelvin() == Circa(273.15));
        CHECK(water_freezing_point_c.to_degrees_fahrenheit() == Circa(32));
        CHECK(water_freezing_point_c.to_degrees_rankine() == Circa(491.67));

        Temperature const water_freezing_point_f = Temperature::degrees_fahrenheit(32);

        CHECK(water_freezing_point_f.to_degrees_celsius() == Circa(0));
        CHECK(water_freezing_point_f.to_kelvin() == Circa(273.15));
        CHECK(water_freezing_point_f.to_degrees_fahrenheit() == Circa(32));
        CHECK(water_freezing_point_f.to_degrees_rankine() == Circa(491.67));

        Temperature const nh4cl_ice_water_mix = Temperature::degrees_fahrenheit(0);

        CHECK(nh4cl_ice_water_mix.to_degrees_celsius() == Circa(-17.7778));
        CHECK(nh4cl_ice_water_mix.to_kelvin() == Circa(255.372));
        CHECK(nh4cl_ice_water_mix.to_degrees_fahrenheit() == Circa(0));
        CHECK(nh4cl_ice_water_mix.to_degrees_rankine() == Circa(459.67));

        Temperature const absolute_zero = Temperature::kelvin(0);

        CHECK(absolute_zero.to_degrees_celsius() == Circa(-273.15));
        CHECK(absolute_zero.to_kelvin() == Circa(0));
        CHECK(absolute_zero.to_degrees_fahrenheit() == Circa(-459.67));
        CHECK(absolute_zero.to_degrees_rankine() == Circa(0));
    }
}

TEST_SUITE("electric_current")
{
    TEST_CASE("currents can be trivially/zero constructed")
    {
        Current const i_default;
        CHECK(i_default == Current::ampere(0));

        Current const i_zero = Current::zero();
        CHECK(i_zero == Current::ampere(0));
    }

    TEST_CASE("currents can be converted to string")
    {
        Current const i_small = Current::ampere(0.15);
        Current const i_large = Current::ampere(15);

        // String to automatic unit.
        CHECK(i_small.to_string() == "150 mA");
        CHECK(i_large.to_string() == "15 A");

        SUBCASE("currents can be streamed as automatic unit")
        {
            std::stringstream ss_small;
            ss_small << i_small;
            CHECK(ss_small.str() == "150 mA");

            std::stringstream ss_large;
            ss_large << i_large;
            CHECK(ss_large.str() == "15 A");
        }

        // String in specific unit.
        CHECK(i_large.to_milliampere().to_string() == "15000 mA");

        SUBCASE("currents can be streamed as specific unit")
        {
            std::stringstream ss;
            ss << i_large.to_milliampere();

            CHECK(ss.str() == "15000 mA");
        }
    }

    TEST_CASE("basic constructions")
    {
        Current i1 = Current::ampere(15);
        CHECK(i1.to_ampere() == 15);

        Current i2 = Current::milliampere(15000);
        CHECK(i2.to_milliampere() == 15000);
    }

    TEST_CASE("unit converting constructions")
    {
        Current i1 = Current::ampere(15);
        CHECK(i1.to_milliampere() == 15000);

        Current i2 = Current::milliampere(15000);
        CHECK(i2.to_ampere() == 15);
    }
}

// NOLINTEND(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)
