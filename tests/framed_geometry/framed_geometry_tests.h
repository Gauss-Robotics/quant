#pragma once
#include <quant/framed_geometry.h>

#include <doctest/doctest.h>

#include <iostream>

#include "DummyLinearState.h"
#include "quant/framed_geometry/Adjoint.h"

using namespace quant;  // NOLINT

TEST_CASE("testing basic constructions")
{
    quant::DummyLinearState const d;  // Dummy.

    FramedDummyLinearState const f1{d, {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};

    CHECK(f1.get_name() == "TCP");
    CHECK(f1.get_base_frame() == "ARMAR-6::RobotRoot");

    FramedDummyLinearState const f2{d, {.name = "CoM", .base_frame = "ARMAR-6::RobotRoot"}};

    CHECK(f2.get_name() == "CoM");
    CHECK(f2.get_base_frame() == "ARMAR-6::RobotRoot");
}

TEST_CASE("testing enframing")
{
    DummyLinearState const p{};

    FramedDummyLinearState const origin{p, {.name = "::Origin", .base_frame = ""}};

    CHECK(origin.get_name() == "::Origin");
    CHECK(origin.get_base_frame() == "");

    FramedDummyLinearDiff const robot_root = origin.enframe(DummyLinearDiff());

    CHECK(robot_root.get_base_frame() == "::Origin");

    FramedDummyLinearState const right_hand_tcp =
        origin.enframe(DummyLinearState(), "ARMAR-6::TCP_R");

    CHECK(right_hand_tcp.get_name() == "ARMAR-6::TCP_R");
    CHECK(right_hand_tcp.get_base_frame() == "::Origin");

    FramedDummySpatialState const right_hand_com =
        right_hand_tcp.enframe(DummySpatialState(), "ARMAR-6::CoM_R");

    CHECK(right_hand_com.get_name() == "ARMAR-6::CoM_R");
    CHECK(right_hand_com.get_base_frame() == "ARMAR-6::TCP_R");
}

TEST_CASE("testing basic framed differences")
{
    SUBCASE("testing framed difference")
    {
        DummyLinearState const p{};  // Dummy position.
        DummyLinearState const d{};  // Dummy position.

        auto x = p - d;

        FramedDummyLinearState const tcp{p, {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
        FramedDummyLinearState const com{p, {.name = "CoM", .base_frame = "ARMAR-6::RobotRoot"}};

        // auto diff = pos2 - pos1;
        // const traits::difference_type_of<Test> ld{};

        FramedDummyLinearDiff const ld = tcp - com;
        // const traits::framed_type_of<DummyLinearDiff> diff{};
        // FramedDummyLinearDiff const diff{};
        //
        CHECK(ld.get_base_frame() == "CoM");
        framed_geometry::BaseChange const bc{.from_frame = "CoM",
                                             .to_frame = "ARMAR-6::PlatformBase",
                                             .transformation =
                                                 units::position::SpatialDisplacement::zero()};
        auto new_tcp = bc * ld;
        CHECK(new_tcp.get_base_frame() == bc.to_frame.data());
        // traits::framed_traits_of<units::position::Position>::basis_change_function(pos1.get_framed_object(),
        // bc);
    }
}

TEST_CASE("testing adjoint matrix")
{
    SUBCASE("Example 3.23 from Modern Robotics.")
    {
        Eigen::Isometry3d T_sb = Eigen::Isometry3d(
            (Eigen::Matrix4d() << -1, 0, 0, 4, 0, 1, 0, 0.4, 0, 0, -1, 0, 0, 0, 0, 1).finished());
        Eigen::Vector<double, 6> V_s = {0, 0, 2, -2, -4, 0};
        Eigen::Vector<double, 6> V_b = {0, 0, -2, 2.8, 4, 0};
        framed_geometry::Adjoint adjoint(T_sb);
        CHECK(V_s.isApprox(adjoint * V_b));
    }
    SUBCASE("Exercise 3.16 from Modern Robotics")
    {
        Eigen::Vector<double, 6> V_s = {3, 2, 1, -1, -2, -3};
        Eigen::Isometry3d T_as = Eigen::Isometry3d(
            (Eigen::Matrix4d() << 0, 0, 1, 0, -1, 0, 0, 3, 0, -1, 0, 0, 0, 0, 0, 1).finished());
        Eigen::Vector<double, 6> V_a = {1, -3, -2, -9, 1, -1};
        auto const adjoint = framed_geometry::Adjoint(T_as);
        Eigen::Matrix4d V =
            (Eigen::Matrix4d() << 0, -1, 2, -1, 1, 0, -3, -2, -2, 3, 0, -3, 0, 0, 0, 0).finished();
        CAPTURE(V_a);
        CAPTURE(V_s);
        CAPTURE(adjoint * V_s);
        CHECK(V_a.isApprox(adjoint * V_s));
        Eigen::Matrix4d V_a_matrix = (T_as * V * T_as.inverse()).matrix();
        CAPTURE(V_a_matrix);
        CAPTURE(framed_geometry::SkewSymmetric6d(V_a).matrix());
        CHECK(framed_geometry::SkewSymmetric6d(V_a).matrix().isApprox(V_a_matrix));
    }
}
