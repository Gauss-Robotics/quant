#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN


#include <iostream>

#include <doctest/doctest.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <quant/units/time.h>
#include <quant/units/position.h>
#include <quant/units/velocity.h>
#include <quant/units/force.h>


using namespace quant;


const double Precision = 1e-6;


TEST_CASE("testing time")
{
    SUBCASE("TimePointTest")
    {
        const TimePoint t1 = TimePoint::MicroSeconds(100);
        CHECK(t1.toMicroSeconds() == 100);

        const TimePoint t2 = TimePoint::MilliSeconds(100);
        CHECK(t2.toMicroSeconds() == 100'000);

        const TimePoint t3 = TimePoint::Seconds(100);
        CHECK(t3.toMicroSeconds() == 100'000'000);

        const TimePoint t4 = TimePoint::Minutes(100);
        CHECK(t4.toMicroSeconds() == 6'000'000'000);

        const TimePoint t5 = TimePoint::Hours(100);
        CHECK(t5.toMicroSeconds() == 360'000'000'000);

        const TimePoint t6 = TimePoint::Days(100);
        CHECK(t6.toMicroSeconds() == 8'640'000'000'000);
    }

    SUBCASE("TimePointRoundingTest")
    {
        const TimePoint t1Down = TimePoint::MicroSeconds(499);
        CHECK(t1Down.toMilliSeconds() == 0);
        const TimePoint t1Up = TimePoint::MicroSeconds(500);
        CHECK(t1Up.toMilliSeconds() == 1);

        const TimePoint t2Down = TimePoint::MilliSeconds(499);
        CHECK(t2Down.toSeconds() == 0);
        const TimePoint t2Up = TimePoint::MilliSeconds(500);
        CHECK(t2Up.toSeconds() == 1);

        const TimePoint t3Down = TimePoint::Seconds(29);
        CHECK(t3Down.toMinutes() == 0);
        const TimePoint t3Up = TimePoint::Seconds(30);
        CHECK(t3Up.toMinutes() == 1);

        const TimePoint t4Down = TimePoint::Minutes(29);
        CHECK(t4Down.toHours() == 0);
        const TimePoint t4Up = TimePoint::Minutes(30);
        CHECK(t4Up.toHours() == 1);

        const TimePoint t5Down = TimePoint::Hours(11);
        CHECK(t5Down.toDays() == 0);
        const TimePoint t5Up = TimePoint::Hours(12);
        CHECK(t5Up.toDays() == 1);
    }

    SUBCASE("DurationRoundingTest")
    {
        const Duration t1Down = Duration::MicroSeconds(499);
        CHECK(t1Down.toMilliSeconds() == 0);
        const Duration t1Up = Duration::MicroSeconds(500);
        CHECK(t1Up.toMilliSeconds() == 1);

        const Duration t2Down = Duration::MilliSeconds(499);
        CHECK(t2Down.toSeconds() == 0);
        const Duration t2Up = Duration::MilliSeconds(500);
        CHECK(t2Up.toSeconds() == 1);

        const Duration t3Down = Duration::Seconds(29);
        CHECK(t3Down.toMinutes() == 0);
        const Duration t3Up = Duration::Seconds(30);
        CHECK(t3Up.toMinutes() == 1);

        const Duration t4Down = Duration::Minutes(29);
        CHECK(t4Down.toHours() == 0);
        const Duration t4Up = Duration::Minutes(30);
        CHECK(t4Up.toHours() == 1);

        const Duration t5Down = Duration::Hours(11);
        CHECK(t5Down.toDays() == 0);
        const Duration t5Up = Duration::Hours(12);
        CHECK(t5Up.toDays() == 1);
    }

    SUBCASE("DurationTest")
    {
        const Duration d1 = TimePoint::MicroSeconds(1000) - TimePoint::MicroSeconds(333);
        CHECK(d1.toMicroSeconds() == 667);
    }
}


TEST_CASE("testing position")
{
    SUBCASE("testing trivial constructions")
    {
        const Position p1;
        CHECK(p1.toMilliMeters().toEigen() == Eigen::Vector3d(0, 0, 0));

        const Position p2 = Position::Origin();
        CHECK(p2.toMilliMeters().toEigen() == Eigen::Vector3d(0, 0, 0));

        const Position p3 = Position::MilliMeters({.x = 1, .y = 2, .z = 3});
        CHECK(p3.toMilliMeters().toEigen() == Eigen::Vector3d(1, 2, 3));

        const Position p4 = Position::MilliMeters(Vector::FromEigen(Eigen::Vector3d(3, 2, 1)));
        CHECK(p4.toMilliMeters().toEigen() == Eigen::Vector3d(3, 2, 1));
    }

    const Position p1 = Position::MilliMeters(100, 200, 300);
    const Position p2 = Position::MilliMeters(0, 100, 0);

    SUBCASE("testing operators")
    {
        const Difference<Position> disturbance =
            Position::MilliMeters({.x = 1e-14, .z = 1e-15}).deltaToOrigin();
        const Position ca_p = disturbance + p1;

        CHECK(p1 != ca_p);
        CHECK(ca_p.isApprox(p1, Precision));
    }

    SUBCASE("testing difference")
    {
        const Position tl = p1 - p2; // TODO: Should this work?
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
        const Difference<Orientation> rot = Orientation::Radians(AxisAngle::AroundY(M_PI)).deltaToOrigin();
        //const Rotation r = Rotation::Roll(0) * Rotation::Pitch(M_PI) * Rotation::Yaw(0);
        // [0, 100, 200]
        const Position pos1 = Position::MilliMeters({.y = 100, .z = 200});
        const Position rotPos = rot * pos1;
        CHECK(rotPos.toMilliMeters().x == doctest::Approx(0));
        CHECK(rotPos.toMilliMeters().y == doctest::Approx(100));
        CHECK(rotPos.toMilliMeters().z == doctest::Approx(-200));

        const Difference<Position> trans = Position::MilliMeters({.x = 5, .z = 100}).deltaToOrigin();
        const Position transPos = trans + pos1;
        CHECK(transPos == Position::MilliMeters({.x = 5, .y = 100, .z = 300}));

        const Difference<Position> rotTrans = rot * trans;
        CHECK(rotTrans.pointFromOrigin().toMilliMeters().x == doctest::Approx(-5));
        CHECK(rotTrans.pointFromOrigin().toMilliMeters().y == doctest::Approx(0));
        CHECK(rotTrans.pointFromOrigin().toMilliMeters().z == doctest::Approx(-100));

        const Position rotTransPos = rotTrans + pos1;
        CHECK(rotTransPos.toMilliMeters().x == doctest::Approx(-5));
        CHECK(rotTransPos.toMilliMeters().y == doctest::Approx(100));
        CHECK(rotTransPos.toMilliMeters().z == doctest::Approx(100));

        /*
        static const FrameID armar6FrameId = {.agent = "Armar6", .frame = "root"};

        const FrameTransform robotRoot_T_global(tf,
                                                {.frame = armar6FrameId, .baseFrame = GlobalFrameID});
        const FrameTransform global_T_robotRoot = robotRoot_T_global.inverse();
        const FramedPosition robotRoot_Pt_tcp(Position(1, 2, 3), armar6FrameId);

        const FramedPosition global_Pt_tcp = global_T_robotRoot * robotRoot_Pt_tcp;*/
    }
}


TEST_CASE("testing velocity")
{
    SUBCASE("AngularVelocityConstructFromFloatEigenVector")
    {
        using namespace quant;

        const Eigen::AngleAxisd radPerSec(M_PI / 2, Eigen::Vector3d(1, 0, 1).normalized());
        const AngularVelocity av = AngularVelocity::RadiansPerSecond(AxisAngle::FromEigen(radPerSec));
        const Eigen::AngleAxisd radPerSecReconstructed = av.toAngleAxis().toEigen();

        CHECK(radPerSecReconstructed.isApprox(radPerSec, Precision));
    }

    SUBCASE("CompoundTypesTest1")
    {
        using namespace quant;

        const Twist t1 = Twist::Zero();
        const LinearVelocity vel1 = LinearVelocity::MilliMetersPerSecond({.y = 100});
        const Twist t2 = vel1.deltaToOrigin() + t1;
        CHECK(t2.linear() == vel1);

        const AngularVelocity vel2 = AngularVelocity::RadiansPerSecond({.angle = M_PI});
        const Twist t3 = vel2.deltaToOrigin() + t1;
        CHECK(t3.angular().isApprox(vel2, Precision));
    }

    SUBCASE("testing complex unit conversions")
    {
        using namespace quant;

        // First measurement.
        const Position x1 = Position::MilliMeters({.z = 100});
        const TimePoint t1 = TimePoint::Seconds(15);

        // Second measurement.
        const Position x2 = Position::MilliMeters({.x = 100, .y = 100, .z = 200});
        const TimePoint t2 = TimePoint::Seconds(17);

        // Calculate differences.
        const LinearDisplacement dx = x2 - x1;
        const Duration dt = t2 - t1;

        // Calculate linear velocity.
        const LinearVelocity vel = dx / dt;

        // Calculate distance and speed.
        const Distance dist = dx.toDistance();
        const Speed speed = vel.toSpeed();

        // Check distance.
        const double distTarget = 173.20508075688772;
        std::cout << "Distance actual: " << dist.toMilliMeters() << "." << std::endl;
        std::cout << "Distance target: " << distTarget << "." << std::endl;
        CHECK(dist.toMilliMeters() == doctest::Approx(distTarget));

        // Check speed.
        const double speedTarget = distTarget / 2;
        std::cout << "Speed actual: " << speed.toMilliMetersPerSecond() << "." << std::endl;
        std::cout << "Speed target: " << speedTarget << "." << std::endl;
        CHECK(speed.toMilliMetersPerSecond() == doctest::Approx(speedTarget));

        // Check velocity.
        const LinearVelocity velTarget =
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
        const Force f = Force::Newton(Vector({.y = 100}));
        const Difference<Force> df = f.deltaToOrigin();
        const Wrench w1 = Wrench::Zero();
        const Wrench w2 = df + w1;
        CHECK(w2.linear() == f);

        const Torque t = Torque::NewtonMeters(AxisAngle::AroundY(1));
        const Difference<Torque> dt = t.deltaToOrigin();
        const Wrench w3 = dt + w1;

        std::cout << "Torque actual: " << w3.angular() << "." << std::endl;
        std::cout << "Torque target: " << t << "." << std::endl;
        CHECK(w3.angular().isApprox(t, Precision));
    }
}

