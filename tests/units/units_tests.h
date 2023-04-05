#pragma once

#include <quant/geometry.h>
#include <quant/units.h>

#include <doctest/doctest.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <iostream>

using namespace quant;

TEST_CASE("testing time")
{
    SUBCASE("basic time point constructions")
    {
        TimePoint const t1 = TimePoint::microseconds(100);
        CHECK(t1.to_microseconds() == 100);

        TimePoint const t2 = TimePoint::milliseconds(100);
        CHECK(t2.to_microseconds() == 100'000);

        TimePoint const t3 = TimePoint::seconds(100);
        CHECK(t3.to_microseconds() == 100'000'000);

        TimePoint const t4 = TimePoint::minutes(100);
        CHECK(t4.to_microseconds() == 6'000'000'000);

        TimePoint const t5 = TimePoint::hours(100);
        CHECK(t5.to_microseconds() == 360'000'000'000);

        TimePoint const t6 = TimePoint::days(100);
        CHECK(t6.to_microseconds() == 8'640'000'000'000);
    }

    SUBCASE("basic time point conversions")
    {
        // NOLINTBEGIN(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)

        TimePoint const t1_down = TimePoint::microseconds(499);
        CHECK(t1_down.to_milliseconds() == Circa(0.499));
        TimePoint const t1_up = TimePoint::microseconds(500);
        CHECK(t1_up.to_milliseconds() == Circa(0.5));

        TimePoint const t2_down = TimePoint::milliseconds(499);
        CHECK(t2_down.to_seconds() == Circa(0.499));
        TimePoint const t2_up = TimePoint::milliseconds(500);
        CHECK(t2_up.to_seconds() == Circa(0.5));

        TimePoint const t3_down = TimePoint::seconds(29);
        CHECK(t3_down.to_minutes() == Circa(0.48333));
        TimePoint const t3_up = TimePoint::seconds(30);
        CHECK(t3_up.to_minutes() == Circa(0.5));

        TimePoint const t4_down = TimePoint::minutes(29);
        CHECK(t4_down.to_hours() == Circa(0.48333));
        TimePoint const t4_up = TimePoint::minutes(30);
        CHECK(t4_up.to_hours() == Circa(0.5));

        TimePoint const t5_down = TimePoint::hours(11);
        CHECK(t5_down.to_days() == Circa(0.45833));
        TimePoint const t5_up = TimePoint::hours(12);
        CHECK(t5_up.to_days() == Circa(0.5));

        // NOLINTEND(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)
    }

    SUBCASE("basic duration conversions")
    {
        // NOLINTBEGIN(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)

        Duration const t1_down = Duration::microseconds(499);
        CHECK(t1_down.to_milliseconds() == Circa(0.499));
        Duration const t1_up = Duration::microseconds(500);
        CHECK(t1_up.to_milliseconds() == Circa(0.5));

        Duration const t2_down = Duration::milliseconds(499);
        CHECK(t2_down.to_seconds() == Circa(0.499));
        Duration const t2_up = Duration::milliseconds(500);
        CHECK(t2_up.to_seconds() == Circa(0.5));

        Duration const t3_down = Duration::seconds(29);
        CHECK(t3_down.to_minutes() == Circa(0.48333));
        Duration const t3_up = Duration::seconds(30);
        CHECK(t3_up.to_minutes() == Circa(0.5));

        Duration const t4_down = Duration::minutes(29);
        CHECK(t4_down.to_hours() == Circa(0.48333));
        Duration const t4_up = Duration::minutes(30);
        CHECK(t4_up.to_hours() == Circa(0.5));

        Duration const t5_down = Duration::hours(11);
        CHECK(t5_down.to_days() == Circa(0.45833));
        Duration const t5_up = Duration::hours(12);
        CHECK(t5_up.to_days() == Circa(0.5));

        // NOLINTEND(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)
    }

    SUBCASE("duration as difference of time point")
    {
        Duration const d1 = TimePoint::microseconds(1000) - TimePoint::microseconds(333);
        CHECK(d1.to_microseconds() == 667);
    }
}

TEST_CASE("testing position")
{
    SUBCASE("testing trivial constructions")
    {
        Position const p1;
        CHECK(p1.to_millimeters().to_eigen() == Eigen::Vector3d(0, 0, 0));

        Position const p2 = Position::zero();
        CHECK(p2.to_millimeters().to_eigen() == Eigen::Vector3d(0, 0, 0));

        Position const p3 = Position::millimeters({.x = 1, .y = 2, .z = 3});
        CHECK(p3.to_millimeters().to_eigen() == Eigen::Vector3d(1, 2, 3));

        Position const p4 = Position::millimeters(Vector::from_eigen(Eigen::Vector3d(3, 2, 1)));
        CHECK(p4.to_millimeters().to_eigen() == Eigen::Vector3d(3, 2, 1));
    }

    Position const p1 = Position::millimeters({.x = 100, .y = 200, .z = 300});
    Position const p2 = Position::millimeters({.y = 100});

    SUBCASE("testing operators")
    {
        LinearDisplacement const disturbance =
            LinearDisplacement::millimeters({.x = 1e-14, .z = 1e-15});
        Position const p = disturbance + p1;

        CHECK(p1 != p);
        CHECK(p == Circa(p));
    }

    SUBCASE("testing position component access")
    {
        CHECK(p1.to_millimeters().to_eigen() == Eigen::Vector3d(100, 200, 300));
        CHECK(p1.to_millimeters().x == 100);
        CHECK(p1.to_millimeters().y == 200);
        CHECK(p1.to_millimeters().z == 300);
    }

    SUBCASE("testing different operations")
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

TEST_CASE("testing velocity")
{
    SUBCASE("AngularVelocityConstructFromFloatEigenVector")
    {
        Eigen::AngleAxisd const rad_per_sec(M_PI / 2, Eigen::Vector3d(1, 0, 1).normalized());
        AngularVelocity const av =
            AngularVelocity::radians_per_second(AxisAngle::from_eigen(rad_per_sec));
        Eigen::AngleAxisd const rad_per_sec_reconstructed = av.to_angle_axis().to_eigen();

        CHECK(rad_per_sec_reconstructed.isApprox(rad_per_sec));
    }

    SUBCASE("CompoundTypesTest1")
    {
        Twist const t1 = Twist::zero();
        LinearVelocity const vel1 = LinearVelocity::millimeters_per_second({.y = 100});
        Twist const t2 = LinearVelocityDifference(vel1) + t1;
        CHECK(t2.linear() == vel1);

        AngularVelocity const vel2 = AngularVelocity::radians_per_second({.angle = M_PI});
        Twist const t3 = AngularVelocityDifference(vel2) + t1;
        CHECK(t3.angular() == Circa(vel2));
    }

    SUBCASE("testing complex unit conversions")
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

        // Calculate distance and speed.
        Distance const dist = dx.to_distance();
        Speed const speed = vel.to_speed();

        // Check distance.
        double const dist_target = 173.20508075688772;
        std::cout << "Distance actual: " << dist.to_millimeters() << "." << std::endl;
        std::cout << "Distance target: " << dist_target << "." << std::endl;
        CHECK(dist.to_millimeters() == Circa(dist_target));

        // Check speed.
        double const speed_target = dist_target / 2;
        std::cout << "Speed actual: " << speed.to_millimeters_per_second() << "." << std::endl;
        std::cout << "Speed target: " << speed_target << "." << std::endl;
        CHECK(speed.to_millimeters_per_second() == Circa(speed_target));

        // Check velocity.
        LinearVelocity const vel_target =
            LinearVelocity::millimeters_per_second({.x = 50, .y = 50, .z = 50});
        // std::cout << "Velocity actual: " << vel << "." << std::endl;
        // std::cout << "Velocity target: " << vel_target << "." << std::endl;
        CHECK(vel == Circa(vel_target));
    }
}

TEST_CASE("testing mass")
{
    // NOLINTBEGIN(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)

    SUBCASE("basic constructions")
    {
        Mass const m1 = Mass::milligrams(100);
        CHECK(m1.to_milligrams() == Circa(100));

        Mass const m2 = Mass::grams(123);
        CHECK(m2.to_grams() == Circa(123));

        Mass const m3 = Mass::kilograms(321);
        CHECK(m3.to_kilograms() == Circa(321));
    }

    SUBCASE("unit converting constructions")
    {
        Mass const m1 = Mass::milligrams(1'000);
        CHECK(m1.to_grams() == 1);

        Mass const m2 = Mass::grams(1'234);
        CHECK(m2.to_kilograms() == 1.234);
    }

    // NOLINTEND(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)
}

TEST_CASE("testing force")
{
    SUBCASE("basic constructions")
    {
        Force const f = Force::newton(Vector({.y = 100}));
        ForceDifference const df{f};
        Wrench const w1 = Wrench::zero();
        Wrench const w2 = df + w1;
        CHECK(w2.linear() == f);

        Torque const t = Torque::newton_meters(AxisAngle::around_y(1));
        TorqueDifference const dt(t);
        Wrench const w3 = dt + w1;

        std::cout << "Torque actual: " << w3.angular() << "." << std::endl;
        std::cout << "Torque target: " << t << "." << std::endl;
        CHECK(w3.angular() == Circa(t));
    }

    SUBCASE("from acceleration and mass")
    {
        // NOLINTBEGIN(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)

        LinearAcceleration const a = LinearAcceleration::meters_per_second_squared({.x = 2.3});
        Mass const m = Mass::kilograms(2);

        Force const f = m * a;

        CHECK(f == Circa(Force::newton({.x = 4.6})));

        // NOLINTEND(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)
    }
}

TEST_CASE("testing temperature")
{
    // NOLINTBEGIN(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)

    SUBCASE("testing canonical zero constructions")
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

    SUBCASE("testing unit-specific zero constructions")
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

    SUBCASE("testing conversions of fix points")
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

    // NOLINTEND(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)
}
