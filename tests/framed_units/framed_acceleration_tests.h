#include <quant/framed_units/acceleration.h>
#include <quant/geometry/Circa.h>
#include <quant/units/acceleration.h>

#include <doctest/doctest.h>

#include <iostream>

using namespace quant;  // NOLINT

TEST_SUITE("testing framed acceleration domain")
{
    TEST_CASE("testing framed linear accelerations")
    {
        SUBCASE("construction")
        {
            FramedLinearAcceleration const a1{
                LinearAcceleration::meters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedLinearAcceleration const a2 = FramedLinearAcceleration::zero({"::", "::"});
            FramedLinearAcceleration const a3{a1};

            CHECK(a1.get_name() == "TCP");
            CHECK(a1.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(a1.get_framed_object() ==
                  Circa(LinearAcceleration::meters_per_second_squared({.x = 1, .y = 2, .z = 3})));

            CHECK(a2.get_name() == "::");
            CHECK(a2.get_base_frame() == "::");
            CHECK(a2.get_framed_object() == Circa(LinearAcceleration::zero()));

            CHECK(a3.get_name() == "TCP");
            CHECK(a3.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(a3.get_framed_object() ==
                  Circa(LinearAcceleration::meters_per_second_squared({.x = 1, .y = 2, .z = 3})));
        }

        SUBCASE("subtraction")
        {
            FramedLinearAcceleration const a1{
                LinearAcceleration::meters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedLinearAcceleration const a2{
                LinearAcceleration::meters_per_second_squared({.x = 4, .y = 5, .z = 6}),
                {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};

            auto const diff = a2 - a1;

            CHECK(diff.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(diff.get_framed_object() ==
                  Circa(LinearAccelerationDifference::meters_per_second_squared(
                      {.x = 3, .y = 3, .z = 3})));
        }

        SUBCASE("base change - translation")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedLinearAcceleration const a1{
                LinearAcceleration::meters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                {.name = name, .base_frame = from_frame}};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0}))};

            auto a2 = bc * a1;

            CHECK(a2.get_name() == name);
            CHECK(a2.get_base_frame() == to_frame);
            CHECK(a2.get_framed_object() ==
                  Circa(LinearAcceleration::meters_per_second_squared({.x = 1, .y = 2, .z = 3})));
        }

        SUBCASE("base change - rotation")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedLinearAcceleration const a1{
                LinearAcceleration::meters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                {.name = name, .base_frame = from_frame}};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 0, .y = 0, .z = 0}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};

            auto a2 = bc * a1;

            CHECK(a2.get_name() == name);
            CHECK(a2.get_base_frame() == to_frame);
            CHECK(a2.get_framed_object() ==
                  Circa(LinearAcceleration::meters_per_second_squared({.x = 1, .y = 3, .z = -2})));
        }

        SUBCASE("base change - transform")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedLinearAcceleration const a1{
                LinearAcceleration::meters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                {.name = name, .base_frame = from_frame}};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};

            auto a2 = bc * a1;

            CHECK(a2.get_name() == name);
            CHECK(a2.get_base_frame() == to_frame);
            CHECK(a2.get_framed_object() ==
                  Circa(LinearAcceleration::meters_per_second_squared({.x = 1, .y = 3, .z = -2})));
        }
    }

    TEST_CASE("testing framed linear acceleration differences")
    {
        SUBCASE("construction")
        {
            FramedLinearAccelerationDifference const f1{
                LinearAccelerationDifference::meters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                "ARMAR-6::RobotRoot"};
            FramedLinearAccelerationDifference const f2 =
                FramedLinearAccelerationDifference::zero("::");
            FramedLinearAccelerationDifference const f3{f1};

            CHECK(f1.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(f1.get_framed_object() ==
                  Circa(LinearAccelerationDifference::meters_per_second_squared(
                      {.x = 1, .y = 2, .z = 3})));

            CHECK(f2.get_base_frame() == "::");
            CHECK(f2.get_framed_object() == Circa(LinearAccelerationDifference::zero()));

            CHECK(f3.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(f3.get_framed_object() ==
                  Circa(LinearAccelerationDifference::meters_per_second_squared(
                      {.x = 1, .y = 2, .z = 3})));
        }

        SUBCASE("addition from right to state")
        {
            FramedLinearAcceleration const acceleration{
                LinearAcceleration::meters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedLinearAccelerationDifference const lad{
                LinearAccelerationDifference::meters_per_second_squared({.x = 3, .y = 2, .z = 1}),
                "TCP"};
            FramedLinearAccelerationDifference const lad_wrong_frame{
                LinearAccelerationDifference::meters_per_second_squared({.x = 3, .y = 2, .z = 1}),
                "ARMAR-6::PlatformBase"};

            auto const new_acceleration = acceleration + lad;
            CHECK(new_acceleration.get_name() == "TCP");
            CHECK(new_acceleration.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(new_acceleration.get_framed_object() ==
                  Circa(LinearAcceleration::meters_per_second_squared({.x = 4, .y = 4, .z = 4})));

            std::string const exception_message =
                "Frame mismatch: TCP vs ARMAR-6::PlatformBase";
            CHECK_THROWS_WITH(acceleration + lad_wrong_frame, exception_message.c_str());
        }

        SUBCASE("base change - translation")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedLinearAccelerationDifference const f1{
                LinearAccelerationDifference::meters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                from_frame};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0}))};
            WARN_NOTHROW(bc * f1);
        }

        SUBCASE("base change - angular")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedLinearAccelerationDifference const f1{
                LinearAccelerationDifference::meters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                from_frame};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 0, .y = 0, .z = 0}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};
            WARN_NOTHROW(bc * f1);
        }

        SUBCASE("base change - transform")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedLinearAccelerationDifference const f1{
                LinearAccelerationDifference::meters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                from_frame};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};
            WARN_NOTHROW(bc * f1);
        }

        SUBCASE("base change - wrong frame")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedLinearAccelerationDifference const f1{
                LinearAccelerationDifference::meters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                from_frame};

            BaseChange const bc{
                .from_frame = "something else",
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0}))};

            std::string const exception_message =
                "Frame mismatch: something else vs " + std::string(from_frame);
            CHECK_THROWS_WITH(bc * f1, exception_message.c_str());
        }

        SUBCASE("base change - difference of changed states is changed difference")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const base_frame = "ARMAR-6::RobotRoot";
            std::string const tcp_r = "ARMAR-6::TCP_R";
            std::string const tcp_l = "ARMAR-6::TCP_L";
            std::string const camera = "ARMAR-6::Camera";
            FramedLinearAcceleration const a1{
                LinearAcceleration::meters_per_second_squared({.x = 1, .y = 0, .z = 0}),
                {.name = tcp_r, .base_frame = base_frame}};
            FramedLinearAcceleration const a2{
                LinearAcceleration::meters_per_second_squared({.x = 0, .y = 1, .z = 0}),
                {.name = tcp_l, .base_frame = base_frame}};
            FramedLinearAccelerationDifference const lad_in_a1 = a2 - a1;

            BaseChange const from_base_to_camera{
                .from_frame = base_frame,
                .to_frame = camera,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};
            auto const a1_in_camera = from_base_to_camera * a1;
            auto const a2_in_camera = from_base_to_camera * a2;
            auto const lad_in_a1_camera = a2_in_camera - a1_in_camera;
            WARN(lad_in_a1 == Circa(lad_in_a1_camera)); // TODO: why is this not the case??
            WARN(a1_in_camera + lad_in_a1 == Circa(a2_in_camera));
        }
    }

    TEST_CASE("testing framed angular accelerations")
    {
        SUBCASE("construction")
        {
            FramedAngularAcceleration const f1{AngularAcceleration::degrees_per_second_squared(
                                                   {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                                               {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedAngularAcceleration const f2 = FramedAngularAcceleration::zero({"::", "::"});
            FramedAngularAcceleration const f3{f1};

            CHECK(f1.get_name() == "TCP");
            CHECK(f1.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(f1.get_framed_object() == Circa(AngularAcceleration::degrees_per_second_squared(
                                                {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})));

            CHECK(f2.get_name() == "::");
            CHECK(f2.get_base_frame() == "::");
            CHECK(f2.get_framed_object() == Circa(AngularAcceleration::zero()));

            CHECK(f3.get_name() == "TCP");
            CHECK(f3.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(f3.get_framed_object() == Circa(AngularAcceleration::degrees_per_second_squared(
                                                {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})));
        }

        SUBCASE("subtraction")
        {
            FramedAngularAcceleration const f1{AngularAcceleration::degrees_per_second_squared(
                                                   {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                                               {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedAngularAcceleration const f2{AngularAcceleration::degrees_per_second_squared(
                                                   {.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}),
                                               {.name = "CoM", .base_frame = "ARMAR-6::RobotRoot"}};

            auto const diff = f2 - f1;

            CHECK(diff.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(diff.get_framed_object() ==
                  Circa(AngularAccelerationDifference::degrees_per_second_squared(
                      {.axis = {.x = -1 / sqrt(2), .y = 1 / sqrt(2), .z = 0},
                       .angle = sqrt(2) * 90})));
        }

        SUBCASE("base change - rotation")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedAngularAcceleration const f1{AngularAcceleration::degrees_per_second_squared(
                                                   {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                                               {.name = name, .base_frame = from_frame}};

            BaseChange const bc{.from_frame = from_frame,
                                .to_frame = to_frame,
                                .transformation = SpatialDisplacement(
                                    LinearDisplacement::zero(),
                                    AngularDisplacement::degrees(
                                        {.axis = {.x = 0, .y = 1, .z = 0}, .angle = 270}))};
            auto f2 = bc * f1;

            CHECK(f2.get_name() == name);
            CHECK(f2.get_base_frame() == to_frame);
            CHECK(f2.get_framed_object() == Circa(AngularAcceleration::degrees_per_second_squared(
                                                {.axis = {.x = 0, .y = 0, .z = -1}, .angle = 90})));
        }
    }

    TEST_CASE("testing framed angular acceleration differences")
    {
        SUBCASE("construction")
        {
            FramedAngularAccelerationDifference const f1{
                AngularAccelerationDifference::degrees_per_second_squared(
                    {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                "ARMAR-6::RobotRoot"};
            FramedAngularAccelerationDifference const f2 =
                FramedAngularAccelerationDifference::zero("::");
            FramedAngularAccelerationDifference const f3{f1};

            CHECK(f1.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(f1.get_framed_object() ==
                  Circa(AngularAccelerationDifference::degrees_per_second_squared(
                      {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})));

            CHECK(f2.get_base_frame() == "::");
            CHECK(f2.get_framed_object() == Circa(AngularAccelerationDifference::zero()));

            CHECK(f3.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(f3.get_framed_object() ==
                  Circa(AngularAccelerationDifference::degrees_per_second_squared(
                      {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})));
        }

        SUBCASE("addition from right to state")
        {
            FramedAngularAcceleration const acceleration{
                AngularAcceleration::degrees_per_second_squared(
                    {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedAngularAccelerationDifference const aad{
                AngularAccelerationDifference::degrees_per_second_squared(
                    {.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}),
                "TCP"};
            FramedAngularAccelerationDifference const aad_wrong_frame{
                AngularAccelerationDifference::degrees_per_second_squared(
                    {.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}),
                "ARMAR-6::PlatformBase"};

            auto const new_acceleration = acceleration + aad;
            CHECK(new_acceleration.get_name() == "TCP");
            CHECK(new_acceleration.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(new_acceleration.get_framed_object() ==
                  Circa(AngularAcceleration::degrees_per_second_squared(
                      {.axis = {.x = 1 / sqrt(2), .y = 1 / sqrt(2), .z = 0},
                       .angle = sqrt(2) * 90})));

            std::string const exception_message =
                "Frame mismatch: TCP vs ARMAR-6::PlatformBase";
            CHECK_THROWS_WITH(acceleration + aad_wrong_frame, exception_message.c_str());
        }

        SUBCASE("base change - translation")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            FramedAngularAccelerationDifference const f1{
                AngularAccelerationDifference::degrees_per_second_squared(
                    {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                from_frame};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0}))};
            WARN_NOTHROW(bc * f1);
        }

        SUBCASE("base change - angular")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            FramedAngularAccelerationDifference const f1{
                AngularAccelerationDifference::degrees_per_second_squared(
                    {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                from_frame};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::zero(),
                    AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}))};
            WARN_NOTHROW(bc * f1);
        }

        SUBCASE("base change - transform")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            FramedAngularAccelerationDifference const f1{
                AngularAccelerationDifference::degrees_per_second_squared(
                    {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                from_frame};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}))};
            WARN_NOTHROW(bc * f1);
        }

        SUBCASE("base change - wrong frame")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            FramedAngularAccelerationDifference const f1{
                AngularAccelerationDifference::degrees_per_second_squared(
                    {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}),
                from_frame};

            BaseChange const bc{
                .from_frame = "something else",
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0}))};

            std::string const exception_message =
                "Frame mismatch: something else vs " + std::string(from_frame);
            CHECK_THROWS_WITH(bc * f1, exception_message.c_str());
        }

        SUBCASE("base change - difference of changed states is changed difference")
        {
            std::string const base_frame = "ARMAR-6::RobotRoot";
            std::string const tcp_r = "ARMAR-6::TCP_R";
            std::string const tcp_l = "ARMAR-6::TCP_L";
            std::string const camera = "ARMAR-6::Camera";
            FramedAngularAcceleration const a1{AngularAcceleration::degrees_per_second_squared(
                                                   {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0}),
                                               {.name = tcp_r, .base_frame = base_frame}};
            FramedAngularAcceleration const a2{AngularAcceleration::degrees_per_second_squared(
                                                   {.axis = {.x = 0, .y = 1, .z = 0}, .angle = 0}),
                                               {.name = tcp_l, .base_frame = base_frame}};
            FramedAngularAccelerationDifference const aad_in_base = a2 - a1;

            BaseChange const from_base_to_camera{
                .from_frame = base_frame,
                .to_frame = camera,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};
            auto const a1_in_camera = from_base_to_camera * a1;
            auto const a2_in_camera = from_base_to_camera * a2;
            auto const aad_in_camera = a2_in_camera - a1_in_camera;
            WARN_NOTHROW(from_base_to_camera * aad_in_base != Circa(aad_in_camera));
        }
    }

    TEST_CASE("testing framed spatial accelerations")
    {
        SUBCASE("construction")
        {
            FramedSpatialAcceleration const a1{
                SpatialAcceleration(
                    LinearAcceleration::millimeters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                    AngularAcceleration::degrees_per_second_squared(
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                {.name = "TCP", .base_frame = "ARMAR-6::RobotRoot"}};
            FramedSpatialAcceleration const a2 = FramedSpatialAcceleration::zero({"::", "::"});
            FramedSpatialAcceleration const a3{a1};

            CHECK(a1.get_name() == "TCP");
            CHECK(a1.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(a1.get_framed_object() ==
                  Circa(SpatialAcceleration(
                      LinearAcceleration::millimeters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                      AngularAcceleration::degrees_per_second_squared(
                          {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))));

            CHECK(a2.get_name() == "::");
            CHECK(a2.get_base_frame() == "::");
            CHECK(a2.get_framed_object() == Circa(SpatialAcceleration::zero()));

            CHECK(a3.get_name() == "TCP");
            CHECK(a3.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(a3.get_framed_object() ==
                  Circa(SpatialAcceleration(
                      LinearAcceleration::millimeters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                      AngularAcceleration::degrees_per_second_squared(
                          {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))));
        }

        SUBCASE("subtraction")
        {
            // TODO: implement subtraction
        }

        SUBCASE("base change - translation")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedSpatialAcceleration const a1{
                SpatialAcceleration(
                    LinearAcceleration::millimeters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                    AngularAcceleration::degrees_per_second_squared(
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                {.name = name, .base_frame = from_frame}};

            BaseChange const bc{.from_frame = from_frame,
                                .to_frame = to_frame,
                                .transformation = SpatialDisplacement(
                                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                                    AngularDisplacement::zero())};

            auto a2 = bc * a1;

            CHECK(a2.get_name() == name);
            CHECK(a2.get_base_frame() == to_frame);
            CHECK(a2.get_framed_object() ==
                  Circa(SpatialAcceleration(
                      LinearAcceleration::millimeters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                      AngularAcceleration::degrees_per_second_squared(
                          {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))));
        }

        SUBCASE("base change - rotation")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedSpatialAcceleration const a1{
                SpatialAcceleration(
                    LinearAcceleration::millimeters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                    AngularAcceleration::degrees_per_second_squared(
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                {.name = name, .base_frame = from_frame}};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 0, .y = 0, .z = 0}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};

            auto a2 = bc * a1;

            CHECK(a2.get_name() == name);
            CHECK(a2.get_base_frame() == to_frame);
            CHECK(a2.get_framed_object() ==
                  Circa(SpatialAcceleration(
                      LinearAcceleration::millimeters_per_second_squared({.x = 1, .y = 3, .z = -2}),
                      AngularAcceleration::degrees_per_second_squared(
                          {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))));
        }

        SUBCASE("base change - transform")
        {
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            std::string const name = "TCP";
            FramedSpatialAcceleration const a1{
                SpatialAcceleration(
                    LinearAcceleration::millimeters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                    AngularAcceleration::degrees_per_second_squared(
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                {.name = name, .base_frame = from_frame}};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};

            auto a2 = bc * a1;

            CHECK(a2.get_name() == name);
            CHECK(a2.get_base_frame() == to_frame);
            CHECK(a2.get_framed_object() ==
                  Circa(SpatialAcceleration(
                      LinearAcceleration::millimeters_per_second_squared({.x = 1, .y = 3, .z = -2}),
                      AngularAcceleration::degrees_per_second_squared(
                          {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))));
        }
    }

    TEST_CASE("testing framed spatial acceleration differences")
    {
        SUBCASE("construction")
        {
            FramedSpatialAccelerationDifference const f1{
                SpatialAccelerationDifference(
                    LinearAccelerationDifference::meters_per_second_squared(
                        {.x = 1, .y = 2, .z = 3}),
                    AngularAccelerationDifference::degrees_per_second_squared(
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                "ARMAR-6::RobotRoot"};
            FramedSpatialAccelerationDifference const f2 =
                FramedSpatialAccelerationDifference::zero("::");
            FramedSpatialAccelerationDifference const f3{f1};

            CHECK(f1.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(f1.get_framed_object() ==
                  Circa(SpatialAccelerationDifference(
                      LinearAccelerationDifference::meters_per_second_squared(
                          {.x = 1, .y = 2, .z = 3}),
                      AngularAccelerationDifference::degrees_per_second_squared(
                          {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))));

            CHECK(f2.get_base_frame() == "::");
            CHECK(f2.get_framed_object() == Circa(SpatialAccelerationDifference::zero()));

            CHECK(f3.get_base_frame() == "ARMAR-6::RobotRoot");
            CHECK(f3.get_framed_object() ==
                  Circa(SpatialAccelerationDifference(
                      LinearAccelerationDifference::meters_per_second_squared(
                          {.x = 1, .y = 2, .z = 3}),
                      AngularAccelerationDifference::degrees_per_second_squared(
                          {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))));
        }

        SUBCASE("base change - translation")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            FramedSpatialAccelerationDifference const f1{
                SpatialAccelerationDifference(
                    LinearAccelerationDifference::meters_per_second_squared(
                        {.x = 1, .y = 2, .z = 3}),
                    AngularAccelerationDifference::degrees_per_second_squared(
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                from_frame};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0}))};
            WARN_NOTHROW(bc * f1);
        }

        SUBCASE("base change - angular")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            FramedSpatialAccelerationDifference const f1{
                SpatialAccelerationDifference(
                    LinearAccelerationDifference::meters_per_second_squared(
                        {.x = 1, .y = 2, .z = 3}),
                    AngularAccelerationDifference::degrees_per_second_squared(
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                from_frame};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::zero(),
                    AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}))};
            WARN_NOTHROW(bc * f1);
        }

        SUBCASE("base change - transform")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            FramedSpatialAccelerationDifference const f1{
                SpatialAccelerationDifference(
                    LinearAccelerationDifference::meters_per_second_squared(
                        {.x = 1, .y = 2, .z = 3}),
                    AngularAccelerationDifference::degrees_per_second_squared(
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                from_frame};

            BaseChange const bc{
                .from_frame = from_frame,
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}))};
            WARN_NOTHROW(bc * f1);
        }

        SUBCASE("base change - wrong frame")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const from_frame = "ARMAR-6::RobotRoot";
            std::string const to_frame = "ARMAR-6::TCP_R";
            FramedSpatialAccelerationDifference const f1{
                SpatialAccelerationDifference(
                    LinearAccelerationDifference::meters_per_second_squared(
                        {.x = 1, .y = 2, .z = 3}),
                    AngularAccelerationDifference::degrees_per_second_squared(
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})),
                from_frame};

            BaseChange const bc{
                .from_frame = "something else",
                .to_frame = to_frame,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0}))};

            std::string const exception_message =
                "Frame mismatch: something else vs " + std::string(from_frame);
            CHECK_THROWS_WITH(bc * f1, exception_message.c_str());
        }

        SUBCASE("base change - difference of changed states is changed difference")
        {
            // TODO: NOT IMPLEMENTED YET
            std::string const base_frame = "ARMAR-6::RobotRoot";
            std::string const tcp_r = "ARMAR-6::TCP_R";
            std::string const tcp_l = "ARMAR-6::TCP_L";
            std::string const camera = "ARMAR-6::Camera";
            FramedSpatialAcceleration const a1{
                SpatialAcceleration(
                    LinearAcceleration::millimeters_per_second_squared({.x = 1, .y = 2, .z = 3}),
                    AngularAcceleration::degrees_per_second_squared(
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0})),
                {.name = tcp_r, .base_frame = base_frame}};
            FramedSpatialAcceleration const a2{
                SpatialAcceleration(
                    LinearAcceleration::millimeters_per_second_squared({.x = 10, .y = 9, .z = 8}),
                    AngularAcceleration::degrees_per_second_squared(
                        {.axis = {.x = 0, .y = 1, .z = 0}, .angle = 0})),
                {.name = tcp_l, .base_frame = base_frame}};
            FramedSpatialAccelerationDifference const sad_in_a1 = a2 - a1;

            BaseChange const from_base_to_camera{
                .from_frame = base_frame,
                .to_frame = camera,
                .transformation = SpatialDisplacement(
                    LinearDisplacement::millimeters({.x = 3, .y = 2, .z = 1}),
                    AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))};
            auto const a1_in_camera = from_base_to_camera * a1;
            auto const a2_in_camera = from_base_to_camera * a2;
            auto const sad_in_camera = a2_in_camera - a1_in_camera;
            WARN(sad_in_a1 == Circa(sad_in_camera));
            WARN(a1_in_camera + sad_in_a1 == Circa(a2_in_camera));
        }
    }
}