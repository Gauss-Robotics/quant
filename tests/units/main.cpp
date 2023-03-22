#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <quant/units.h>

#include <doctest/doctest.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <iostream>

using namespace quant;

double const Precision = 1e-6;

TEST_CASE("testing time")
{
    SUBCASE("TimePointTest")
    {
        TimePoint const t1 = TimePoint::MicroSeconds(100);
        CHECK(t1.toMicroSeconds() == 100);

        TimePoint const t2 = TimePoint::MilliSeconds(100);
        CHECK(t2.toMicroSeconds() == 100'000);

        TimePoint const t3 = TimePoint::Seconds(100);
        CHECK(t3.toMicroSeconds() == 100'000'000);

        TimePoint const t4 = TimePoint::Minutes(100);
        CHECK(t4.toMicroSeconds() == 6'000'000'000);

        TimePoint const t5 = TimePoint::Hours(100);
        CHECK(t5.toMicroSeconds() == 360'000'000'000);

        TimePoint const t6 = TimePoint::Days(100);
        CHECK(t6.toMicroSeconds() == 8'640'000'000'000);
    }

    SUBCASE("TimePointRoundingTest")
    {
        TimePoint const t1Down = TimePoint::MicroSeconds(499);
        CHECK(t1Down.toMilliSeconds() == 0);
        TimePoint const t1Up = TimePoint::MicroSeconds(500);
        CHECK(t1Up.toMilliSeconds() == 1);

        TimePoint const t2Down = TimePoint::MilliSeconds(499);
        CHECK(t2Down.toSeconds() == 0);
        TimePoint const t2Up = TimePoint::MilliSeconds(500);
        CHECK(t2Up.toSeconds() == 1);

        TimePoint const t3Down = TimePoint::Seconds(29);
        CHECK(t3Down.toMinutes() == 0);
        TimePoint const t3Up = TimePoint::Seconds(30);
        CHECK(t3Up.toMinutes() == 1);

        TimePoint const t4Down = TimePoint::Minutes(29);
        CHECK(t4Down.toHours() == 0);
        TimePoint const t4Up = TimePoint::Minutes(30);
        CHECK(t4Up.toHours() == 1);

        TimePoint const t5Down = TimePoint::Hours(11);
        CHECK(t5Down.toDays() == 0);
        TimePoint const t5Up = TimePoint::Hours(12);
        CHECK(t5Up.toDays() == 1);
    }

    SUBCASE("DurationRoundingTest")
    {
        Duration const t1Down = Duration::MicroSeconds(499);
        CHECK(t1Down.toMilliSeconds() == 0);
        Duration const t1Up = Duration::MicroSeconds(500);
        CHECK(t1Up.toMilliSeconds() == 1);

        Duration const t2Down = Duration::MilliSeconds(499);
        CHECK(t2Down.toSeconds() == 0);
        Duration const t2Up = Duration::MilliSeconds(500);
        CHECK(t2Up.toSeconds() == 1);

        Duration const t3Down = Duration::Seconds(29);
        CHECK(t3Down.toMinutes() == 0);
        Duration const t3Up = Duration::Seconds(30);
        CHECK(t3Up.toMinutes() == 1);

        Duration const t4Down = Duration::Minutes(29);
        CHECK(t4Down.toHours() == 0);
        Duration const t4Up = Duration::Minutes(30);
        CHECK(t4Up.toHours() == 1);

        Duration const t5Down = Duration::Hours(11);
        CHECK(t5Down.toDays() == 0);
        Duration const t5Up = Duration::Hours(12);
        CHECK(t5Up.toDays() == 1);
    }

    SUBCASE("DurationTest")
    {
        Duration const d1 = TimePoint::MicroSeconds(1000) - TimePoint::MicroSeconds(333);
        CHECK(d1.toMicroSeconds() == 667);
    }
}

TEST_CASE("testing position")
{
    SUBCASE("testing trivial constructions")
    {
        Position const p1;
        CHECK(p1.toMilliMeters().toEigen() == Eigen::Vector3d(0, 0, 0));

        Position const p2 = Position::Origin();
        CHECK(p2.toMilliMeters().toEigen() == Eigen::Vector3d(0, 0, 0));

        Position const p3 = Position::MilliMeters({.x = 1, .y = 2, .z = 3});
        CHECK(p3.toMilliMeters().toEigen() == Eigen::Vector3d(1, 2, 3));

        Position const p4 = Position::MilliMeters(Vector::FromEigen(Eigen::Vector3d(3, 2, 1)));
        CHECK(p4.toMilliMeters().toEigen() == Eigen::Vector3d(3, 2, 1));
    }

    Position const p1 = Position::MilliMeters(100, 200, 300);
    Position const p2 = Position::MilliMeters(0, 100, 0);

    SUBCASE("testing operators")
    {
        LinearDisplacement const disturbance =
            LinearDisplacement::MilliMeters({.x = 1e-14, .z = 1e-15});
        Position const p = disturbance + p1;

        CHECK(p1 != p);
        CHECK(p.isApprox(p1, Precision));
    }

    SUBCASE("testing difference")
    {
        Position const tl = p1 - p2;  // TODO(dreher): Should this work?
        CHECK(tl.toMilliMeters().toEigen() == Eigen::Vector3d(100, 100, 300));
    }

    SUBCASE("testing position component access")
    {
        CHECK(p1.toMilliMeters().toEigen() == Eigen::Vector3d(100, 200, 300));
        CHECK(p1.toMilliMeters().x == 100);
        CHECK(p1.toMilliMeters().y == 200);
        CHECK(p1.toMilliMeters().z == 300);
    }

    SUBCASE("testing different operations")
    {
        AngularDisplacement const rot = AngularDisplacement::Radians(AxisAngle::AroundY(M_PI));
        Position const pos1 = Position::MilliMeters({.y = 100, .z = 200});
        Position const rotPos = rot * pos1;
        CHECK(rotPos.toMilliMeters().x == doctest::Approx(0));
        CHECK(rotPos.toMilliMeters().y == doctest::Approx(100));
        CHECK(rotPos.toMilliMeters().z == doctest::Approx(-200));

        LinearDisplacement const trans = LinearDisplacement::MilliMeters({.x = 5, .z = 100});
        Position const transPos = trans + pos1;
        CHECK(transPos == Position::MilliMeters({.x = 5, .y = 100, .z = 300}));

        LinearDisplacement const rotTrans = rot * trans;
        CHECK(rotTrans.toMilliMeters().x == doctest::Approx(-5));
        CHECK(rotTrans.toMilliMeters().y == doctest::Approx(0));
        CHECK(rotTrans.toMilliMeters().z == doctest::Approx(-100));

        Position const rotTransPos = rotTrans + pos1;
        CHECK(rotTransPos.toMilliMeters().x == doctest::Approx(-5));
        CHECK(rotTransPos.toMilliMeters().y == doctest::Approx(100));
        CHECK(rotTransPos.toMilliMeters().z == doctest::Approx(100));
    }
}

TEST_CASE("testing velocity")
{
    SUBCASE("AngularVelocityConstructFromFloatEigenVector")
    {
        Eigen::AngleAxisd const radPerSec(M_PI / 2, Eigen::Vector3d(1, 0, 1).normalized());
        AngularVelocity const av =
            AngularVelocity::RadiansPerSecond(AxisAngle::FromEigen(radPerSec));
        Eigen::AngleAxisd const radPerSecReconstructed = av.toAngleAxis().toEigen();

        CHECK(radPerSecReconstructed.isApprox(radPerSec, Precision));
    }

    SUBCASE("CompoundTypesTest1")
    {
        Twist const t1 = Twist::Zero();
        LinearVelocity const vel1 = LinearVelocity::MilliMetersPerSecond({.y = 100});
        Twist const t2 = LinearVelocityDifference(vel1) + t1;
        CHECK(t2.linear() == vel1);

        AngularVelocity const vel2 = AngularVelocity::RadiansPerSecond({.angle = M_PI});
        Twist const t3 = vel2.deltaToOrigin() + t1;
        CHECK(t3.angular().isApprox(vel2, Precision));
    }

    SUBCASE("testing complex unit conversions")
    {
        // First measurement.
        Position const x1 = Position::MilliMeters({.z = 100});
        TimePoint const t1 = TimePoint::Seconds(15);

        // Second measurement.
        Position const x2 = Position::MilliMeters({.x = 100, .y = 100, .z = 200});
        TimePoint const t2 = TimePoint::Seconds(17);

        // Calculate differences.
        LinearDisplacement const dx = x2 - x1;
        Duration const dt = t2 - t1;

        // Calculate linear velocity.
        LinearVelocity const vel = dx / dt;

        // Calculate distance and speed.
        Distance const dist = dx.toDistance();
        Speed const speed = vel.toSpeed();

        // Check distance.
        double const distTarget = 173.20508075688772;
        std::cout << "Distance actual: " << dist.toMilliMeters() << "." << std::endl;
        std::cout << "Distance target: " << distTarget << "." << std::endl;
        CHECK(dist.toMilliMeters() == doctest::Approx(distTarget));

        // Check speed.
        double const speedTarget = distTarget / 2;
        std::cout << "Speed actual: " << speed.toMilliMetersPerSecond() << "." << std::endl;
        std::cout << "Speed target: " << speedTarget << "." << std::endl;
        CHECK(speed.toMilliMetersPerSecond() == doctest::Approx(speedTarget));

        // Check velocity.
        LinearVelocity const velTarget =
            LinearVelocity::MilliMetersPerSecond({.x = 50, .y = 50, .z = 50});
        std::cout << "Velocity actual: " << vel << "." << std::endl;
        std::cout << "Velocity target: " << velTarget << "." << std::endl;
        CHECK(vel.isApprox(velTarget, Precision));
    }
}

TEST_CASE("testing force")
{
    SUBCASE("CompoundTypesTest2")
    {
        Force const f = Force::Newton(Vector({.y = 100}));
        ForceDifference const df{f};
        Wrench const w1 = Wrench::Zero();
        Wrench const w2 = df + w1;
        CHECK(w2.linear() == f);

        Torque const t = Torque::NewtonMeters(AxisAngle::AroundY(1));
        Difference<Torque> const dt = t.deltaToOrigin();
        Wrench const w3 = dt + w1;

        std::cout << "Torque actual: " << w3.angular() << "." << std::endl;
        std::cout << "Torque target: " << t << "." << std::endl;
        CHECK(w3.angular().isApprox(t, Precision));
    }
}

TEST_CASE("testing temperature")
{
    SUBCASE("testing canonical zero constructions")
    {
        Temperature const zeroDefault;

        CHECK(zeroDefault.toDegreeCelsius() == 0);

        Temperature const zeroDegreeCelsius = Temperature::DegreeCelcius(0);

        CHECK(zeroDegreeCelsius.toDegreeCelsius() == 0);

        Temperature const zeroDegreeCelsiusFromKelvin = Temperature::Kelvin(273.15);

        CHECK(zeroDegreeCelsiusFromKelvin.toDegreeCelsius() == 0);

        Temperature const zeroDegreeCelsiusFromDegreeFahrenheit = Temperature::DegreeFahrenheit(32);

        CHECK(zeroDegreeCelsiusFromDegreeFahrenheit.toDegreeCelsius() == doctest::Approx(0));

        Temperature const zeroDegreeCelsiusFromDegreeRankine = Temperature::DegreeRankine(491.67);

        CHECK(zeroDegreeCelsiusFromDegreeRankine.toDegreeCelsius() == doctest::Approx(0));
    }

    SUBCASE("testing unit-specific zero constructions")
    {
        Temperature const zeroDegreeCelsius = Temperature::DegreeCelcius(0);

        CHECK(zeroDegreeCelsius.toDegreeCelsius() == 0);

        Temperature const zeroKelvin = Temperature::Kelvin(0);

        CHECK(zeroKelvin.toDegreeCelsius() == -273.15);

        Temperature const zeroDegreeFahrenheit = Temperature::DegreeFahrenheit(0);

        CHECK(zeroDegreeFahrenheit.toDegreeCelsius() == doctest::Approx(-17.7778));

        Temperature const zeroDegreeRankine = Temperature::DegreeRankine(0);

        CHECK(zeroDegreeRankine.toDegreeCelsius() == doctest::Approx(-273.15));
    }

    SUBCASE("testing conversions of fix points")
    {
        // Data for these unit tests taken from the comparison table from the German wikipedia:
        // https://de.wikipedia.org/wiki/Grad_Fahrenheit

        Temperature const waterBoilingPoint = Temperature::DegreeCelcius(100);

        CHECK(waterBoilingPoint.toDegreeCelsius() == 100);
        CHECK(waterBoilingPoint.toKelvin() == 373.15);
        CHECK(waterBoilingPoint.toDegreeFahrenheit() == 212);
        CHECK(waterBoilingPoint.toDegreeRankine() == doctest::Approx(671.67));

        // According to Fahrenheit.
        Temperature const bodyTemperatureHuman = Temperature::DegreeFahrenheit(96);

        CHECK(bodyTemperatureHuman.toDegreeCelsius() == doctest::Approx(35.5556));
        CHECK(bodyTemperatureHuman.toDegreeFahrenheit() == doctest::Approx(96));
        CHECK(bodyTemperatureHuman.toKelvin() == doctest::Approx(308.705));
        CHECK(bodyTemperatureHuman.toDegreeRankine() == doctest::Approx(555.67));

        Temperature const waterTriplePoint = Temperature::Kelvin(273.16);

        CHECK(waterTriplePoint.toDegreeCelsius() == doctest::Approx(0.01));
        CHECK(waterTriplePoint.toKelvin() == doctest::Approx(273.16));
        CHECK(waterTriplePoint.toDegreeFahrenheit() == doctest::Approx(32.018));
        CHECK(waterTriplePoint.toDegreeRankine() == doctest::Approx(491.688));

        Temperature const waterFreezingPointC = Temperature::DegreeCelcius(0);

        CHECK(waterFreezingPointC.toDegreeCelsius() == doctest::Approx(0));
        CHECK(waterFreezingPointC.toKelvin() == doctest::Approx(273.15));
        CHECK(waterFreezingPointC.toDegreeFahrenheit() == doctest::Approx(32));
        CHECK(waterFreezingPointC.toDegreeRankine() == doctest::Approx(491.67));

        Temperature const waterFreezingPointF = Temperature::DegreeFahrenheit(32);

        CHECK(waterFreezingPointF.toDegreeCelsius() == doctest::Approx(0));
        CHECK(waterFreezingPointF.toKelvin() == doctest::Approx(273.15));
        CHECK(waterFreezingPointF.toDegreeFahrenheit() == doctest::Approx(32));
        CHECK(waterFreezingPointF.toDegreeRankine() == doctest::Approx(491.67));

        Temperature const nh4clIceWaterMix = Temperature::DegreeFahrenheit(0);

        CHECK(nh4clIceWaterMix.toDegreeCelsius() == doctest::Approx(-17.7778));
        CHECK(nh4clIceWaterMix.toKelvin() == doctest::Approx(255.372));
        CHECK(nh4clIceWaterMix.toDegreeFahrenheit() == doctest::Approx(0));
        CHECK(nh4clIceWaterMix.toDegreeRankine() == doctest::Approx(459.67));

        Temperature const absoluteZero = Temperature::Kelvin(0);

        CHECK(absoluteZero.toDegreeCelsius() == doctest::Approx(-273.15));
        CHECK(absoluteZero.toKelvin() == doctest::Approx(0));
        CHECK(absoluteZero.toDegreeFahrenheit() == doctest::Approx(-459.67));
        CHECK(absoluteZero.toDegreeRankine() == doctest::Approx(0));
    }
}
