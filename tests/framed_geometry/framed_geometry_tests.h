#pragma once
#include <quant/framed_geometry.h>
#include "DummyLinearState.h"

#include <doctest/doctest.h>

#include <iostream>

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

    FramedDummyLinearDiff const robot_root =
        origin.enframe(DummyLinearDiff());

    CHECK(robot_root.get_base_frame() == "::Origin");

    FramedDummyLinearState const right_hand_tcp = origin.enframe(
        DummyLinearState(), "ARMAR-6::TCP_R");

    CHECK(right_hand_tcp.get_name() == "ARMAR-6::TCP_R");
    CHECK(right_hand_tcp.get_base_frame() == "::Origin");

    FramedDummySpatialState const right_hand_com = right_hand_tcp.enframe(
        DummySpatialState(), "ARMAR-6::CoM_R");

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
        CHECK(ld.get_base_frame() == "ARMAR-6::RobotRoot");
        framed_geometry::BaseChange const bc{.from_frame = "ARMAR-6::RobotRoot",
                                             .to_frame = "ARMAR-6::PlatformBase",
                                             .transformation =
                                             units::position::SpatialDisplacement::zero()};
        auto new_tcp = bc * ld;
        CHECK(new_tcp.get_base_frame() == bc.to_frame.data());
        // traits::framed_traits_of<units::position::Position>::basis_change_function(pos1.get_framed_object(), bc);
    }
}
