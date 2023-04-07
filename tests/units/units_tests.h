#pragma once

#include <quant/geometry.h>
#include <quant/units.h>

#include <doctest/doctest.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <iostream>

using namespace quant;  // NOLINT

// NOLINTBEGIN(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)

TEST_SUITE("time")
{
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
}

TEST_SUITE("position")
{
    TEST_CASE("testing trivial constructions")
    {
        Position const p1;
        CHECK(p1 == Position::millimeters({.x = 0, .y = 0, .z = 0}));

        Position const p2 = Position::zero();
        CHECK(p2 == Position::millimeters({.x = 0, .y = 0, .z = 0}));

        Position const p3 = Position::millimeters({.x = 1, .y = 2, .z = 3});
        CHECK(p3.to_millimeters().x == 1);
        CHECK(p3.to_millimeters().y == 2);
        CHECK(p3.to_millimeters().z == 3);
        CHECK(p3.to_millimeters().unit_symbol == "mm");
    }

    TEST_CASE("testing operators")
    {
        Position const p = Position::millimeters({.x = 100, .y = 200, .z = 300});
        LinearDisplacement const disturbance =
            LinearDisplacement::millimeters({.x = 1e-14, .z = 1e-15});
        Position const p_disturbed = disturbance + p;

        CHECK(p_disturbed != p);
        CHECK(p_disturbed == Circa(p));
    }

    TEST_CASE("testing position component access")
    {
        Position const p1 = Position::millimeters({.x = 100, .y = 200, .z = 300});
        CHECK(p1.to_millimeters().x == 100);
        CHECK(p1.to_millimeters().y == 200);
        CHECK(p1.to_millimeters().z == 300);
        CHECK(p1.to_millimeters().unit_symbol == "mm");
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
        Twist const t3 = AngularVelocityDifference(vel2) + t1;
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
    TEST_CASE("basic constructions")
    {
        LinearMomentum const p = LinearMomentum::kilogram_meters_per_second({.x = 2.7});

        CHECK(p == Circa(LinearMomentum::kilogram_meters_per_second({.x = 2.7})));
        CHECK(p.to_kilogram_meters_per_second().to_string() == "[2.7 0 0] kg⋅m/s");
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
    TEST_CASE("basic constructions")
    {
        Force const f = Force::newton(Vector({.y = 100}));
        ForceDifference const df{f};
        Wrench const w1 = Wrench::zero();
        Wrench const w2 = df + w1;
        CHECK(w2.linear() == f);

        Torque const t = Torque::newton_meters(AxisAngle::around_y(1));
        TorqueDifference const dt(t);
        Wrench const w3 = dt + w1;

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
    TEST_CASE("testing canonical zero constructions")
    {
        Temperature const zero_default;

        CHECK(zero_default.to_degree_celsius() == 0);

        Temperature const zero_degree_celsius = Temperature::degree_celcius(0);

        CHECK(zero_degree_celsius.to_degree_celsius() == 0);

        Temperature const zero_degree_celsius_from_kelvin = Temperature::kelvin(273.15);

        CHECK(zero_degree_celsius_from_kelvin.to_degree_celsius() == 0);

        Temperature const zero_degree_celsius_from_degree_fahrenheit =
            Temperature::degree_fahrenheit(32);

        CHECK(zero_degree_celsius_from_degree_fahrenheit.to_degree_celsius() == Circa(0));

        Temperature const zero_degree_celsius_from_degree_rankine =
            Temperature::degree_rankine(491.67);

        CHECK(zero_degree_celsius_from_degree_rankine.to_degree_celsius() == Circa(0));
    }

    TEST_CASE("testing unit-specific zero constructions")
    {
        Temperature const zero_degree_celsius = Temperature::degree_celcius(0);

        CHECK(zero_degree_celsius.to_degree_celsius() == 0);

        Temperature const zero_kelvin = Temperature::kelvin(0);

        CHECK(zero_kelvin.to_degree_celsius() == -273.15);

        Temperature const zero_degree_fahrenheit = Temperature::degree_fahrenheit(0);

        CHECK(zero_degree_fahrenheit.to_degree_celsius() == Circa(-17.7778));

        Temperature const zero_degree_rankine = Temperature::degree_rankine(0);

        CHECK(zero_degree_rankine.to_degree_celsius() == Circa(-273.15));
    }

    TEST_CASE("temperatures can be converted to several fix points")
    {
        // Data for these unit tests taken from the comparison table from the German wikipedia:
        // https://de.wikipedia.org/wiki/Grad_Fahrenheit

        Temperature const water_boiling_point = Temperature::degree_celcius(100);

        CHECK(water_boiling_point.to_degree_celsius() == 100);
        CHECK(water_boiling_point.to_kelvin() == 373.15);
        CHECK(water_boiling_point.to_degree_fahrenheit() == 212);
        CHECK(water_boiling_point.to_degree_rankine() == Circa(671.67));

        // According to Fahrenheit.
        Temperature const body_temperature_human = Temperature::degree_fahrenheit(96);

        CHECK(body_temperature_human.to_degree_celsius() == Circa(35.5556));
        CHECK(body_temperature_human.to_degree_fahrenheit() == Circa(96));
        CHECK(body_temperature_human.to_kelvin() == Circa(308.705));
        CHECK(body_temperature_human.to_degree_rankine() == Circa(555.67));

        Temperature const water_triple_point = Temperature::kelvin(273.16);

        CHECK(water_triple_point.to_degree_celsius() == Circa(0.01));
        CHECK(water_triple_point.to_kelvin() == Circa(273.16));
        CHECK(water_triple_point.to_degree_fahrenheit() == Circa(32.018));
        CHECK(water_triple_point.to_degree_rankine() == Circa(491.688));

        Temperature const water_freezing_point_c = Temperature::degree_celcius(0);

        CHECK(water_freezing_point_c.to_degree_celsius() == Circa(0));
        CHECK(water_freezing_point_c.to_kelvin() == Circa(273.15));
        CHECK(water_freezing_point_c.to_degree_fahrenheit() == Circa(32));
        CHECK(water_freezing_point_c.to_degree_rankine() == Circa(491.67));

        Temperature const water_freezing_point_f = Temperature::degree_fahrenheit(32);

        CHECK(water_freezing_point_f.to_degree_celsius() == Circa(0));
        CHECK(water_freezing_point_f.to_kelvin() == Circa(273.15));
        CHECK(water_freezing_point_f.to_degree_fahrenheit() == Circa(32));
        CHECK(water_freezing_point_f.to_degree_rankine() == Circa(491.67));

        Temperature const nh4cl_ice_water_mix = Temperature::degree_fahrenheit(0);

        CHECK(nh4cl_ice_water_mix.to_degree_celsius() == Circa(-17.7778));
        CHECK(nh4cl_ice_water_mix.to_kelvin() == Circa(255.372));
        CHECK(nh4cl_ice_water_mix.to_degree_fahrenheit() == Circa(0));
        CHECK(nh4cl_ice_water_mix.to_degree_rankine() == Circa(459.67));

        Temperature const absolute_zero = Temperature::kelvin(0);

        CHECK(absolute_zero.to_degree_celsius() == Circa(-273.15));
        CHECK(absolute_zero.to_kelvin() == Circa(0));
        CHECK(absolute_zero.to_degree_fahrenheit() == Circa(-459.67));
        CHECK(absolute_zero.to_degree_rankine() == Circa(0));
    }
}

// NOLINTEND(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)
