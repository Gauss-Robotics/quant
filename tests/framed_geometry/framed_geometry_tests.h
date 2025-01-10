#pragma once

#include <quant/framed_geometry.h>
#include <quant/framed_geometry/forward_declarations.h>
#include <quant/geometry/forward_declarations.h>
#include <quant/units.h>

#include <doctest/doctest.h>

#include <iostream>

using namespace quant;  // NOLINT

namespace quant
{
    struct Test;
    struct TestDiff;
    using TestDomain = traits::Define3DDomain<Test, TestDiff, Test, TestDiff, Test, TestDiff>;
    template <>
    struct traits::DefineTraits<Test>
    {
        using Domain = TestDomain;
        using Difference = TestDiff;
        using GeometricType = LinearStateType;
    };

    template <>
    struct traits::DefineTraits<TestDiff>
    {
        using Domain = TestDomain;
        using Difference = TestDiff;
        using GeometricType = LinearDifferenceType;
    };

    struct Test : geometry::LinearState<Test>
    {
    };

    struct TestDiff : geometry::Difference<Test>
    {
        TestDiff() = default;
        TestDiff(Test t){};
    };

    namespace framed_geometry
    {
        template <>
        struct FrameConversion<Test>
        {
            static Test&
            convert(Test& unit, const units::position::SpatialDisplacement& /*transform*/)
            {
                return unit;
            }
        };

        template <>
        struct FrameConversion<TestDiff>
        {
            static TestDiff&
            convert(TestDiff& unit, const units::position::SpatialDisplacement& /*transform*/)
            {
                return unit;
            }
        };
    }
}
TEST_CASE("testing basic constructions")
{
    quant::Test d;  // Dummy.

    Framed<Test> const f1{d, {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};

    CHECK(f1.get_name() == "TCP");
    CHECK(f1.get_base_frame() == "ARMAR-6::RobotRoot");

    Framed<Test> const f2{d, {.name = "CoM", .base_frame = "ARMAR-6::RobotRoot"}};

    CHECK(f2.get_name() == "CoM");
    CHECK(f2.get_base_frame() == "ARMAR-6::RobotRoot");
}

TEST_CASE("testing enframing")
{
    TestDiff const p{};

    Framed<TestDiff> const origin{p, {.name = "::Origin", .base_frame = ""}};

    CHECK(origin.get_name() == "::Origin");
    CHECK(origin.get_base_frame() == "");

    Framed<TestDiff> const robot_root =
        origin.enframe(TestDiff(), "ARMAR-6::RobotRoot");

    CHECK(robot_root.get_name() == "ARMAR-6::RobotRoot");
    CHECK(robot_root.get_base_frame() == "::Origin");

    Framed<TestDiff> const right_hand_tcp = robot_root.enframe(
        TestDiff(), "ARMAR-6::TCP_R");

    CHECK(right_hand_tcp.get_name() == "ARMAR-6::TCP_R");
    CHECK(right_hand_tcp.get_base_frame() == "ARMAR-6::RobotRoot");

    Framed<TestDiff> const right_hand_com = robot_root.enframe(
        TestDiff(), "ARMAR-6::CoM_R");

    CHECK(right_hand_com.get_name() == "ARMAR-6::CoM_R");
    CHECK(right_hand_com.get_base_frame() == "ARMAR-6::RobotRoot");
}

TEST_CASE("testing basic framed differences")
{
    SUBCASE("testing framed difference")
    {
        Test const p{};  // Dummy position.

        Framed<Test> const tcp{p, {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
        Framed<Test> const com{p, {.name = "CoM", .base_frame = "ARMAR-6::RobotRoot"}};

        Framed<TestDiff> const ld = tcp - com;

        CHECK(ld.get_name() == "TCP");
        CHECK(ld.get_base_frame() == "ARMAR-6::RobotRoot");
    }
}
