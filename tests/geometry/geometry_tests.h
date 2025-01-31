#pragma once

#include <quant/units/acceleration.h>
#include <quant/units/position.h>
#include <quant/units/time.h>
#include <quant/units/velocity.h>

#include <doctest/doctest.h>

#include <type_traits>

#include "quant/geometry/Circa.h"

namespace quant::traits::arithmetics
{
    namespace addition
    {
        template <typename T, typename U>
        class is_possible
        {
            template <typename X, typename Y>
            static auto
            test(int) -> decltype(std::declval<X>() + std::declval<Y>(), std::true_type());

            template <typename, typename>
            static std::false_type
            test(...);

        public:
            static constexpr bool value = decltype(test<T, U>(0))::value;
        };

        template <typename T, typename U>
        inline constexpr bool is_possible_v = is_possible<T, U>::value;

        template <typename T, typename U>
        class is_possible_inplace
        {
            template <typename X, typename Y>
            static auto
            test_inplace(int)
                -> decltype(std::declval<X&>() += std::declval<Y>(), std::true_type());

            template <typename, typename>
            static std::false_type
            test_inplace(...);

        public:
            static constexpr bool value = decltype(test_inplace<T, U>(0))::value;
        };

        template <typename T, typename U>
        inline constexpr bool is_possible_inplace_v = is_possible_inplace<T, U>::value;
    }  // namespace addition

    namespace subtraction
    {
        template <typename T, typename U>
        class is_possible
        {
            template <typename X, typename Y>
            static auto
            test(int) -> decltype(std::declval<X>() - std::declval<Y>(), std::true_type());

            template <typename, typename>
            static std::false_type
            test(...);

        public:
            static constexpr bool value = decltype(test<T, U>(0))::value;
        };

        template <typename T, typename U>
        inline constexpr bool is_possible_v = is_possible<T, U>::value;

        template <typename T, typename U>
        class is_possible_inplace
        {
            template <typename X, typename Y>
            static auto
            test_inplace(int)
                -> decltype(std::declval<X&>() -= std::declval<Y>(), std::true_type());

            template <typename, typename>
            static std::false_type
            test_inplace(...);

        public:
            static constexpr bool value = decltype(test_inplace<T, U>(0))::value;
        };

        template <typename T, typename U>
        inline constexpr bool is_possible_inplace_v = is_possible_inplace<T, U>::value;
    }  // namespace subtraction

    namespace multiplication
    {
        template <typename T, typename U>
        class is_possible
        {
            template <typename X, typename Y>
            static auto
            test(int) -> decltype(std::declval<X>() * std::declval<Y>(), std::true_type());

            template <typename, typename>
            static std::false_type
            test(...);

        public:
            static constexpr bool value = decltype(test<T, U>(0))::value;
        };

        template <typename T, typename U>
        inline constexpr bool is_possible_v = is_possible<T, U>::value;

        template <typename T, typename U>
        class is_possible_inplace
        {
            template <typename X, typename Y>
            static auto
            test_inplace(int)
                -> decltype(std::declval<X&>() *= std::declval<Y>(), std::true_type());

            template <typename, typename>
            static std::false_type
            test_inplace(...);

        public:
            static constexpr bool value = decltype(test_inplace<T, U>(0))::value;
        };

        template <typename T, typename U>
        inline constexpr bool is_possible_inplace_v = is_possible_inplace<T, U>::value;
    }  // namespace multiplication

    namespace division
    {
        template <typename T, typename U>
        class is_possible
        {
            template <typename X, typename Y>
            static auto
            test(int) -> decltype(std::declval<X>() / std::declval<Y>(), std::true_type());

            template <typename, typename>
            static std::false_type
            test(...);

        public:
            static constexpr bool value = decltype(test<T, U>(0))::value;
        };

        template <typename T, typename U>
        inline constexpr bool is_possible_v = is_possible<T, U>::value;

        template <typename T, typename U>
        class is_possible_inplace
        {
            template <typename X, typename Y>
            static auto
            test_inplace(int)
                -> decltype(std::declval<X&>() /= std::declval<Y>(), std::true_type());

            template <typename, typename>
            static std::false_type
            test_inplace(...);

        public:
            static constexpr bool value = decltype(test_inplace<T, U>(0))::value;
        };

        template <typename T, typename U>
        inline constexpr bool is_possible_inplace_v = is_possible_inplace<T, U>::value;
    }  // namespace division

    template <typename StateT, typename DifferenceT>
    void
    check_arithmetics()
    {
        SUBCASE("math operators are defined for State vs State")
        {
            // State with State
            static_assert(not addition::is_possible_v<StateT, StateT>,
                          "State types should not be addable");
            static_assert(not addition::is_possible_inplace_v<StateT, StateT>,
                          "State types should not be addable inplace");
            static_assert(subtraction::is_possible_v<StateT, StateT>,
                          "State types should not be subtractable");
            static_assert(not subtraction::is_possible_inplace_v<StateT, StateT>,
                          "State types should not be subtractable inplace");
            static_assert(not multiplication::is_possible_v<StateT, StateT>,
                          "State types should not be multiplicative");
            static_assert(not multiplication::is_possible_inplace_v<StateT, StateT>,
                          "State types should not be multiplicative inplace");
            // static_assert(division::is_possible_v<StateT, StateT>,
            //               "State types should be dividable");
            static_assert(not division::is_possible_inplace_v<StateT, StateT>,
                          "State types should not be dividable inplace");
        }
        SUBCASE("math operators are defined for State vs Difference")
        {
            // State with Difference
            static_assert(addition::is_possible_v<StateT, DifferenceT>,
                          "State and Difference types should be addable");
            static_assert(addition::is_possible_inplace_v<StateT, DifferenceT>,
                          "State and Difference types should be addable inplace");
            static_assert(subtraction::is_possible_v<StateT, DifferenceT>,
                          "State and Difference types should be subtractable");
            static_assert(subtraction::is_possible_inplace_v<StateT, DifferenceT>,
                          "State and Difference types should be subtractable inplace");
            static_assert(not multiplication::is_possible_v<StateT, DifferenceT>,
                          "State and Difference types should not be multiplicative");
            static_assert(not multiplication::is_possible_inplace_v<StateT, DifferenceT>,
                          "State and Difference types should not be multiplicative inplace");
            static_assert(not division::is_possible_v<StateT, DifferenceT>,
                          "State and Difference types should not be dividable");
            static_assert(not division::is_possible_inplace_v<StateT, DifferenceT>,
                          "State and Difference types should not be dividable inplace");
        }
        SUBCASE("math operators are defined for Difference vs State")
        {
            // Difference with State
            static_assert(not addition::is_possible_v<DifferenceT, StateT>,
                          "Difference and State types should not be addable");
            static_assert(not addition::is_possible_inplace_v<DifferenceT, StateT>,
                          "Difference and State types should not be addable inplace");
            static_assert(not subtraction::is_possible_v<DifferenceT, StateT>,
                          "Difference and State types should not be subtractable");
            static_assert(not subtraction::is_possible_inplace_v<DifferenceT, StateT>,
                          "Difference and State types should not be subtractable inplace");
            static_assert(not multiplication::is_possible_v<DifferenceT, StateT>,
                          "Difference and State types should not be multiplicative");
            static_assert(not multiplication::is_possible_inplace_v<DifferenceT, StateT>,
                          "Difference and State types should not be multiplicative inplace");
            static_assert(not division::is_possible_v<DifferenceT, StateT>,
                          "Difference and State types should not be dividable");
            static_assert(not division::is_possible_inplace_v<DifferenceT, StateT>,
                          "Difference and State types should not be dividable inplace");
        }
        SUBCASE("math operators are defined for Difference vs Difference")
        {
            // Difference with Difference
#ifdef QUANT_ENABLE_DIFFERENCE_ADDITION
            static_assert(addition::is_possible_v<DifferenceT, DifferenceT>,
                          "Difference and Difference types should be addable");
            static_assert(addition::is_possible_inplace_v<DifferenceT, DifferenceT>,
                          "Difference and Difference types should be addable inplace");
            static_assert(subtraction::is_possible_v<DifferenceT, DifferenceT>,
                          "Difference and Difference types should be subtractable");
            static_assert(subtraction::is_possible_inplace_v<DifferenceT, DifferenceT>,
                          "Difference and Difference types should be subtractable inplace");
#else
            static_assert(not addition::is_possible_v<DifferenceT, DifferenceT>,
                          "Difference and Difference types should be addable");
            static_assert(not addition::is_possible_inplace_v<DifferenceT, DifferenceT>,
                          "Difference and Difference types should be addable inplace");
            static_assert(not subtraction::is_possible_v<DifferenceT, DifferenceT>,
                          "Difference and Difference types should be subtractable");
            static_assert(not subtraction::is_possible_inplace_v<DifferenceT, DifferenceT>,
                          "Difference and Difference types should be subtractable inplace");
#endif
            static_assert(not multiplication::is_possible_v<DifferenceT, DifferenceT>,
                          "Difference and Difference types should not be multiplicative");
            static_assert(not multiplication::is_possible_inplace_v<DifferenceT, DifferenceT>,
                          "Difference and Difference types should not be multiplicative inplace");
            // static_assert(division::is_possible_v<DifferenceT, DifferenceT>,
            //               "Difference and Difference types should be dividable"); TODO: this
            //               should only be possible partially (e.g. not for poses or orientations)
            static_assert(not division::is_possible_inplace_v<DifferenceT, DifferenceT>,
                          "Difference and Difference types should not be dividable inplace");
        }
        auto state = StateT();
        auto diff = DifferenceT();
        state += diff;
        state -= diff;
        state + diff;
        state - diff;

#ifdef QUANT_ENABLE_DIFFERENCE_ADDITION
        diff + diff;
        diff += diff;
        diff - diff;
        diff -= diff;
#endif
    }

    template <typename Quantity1, typename Quantity2>
    void
    check_differing_domains()
    {
        static_assert(not addition::is_possible_v<Quantity1, Quantity2>,
                      "Different domains should not be addable");
        static_assert(not addition::is_possible_inplace_v<Quantity1, Quantity2>,
                      "Different domains should not be addable inplace");
        static_assert(not subtraction::is_possible_v<Quantity1, Quantity2>,
                      "Different domains should not be subtractable");
        static_assert(not subtraction::is_possible_inplace_v<Quantity1, Quantity2>,
                      "Different domains should not be subtractable inplace");
        static_assert(not multiplication::is_possible_v<Quantity1, Quantity2>,
                      "Different domains should not be multiplicative");
        static_assert(not multiplication::is_possible_inplace_v<Quantity1, Quantity2>,
                      "Different domains should not be multiplicative inplace");
        static_assert(not division::is_possible_v<Quantity1, Quantity2>,
                      "Different domains should not be dividable");
        static_assert(not division::is_possible_inplace_v<Quantity1, Quantity2>,
                      "Different domains should not be dividable inplace");
    }
}  // namespace quant::traits::arithmetics

using namespace quant;

TEST_SUITE("concrete instantiation using position")
{
    TEST_CASE("check arithmetics for TimePoint and Duration -- R1")
    {
        traits::arithmetics::check_arithmetics<TimePoint, Duration>();
    }
    TEST_CASE("check arithmetics for Position and LinearDisplacement -- R3")
    {
        traits::arithmetics::check_arithmetics<Position, LinearDisplacement>();
    }
    TEST_CASE("check arithmetics for Orientation and AngularDisplacement -- SO3")
    {
        traits::arithmetics::check_arithmetics<Orientation, AngularDisplacement>();
    }
    TEST_CASE("check arithmetics for Pose and SpatialDisplacement -- SE3")
    {
        traits::arithmetics::check_arithmetics<Pose, SpatialDisplacement>();
    }
    TEST_CASE("check different domains cannot interact")
    {
        traits::arithmetics::check_differing_domains<Position, Orientation>();
        traits::arithmetics::check_differing_domains<Position, Pose>();
        traits::arithmetics::check_differing_domains<Position, AngularDisplacement>();
        traits::arithmetics::check_differing_domains<Position, SpatialDisplacement>();

        traits::arithmetics::check_differing_domains<Orientation, Pose>();
        traits::arithmetics::check_differing_domains<Orientation, LinearDisplacement>();
        traits::arithmetics::check_differing_domains<Orientation, SpatialDisplacement>();

        traits::arithmetics::check_differing_domains<Pose, LinearDisplacement>();
        traits::arithmetics::check_differing_domains<Pose, AngularDisplacement>();

        traits::arithmetics::check_differing_domains<Position, LinearVelocity>();
        traits::arithmetics::check_differing_domains<Position, AngularVelocity>();
        traits::arithmetics::check_differing_domains<Position, LinearAcceleration>();
        traits::arithmetics::check_differing_domains<Position, AngularAcceleration>();
    }
    TEST_CASE("geometric objects are copy-assignable")
    {
        Position p1 = Position::millimeters({.x = 1, .y = 2, .z = 3});
        Position p2 = Position::millimeters({.x = 42, .y = 42, .z = 42});

        SUBCASE("states are copy-assignable")
        {
            CHECK(p1 == Position::millimeters({.x = 1, .y = 2, .z = 3}));
            CHECK(p2 == Position::millimeters({.x = 42, .y = 42, .z = 42}));

            p1 = p2;

            CHECK(p1 == Position::millimeters({.x = 42, .y = 42, .z = 42}));
            CHECK(p2 == Position::millimeters({.x = 42, .y = 42, .z = 42}));

            p1 = Position::millimeters({.x = 2});

            CHECK(p1 == Position::millimeters({.x = 2, .y = 0, .z = 0}));
            CHECK(p2 == Position::millimeters({.x = 42, .y = 42, .z = 42}));
        }

        LinearDisplacement ld1{p1};
        LinearDisplacement ld2{p2};

        SUBCASE("differences are copy-assignable")
        {
            CHECK(ld1 == LinearDisplacement::millimeters({.x = 1, .y = 2, .z = 3}));
            CHECK(ld2 == LinearDisplacement::millimeters({.x = 42, .y = 42, .z = 42}));

            ld1 = ld2;

            CHECK(ld1 == LinearDisplacement::millimeters({.x = 42, .y = 42, .z = 42}));
            CHECK(ld2 == LinearDisplacement::millimeters({.x = 42, .y = 42, .z = 42}));

            ld1 = LinearDisplacement::millimeters({.x = 2});

            CHECK(ld1 == LinearDisplacement::millimeters({.x = 2, .y = 0, .z = 0}));
            CHECK(ld2 == LinearDisplacement::millimeters({.x = 42, .y = 42, .z = 42}));
        }
    }

    TEST_CASE("Scalar states subtraction is a difference")
    {
        Position const p1 = Position::millimeters({.x = 1, .y = 2, .z = 3});
        Position const p2 = Position::millimeters({.x = 42, .y = 42, .z = 42});

        namespace traits = traits::arithmetics;

        // TODO: Tests for scaling with float, double, long double, int, long, long lonng
        // TODO: Tests for negation

        LinearDisplacement const diff = p2 - p1;
        CHECK(diff == LinearDisplacement::millimeters({41, 40, 39}));

        auto const p3 = p1 + diff;
        CHECK(p3 == p2);

        auto p5 = p2 - diff;
        // const auto p6 = diff - p1; << This should not compile
        CHECK(p5 == p1);
        p5 += diff;
        CHECK(p5 == p2);
        p5 -= diff;
        CHECK(p5 == p1);
    }
}

TEST_SUITE("subtraction state from state")
{
    TEST_CASE("scalar state and difference")
    {
        TimePoint t1 = TimePoint::seconds(1);
        TimePoint t2 = TimePoint::seconds(2);
        Duration const dt = t2 - t1;
        CHECK(dt == Duration::seconds(1));
        CHECK(t1 + dt == t2);
        CHECK(t2 - dt == t1);
    }

    TEST_CASE("linear state and difference")
    {
        Position p1 = Position::meters({.x = 1, .y = 2, .z = 3});
        Position p2 = Position::meters({.x = 4, .y = 5, .z = 6});
        LinearDisplacement const dp = p2 - p1;
        CHECK(dp == LinearDisplacement::meters({.x = 3, .y = 3, .z = 3}));
        CHECK(p1 + dp == p2);
        CHECK(p2 - dp == p1);
    }

    TEST_CASE("angular state and difference")
    {
        auto test_angular_aa =
            [](AxisAngle const& a, AxisAngle const& b, AxisAngle const& difference)
        {
            Orientation o1 = Orientation::degrees(a);
            Orientation o2 = Orientation::degrees(b);
            AngularDisplacement const dori = o2 - o1;
            AngularDisplacement const target_dori = AngularDisplacement::degrees(difference);
            CHECK_MESSAGE(dori == Circa(target_dori),
                          o1.to_string(),
                          o2.to_string(),
                          dori.to_string(),
                          target_dori.to_string());
            CHECK_MESSAGE((o1 + dori) == Circa(o2),
                          o1.to_string(),
                          o2.to_string(),
                          (o1 + dori).to_string(),
                          dori.to_string());
            CHECK_MESSAGE((o2 - dori) == Circa(o1),
                          o1.to_string(),
                          o2.to_string(),
                          (o2 - dori).to_string(),
                          dori.to_string());
        };
        auto test_angular_quat = [](Eigen::Quaterniond const& a,
                                    Eigen::Quaterniond const& b,
                                    Eigen::Quaterniond const& difference)
        {
            Orientation o1 = Orientation::degrees(a);
            Orientation o2 = Orientation::degrees(b);
            AngularDisplacement const dori = o2 - o1;
            CHECK_MESSAGE(dori == Circa(AngularDisplacement::degrees(difference)),
                          o1.to_string(),
                          o2.to_string(),
                          dori.to_string(),
                          AngularDisplacement::degrees(difference).to_string());
            CHECK_MESSAGE((o1 + dori) == Circa(o2),
                          o1.to_string(),
                          o2.to_string(),
                          (o1 + dori).to_string(),
                          dori.to_string());
            CHECK_MESSAGE((o2 - dori) == Circa(o1),
                          o1.to_string(),
                          o2.to_string(),
                          (o2 - dori).to_string(),
                          dori.to_string());
        };

        test_angular_aa({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0},
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0},
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0});
        test_angular_aa({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0},
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90},
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90});
        test_angular_aa({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 45},
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = -45},
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = -90});
        test_angular_aa(
            {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90},
            {.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90},
            {.axis = {.x = -1 / sqrt(3), .y = 1 / sqrt(3), .z = -1 / sqrt(3)}, .angle = 120});

        // TODO: This doesn't work as it should as the same angle can be represented by two
        // different quaternions
        test_angular_aa({.axis = {.x = 0, .y = 0, .z = 1}, .angle = 360},
                        {.axis = {.x = 0, .y = 0, .z = 1}, .angle = 10},
                        {.axis = {.x = 0, .y = 0, .z = 1}, .angle = 10});
        test_angular_quat(Eigen::Quaterniond::Identity(),
                          Eigen::Quaterniond(1, 0, 0, 0),
                          Eigen::Quaterniond(1, 0, 0, 0));
        test_angular_quat(Eigen::Quaterniond(sqrt(2) / 2, sqrt(2) / 2, 0, 0),
                          Eigen::Quaterniond(sqrt(2) / 2, 0, sqrt(2) / 2, 0),
                          Eigen::Quaterniond(0.5, -0.5, 0.5, -0.5));
        test_angular_quat(Eigen::Quaterniond(sqrt(2) / 2, 0, 0, sqrt(2) / 2),
                          Eigen::Quaterniond(sqrt(2) / 2, 0, 0, -sqrt(2) / 2),
                          Eigen::Quaterniond(0, 0, 0, -1));
    }

    TEST_CASE("spatial state and difference")
    {
        auto test_spatial_aa =
            [](AxisAngle const& a, AxisAngle const& b, AxisAngle const& difference)
        {
            Pose const pose1 =
                Pose(Position::meters({.x = 0, .y = 0, .z = 0}), Orientation::degrees(a));
            Pose const pose2 =
                Pose(Position::meters({.x = 0, .y = 0, .z = 0}), Orientation::degrees(b));
            SpatialDisplacement const dpose = pose2 - pose1;
            SpatialDisplacement const target_dpose =
                SpatialDisplacement(LinearDisplacement::meters({.x = 0, .y = 0, .z = 0}),
                                    AngularDisplacement::degrees(difference));
            CHECK_MESSAGE(
                dpose == Circa(target_dpose), dpose.to_string(), target_dpose.to_string());
            CHECK((pose1 + dpose) == Circa(pose2));
            CHECK((pose2 - dpose) == Circa(pose1));
        };
        test_spatial_aa({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0},
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0},
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0});
        test_spatial_aa({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0},
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90},
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90});
        test_spatial_aa({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 45},
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = -45},
                        {.axis = {.x = 1, .y = 0, .z = 0}, .angle = -90});
        test_spatial_aa(
            {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90},
            {.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90},
            {.axis = {.x = -1 / sqrt(3), .y = 1 / sqrt(3), .z = -1 / sqrt(3)}, .angle = 120});

        auto test_spatial_v3 = [](Vector const& a, Vector const& b, Vector const& difference)
        {
            Pose const pose1 =
                Pose(Position::meters(a), Orientation::degrees(Eigen::Quaterniond::Identity()));
            Pose const pose2 =
                Pose(Position::meters(b), Orientation::degrees(Eigen::Quaterniond::Identity()));
            SpatialDisplacement const dpose = pose2 - pose1;
            SpatialDisplacement const target_dpose =
                SpatialDisplacement(LinearDisplacement::meters(difference),
                                    AngularDisplacement::degrees(Eigen::Quaterniond::Identity()));
            CHECK_MESSAGE(
                dpose == Circa(target_dpose), dpose.to_string(), target_dpose.to_string());
            CHECK((pose1 + dpose) == Circa(pose2));
            CHECK((pose2 - dpose) == Circa(pose1));
        };

        test_spatial_v3(
            {.x = 0, .y = 0, .z = 0}, {.x = 0, .y = 0, .z = 0}, {.x = 0, .y = 0, .z = 0});
        test_spatial_v3(
            {.x = 0, .y = 0, .z = 0}, {.x = 0, .y = 0, .z = 1}, {.x = 0, .y = 0, .z = 1});
        test_spatial_v3(
            {.x = 1, .y = 2, .z = 3}, {.x = 4, .y = 5, .z = 6}, {.x = 3, .y = 3, .z = 3});
        Pose const pose1 =
            Pose(Position::meters({.x = 1, .y = 2, .z = 3}),
                 Orientation::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}));
        Pose const pose2 =
            Pose(Position::meters({.x = 4, .y = 5, .z = 6}),
                 Orientation::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}));
        SpatialDisplacement const dpose = pose2 - pose1;
        auto const target_dpose = SpatialDisplacement(
            LinearDisplacement::meters({.x = 3, .y = 3, .z = -3}),
            AngularDisplacement::degrees(
                {.axis = {.x = -1 / sqrt(3), .y = 1 / sqrt(3), .z = -1 / sqrt(3)}, .angle = 120}));
        CHECK_MESSAGE(dpose == Circa(target_dpose), dpose.to_string(), target_dpose.to_string());
        CHECK((pose1 + dpose) == Circa(pose2));
        CHECK((pose2 - dpose) == Circa(pose1));
    }
    TEST_CASE("state from itself is identity")
    {
        auto test = [](auto const& state)
        {
            using StateT = std::decay_t<decltype(state)>;
            using DiffT = traits::difference_type_of<StateT>;
            CHECK((state - state) == Circa(DiffT::zero()));
        };
        TimePoint::zero();
        test(TimePoint::seconds(1));
        test(Position::meters({.x = 1, .y = 2, .z = 3}));
        test(Orientation::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}));
        test(Pose(Position::meters({.x = 1, .y = 2, .z = 3}),
                  Orientation::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})));
    }
}

TEST_SUITE("addition of difference to state")
{
    TEST_CASE("scalar state and difference")
    {
        TimePoint t1 = TimePoint::seconds(1);
        Duration const dt = Duration::seconds(1);
        TimePoint const t2 = t1 + dt;
        t1 += dt;
        CHECK(t1 == TimePoint::seconds(2));
        CHECK(t1 == Circa(t2));
    }

    TEST_CASE("linear state and difference")
    {
        Position p1 = Position::meters({.x = 1, .y = 2, .z = 3});
        LinearDisplacement const dp = LinearDisplacement::meters({.x = 3, .y = 3, .z = 3});
        Position const p2 = p1 + dp;
        p1 += dp;
        CHECK(p1 == Position::meters({.x = 4, .y = 5, .z = 6}));
        CHECK(p1 == Circa(p2));
    }

    TEST_CASE("angular state and difference")
    {
        Orientation o1 = Orientation::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90});
        AngularDisplacement const dori =
            AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90});
        Orientation const o2 = o1 + dori;
        o1 += dori;
        CHECK(o1 ==
              Circa(Orientation::degrees(
                  {.axis = {.x = 1 / sqrt(3), .y = 1 / sqrt(3), .z = 1 / sqrt(3)}, .angle = 120})));
        CHECK(o1 == Circa(o2));
    }

    TEST_CASE("spatial state and difference")
    {
        Pose pose1 = Pose(Position::meters({.x = 1, .y = 2, .z = 3}),
                          Orientation::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 0}));
        SpatialDisplacement const dpose = SpatialDisplacement(
            LinearDisplacement::meters({.x = 3, .y = 3, .z = 3}),
            AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}));
        Pose const pose2 = pose1 + dpose;
        pose1 += dpose;
        CHECK(pose1 ==
              Circa(Pose(Position::meters({.x = 4, .y = 5, .z = 6}),
                         Orientation::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}))));
        CHECK(pose1 == Circa(pose2));
    }
}

TEST_SUITE("subtraction of difference from state")
{
    TEST_CASE("scalar state and difference")
    {
        TimePoint t1 = TimePoint::seconds(2);
        Duration const dt = Duration::seconds(1);
        TimePoint const t2 = t1 - dt;
        t1 -= dt;
        CHECK(t1 == TimePoint::seconds(1));
        CHECK(t1 == Circa(t2));
    }

    TEST_CASE("linear state and difference")
    {
        Position p1 = Position::meters({.x = 4, .y = 5, .z = 6});
        LinearDisplacement const dp = LinearDisplacement::meters({.x = 3, .y = 3, .z = 3});
        Position const p2 = p1 - dp;
        p1 -= dp;
        CHECK(p1 == Position::meters({.x = 1, .y = 2, .z = 3}));
        CHECK(p1 == Circa(p2));
    }

    TEST_CASE("angular state and difference")
    {
        Orientation o1 = Orientation::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90});
        AngularDisplacement const dori =
            AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90});
        Orientation const o2 = o1 - dori;
        o1 -= dori;
        CHECK(o1 == Circa(Orientation::degrees(
                        {.axis = {.x = 1 / sqrt(3), .y = -1 / sqrt(3), .z = -1 / sqrt(3)},
                         .angle = 120})));
        CHECK(o1 == Circa(o2));
    }

    TEST_CASE("spatial state and difference")
    {
        Pose pose1 = Pose(Position::meters({.x = 4, .y = 5, .z = 6}),
                          Orientation::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}));
        SpatialDisplacement const dpose = SpatialDisplacement(
            LinearDisplacement::meters({.x = 3, .y = 3, .z = 3}),
            AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}));
        Pose const pose2 = pose1 - dpose;
        pose1 -= dpose;
        CHECK(pose1 ==
              Circa(Pose(Position::meters({.x = 7, .y = 8, .z = 3}),
                         Orientation::degrees(
                             {.axis = {.x = 1 / sqrt(3), .y = -1 / sqrt(3), .z = -1 / sqrt(3)},
                              .angle = 120}))));
        CHECK(pose1 == Circa(pose2));
    }
}

TEST_SUITE("inplace subtraction of state and difference")
{
    TEST_CASE("scalar state and difference")
    {
        TimePoint t1 = TimePoint::seconds(1);
        TimePoint t2 = TimePoint::seconds(2);
        Duration const dt = t2 - t1;
        Duration const dt2 = Duration::seconds(1);
        t1 -= dt;
        t2 -= dt2;
        CHECK(t1 == TimePoint::seconds(0));
        CHECK(t2 == TimePoint::seconds(1));
    }

    TEST_CASE("linear state and difference")
    {
        Position p1 = Position::meters({.x = 1, .y = 2, .z = 3});
        Position p2 = Position::meters({.x = 4, .y = 5, .z = 6});
        LinearDisplacement const dp = p2 - p1;
        LinearDisplacement const dp2 = LinearDisplacement::meters({.x = 3, .y = 3, .z = 3});
        p1 -= dp;
        p2 -= dp2;
        CHECK(p1 == Position::meters({.x = -2, .y = -1, .z = 0}));
        CHECK(p2 == Position::meters({.x = 1, .y = 2, .z = 3}));
    }

    TEST_CASE("angular state and difference")
    {
        Orientation o1 = Orientation::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90});
        Orientation o2 = Orientation::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 45});
        AngularDisplacement const dori = o2 - o1;
        AngularDisplacement const dori2 =
            AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 35});
        o1 -= dori;
        o2 -= dori2;
        CHECK(o1 == Circa(Orientation::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 135})));
        CHECK(o2 == Circa(Orientation::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 10})));
    }

    TEST_CASE("spatial state and difference")
    {
        Pose pose1 = Pose(Position::meters({.x = 1, .y = 2, .z = 3}),
                          Orientation::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 10}));

        Pose pose2 = Pose(Position::meters({.x = 4, .y = 5, .z = 6}),
                          Orientation::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 10}));

        SpatialDisplacement const dpose = pose2 - pose1;
        SpatialDisplacement const dpose2 = SpatialDisplacement(
            LinearDisplacement::meters({.x = 0, .y = 0, .z = 0}),
            AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 50}));
        pose1 -= dpose;
        pose2 -= dpose2;
        CHECK_MESSAGE(pose1 == Circa(Pose(Position::meters({.x = -2, .y = -1, .z = 0}),
                                          Orientation::degrees(
                                              {.axis = {.x = 1, .y = 0, .z = 0}, .angle = 10}))),
                      pose1.to_string());
        CHECK_MESSAGE(pose2 == Circa(Pose(Position::meters({.x = 4, .y = 5, .z = 6}),
                                          Orientation::degrees(
                                              {.axis = {.x = 1, .y = 0, .z = 0}, .angle = -40}))),
                      pose2.to_string());
        CHECK((pose1 + dpose) ==
              Circa(Pose(Position::meters({.x = 1, .y = 2, .z = 3}),
                         Orientation::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 10}))));
        CHECK((pose2 + dpose2) ==
              Circa(Pose(Position::meters({.x = 4, .y = 5, .z = 6}),
                         Orientation::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 10}))));
    }
}
#ifdef QUANT_ENABLE_DIFFERENCE_ADDITION
TEST_SUITE("addition of difference and difference")
{
    TEST_CASE("scalar difference and difference")
    {
        auto const d1 = Duration::seconds(1);
        auto const d2 = Duration::seconds(2);
        auto const dsum = d1 + d2;
        CHECK(dsum == Duration::seconds(3));
        CHECK(dsum - d2 == d1);
    }
    TEST_CASE("linear difference and difference")
    {
        auto const ld1 = LinearDisplacement::meters({.x = 1, .y = 2, .z = 3});
        auto const ld2 = LinearDisplacement::meters({.x = 4, .y = 5, .z = 6});
        auto const ldsum = ld1 + ld2;
        CHECK(ldsum == LinearDisplacement::meters({.x = 5, .y = 7, .z = 9}));
        CHECK(ldsum - ld2 == ld1);
    }
    TEST_CASE("angular difference and difference")
    {
        auto const ad1 =
            AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90});
        auto const ad2 =
            AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90});
        auto const adsum = ad1 + ad2;
        CHECK(adsum ==
              Circa(AngularDisplacement::degrees(
                  {.axis = {.x = 1 / sqrt(3), .y = 1 / sqrt(3), .z = 1 / sqrt(3)}, .angle = 120})));
        CHECK((adsum - ad2) == Circa(ad1));
    }
    TEST_CASE("spatial difference and difference")
    {
        auto const sd1 = SpatialDisplacement(
            LinearDisplacement::meters({.x = 1, .y = 2, .z = 3}),
            AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}));
        auto const sd2 = SpatialDisplacement(
            LinearDisplacement::meters({.x = 4, .y = 5, .z = 6}),
            AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}));
        auto const sdsum = sd1 + sd2;
        CHECK_MESSAGE(sdsum ==
                          Circa(SpatialDisplacement(
                              LinearDisplacement::meters({.x = 5, .y = -4, .z = 8}),
                              AngularDisplacement::degrees(
                                  {.axis = {.x = 1 / sqrt(3), .y = 1 / sqrt(3), .z = 1 / sqrt(3)},
                                   .angle = 120}))),
                      sdsum.to_string());
        CHECK((sdsum - sd2) == Circa(sd1));
    }
    TEST_CASE(
        "addition of difference added to state is the same as the difference added separately")
    {
        auto test = [](auto const& state, auto const& diff1, auto const& diff2)
        {
            auto const state_plus_diff1 = state + diff1;
            auto const state_plus_diff2 = state + diff2;
            auto const diff1_plus_diff2 = diff1 + diff2;
            auto const diff2_plus_diff1 = diff2 + diff1;
            auto const state12 = state_plus_diff1 + diff2;
            auto const state21 = state_plus_diff2 + diff1;
            CHECK_MESSAGE((state12) == Circa(state + diff1_plus_diff2),
                          state.to_string(),
                          diff1.to_string(),
                          diff2.to_string());
            CHECK_MESSAGE((state21) == Circa(state + diff2_plus_diff1),
                          state.to_string(),
                          diff1.to_string(),
                          diff2.to_string());
            CHECK(((state + diff1_plus_diff2) - diff2) == Circa(state_plus_diff1));
            CHECK(((state + diff2_plus_diff1) - diff1) == Circa(state_plus_diff2));
            // CHECK_MESSAGE((state - diff1_plus_diff2) == Circa((state - diff1) - diff2),
            //               state.to_string(),
            //               diff1.to_string(),
            //               diff2.to_string(),
            //               diff1_plus_diff2.to_string(),
            //               (state - diff1).to_string(),
            //               diff2.to_string());
            // CHECK_MESSAGE((state - diff2_plus_diff1) == Circa((state - diff2) - diff1),
            //               state.to_string(),
            //               diff1.to_string(),
            //               diff2.to_string(),
            //               diff2_plus_diff1.to_string(),
            //               (state - diff2).to_string(),
            //               diff1.to_string());
            INFO("Addition of Difference is commutattive: ",
                 (state + diff1_plus_diff2) == Circa(state + diff2_plus_diff1));
        };
        test(TimePoint::seconds(1), Duration::seconds(1), Duration::seconds(2));
        test(Position::meters({.x = 1, .y = 2, .z = 3}),
             LinearDisplacement::meters({.x = 1, .y = 2, .z = 3}),
             LinearDisplacement::meters({.x = 4, .y = 5, .z = 6}));
        test(Orientation::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 10}),
             AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 10}),
             AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 20}));
        test(Pose(Position::meters({.x = 1, .y = 2, .z = 3}),
                  Orientation::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 10})),
             SpatialDisplacement(
                 LinearDisplacement::meters({.x = 1, .y = 2, .z = 3}),
                 AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 10})),
             SpatialDisplacement(
                 LinearDisplacement::meters({.x = 4, .y = 5, .z = 6}),
                 AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 20})));
    }
    TEST_CASE("addition is opposite of subtraction")
    {
        auto test = [](auto const& state, auto const& diff)
        {
            auto const state_plus_diff = state + diff;
            auto const state_minus_diff = state - diff;
            CHECK_MESSAGE(
                (state_plus_diff - diff) == Circa(state), state.to_string(), diff.to_string());
            CHECK_MESSAGE(
                (state_minus_diff + diff) == Circa(state), state.to_string(), diff.to_string());
            CHECK_MESSAGE(
                (state + diff - diff) == Circa(state), state.to_string(), diff.to_string());
            CHECK_MESSAGE(
                (state - diff + diff) == Circa(state), state.to_string(), diff.to_string());
        };
    }
}

TEST_SUITE("inplace addition of difference and difference")
{
    TEST_CASE("scalar difference and difference")
    {
        auto d1 = Duration::seconds(1);
        auto const d2 = Duration::seconds(2);
        d1 += d2;
        CHECK(d1 == Circa(Duration::seconds(3)));
        d1 -= d2;
        CHECK(d1 == Circa(Duration::seconds(1)));
    }
    TEST_CASE("linear difference and difference")
    {
        auto ld1 = LinearDisplacement::meters({.x = 1, .y = 2, .z = 3});
        auto const ld2 = LinearDisplacement::meters({.x = 4, .y = 5, .z = 6});
        ld1 += ld2;
        CHECK(ld1 == Circa(LinearDisplacement::meters({.x = 5, .y = 7, .z = 9})));
        ld1 -= ld2;
        CHECK(ld1 == Circa(LinearDisplacement::meters({.x = 1, .y = 2, .z = 3})));
    }
    TEST_CASE("angular difference and difference")
    {
        auto ad1 = AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90});
        auto const ad2 =
            AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90});
        ad1 += ad2;
        CHECK(ad1 ==
              Circa(AngularDisplacement::degrees(
                  {.axis = {.x = 1 / sqrt(3), .y = 1 / sqrt(3), .z = 1 / sqrt(3)}, .angle = 120})));
        ad1 -= ad2;
        CHECK(ad1 ==
              Circa(AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90})));
    }
    TEST_CASE("spatial difference and difference")
    {
        auto sd1 = SpatialDisplacement(
            LinearDisplacement::meters({.x = 1, .y = 2, .z = 3}),
            AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}));
        auto const sd2 = SpatialDisplacement(
            LinearDisplacement::meters({.x = 4, .y = 5, .z = 6}),
            AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}));
        sd1 += sd2;
        CHECK(sd1 == Circa(SpatialDisplacement(
                         LinearDisplacement::meters({.x = 5, .y = -4, .z = 8}),
                         AngularDisplacement::degrees(
                             {.axis = {.x = 1 / sqrt(3), .y = 1 / sqrt(3), .z = 1 / sqrt(3)},
                              .angle = 120}))));
        sd1 -= sd2;
        CHECK(sd1 ==
              Circa(SpatialDisplacement(
                  LinearDisplacement::meters({.x = 1, .y = 2, .z = 3}),
                  AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}))));
    }
}

TEST_SUITE("subtraction of difference and difference")
{
    TEST_CASE("scalar difference and difference")
    {
        Duration const d1 = Duration::seconds(1);
        Duration const d2 = Duration::seconds(2);
        Duration const dsub = d2 - d1;
        CHECK(dsub == Circa(Duration::seconds(1)));
    }
    TEST_CASE("linear difference and difference")
    {
        LinearDisplacement const ld1 = LinearDisplacement::meters({.x = 1, .y = 2, .z = 3});
        LinearDisplacement const ld2 = LinearDisplacement::meters({.x = 4, .y = 5, .z = 6});
        LinearDisplacement const ldsub = ld2 - ld1;
        CHECK(ldsub == Circa(LinearDisplacement::meters({.x = 3, .y = 3, .z = 3})));
    }
    TEST_CASE("angular difference and difference")
    {
        AngularDisplacement const ad1 =
            AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90});
        AngularDisplacement const ad2 =
            AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90});
        AngularDisplacement const adsub = ad1 - ad2;
        CHECK(adsub == Circa(AngularDisplacement::degrees(
                           {.axis = {.x = 1 / sqrt(3), .y = -1 / sqrt(3), .z = -1 / sqrt(3)},
                            .angle = 120})));
    }
    TEST_CASE("spatial difference and difference")
    {
        SpatialDisplacement const sd1 = SpatialDisplacement(
            LinearDisplacement::meters({.x = 1, .y = 2, .z = 3}),
            AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}));
        SpatialDisplacement const sd2 = SpatialDisplacement(
            LinearDisplacement::meters({.x = 4, .y = 5, .z = 6}),
            AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}));
        SpatialDisplacement const sdsub = sd1 - sd2;
        CHECK(sdsub == Circa(SpatialDisplacement(
                           LinearDisplacement::meters({.x = 7, .y = 6, .z = -2}),
                           AngularDisplacement::degrees(
                               {.axis = {.x = 1 / sqrt(3), .y = -1 / sqrt(3), .z = -1 / sqrt(3)},
                                .angle = 120}))));
    }
    // TODO: This doesn't work as I would expect it to
    // TEST_CASE("subtraction of difference subtracted from state is the same as the difference
    // added "
    //           "separately")
    // {
    //     auto test = [](auto const& state, auto const& diff1, auto const& diff2)
    //     {
    //         auto const state_minus_diff1 = state - diff1;
    //         auto const state_minus_diff2 = state - diff2;
    //         auto const diff1_minus_diff2 = diff1 - diff2;
    //         auto const diff2_minus_diff1 = diff2 - diff1;
    //         auto const state12 = state_minus_diff1 + diff2;
    //         auto const state21 = state_minus_diff2 + diff1;
    //         CHECK_MESSAGE((state12) == Circa(state - diff1_minus_diff2),
    //                       state.to_string(),
    //                       state12.to_string(),
    //                       (state - diff1_minus_diff2).to_string());
    //         CHECK_MESSAGE((state21) == Circa(state - diff2_minus_diff1),
    //                       state.to_string(),
    //                       state21.to_string(),
    //                       (state - diff2_minus_diff1).to_string());
    //         CHECK(((state - diff1_minus_diff2) - diff2) == Circa(state_minus_diff1));
    //         CHECK(((state - diff2_minus_diff1) - diff1) == Circa(state_minus_diff2));
    //         CHECK((state - diff1_minus_diff2) == Circa(state - diff1 + diff2));
    //         CHECK((state - diff2_minus_diff1) == Circa(state - diff2 + diff1));
    //         INFO("Subtraction of Difference is commutattive: ",
    //              (state - diff1_minus_diff2) == Circa(state - diff2_minus_diff1));
    //     };
    //     test(TimePoint::seconds(1), Duration::seconds(1), Duration::seconds(2));
    //     test(Position::meters({.x = 1, .y = 2, .z = 3}),
    //          LinearDisplacement::meters({.x = 1, .y = 2, .z = 3}),
    //          LinearDisplacement::meters({.x = 4, .y = 5, .z = 6}));
    //     test(Orientation::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 10}),
    //          AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 10}),
    //          AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 20}));
    //     test(Pose(Position::meters({.x = 1, .y = 2, .z = 3}),
    //               Orientation::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 10})),
    //          SpatialDisplacement(
    //              LinearDisplacement::meters({.x = 1, .y = 2, .z = 3}),
    //              AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 10})),
    //          SpatialDisplacement(
    //              LinearDisplacement::meters({.x = 4, .y = 5, .z = 6}),
    //              AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 20})));
    // }
}

TEST_SUITE("inplace subtraction of difference and difference")
{
    TEST_CASE("scalar difference and difference")
    {
        Duration d1 = Duration::seconds(1);
        Duration const d2 = Duration::seconds(2);
        d1 -= d2;
        CHECK(d1 == Circa(Duration::seconds(-1)));
    }

    TEST_CASE("linear difference and difference")
    {
        LinearDisplacement ld1 = LinearDisplacement::meters({.x = 1, .y = 2, .z = 3});
        LinearDisplacement const ld2 = LinearDisplacement::meters({.x = 4, .y = 5, .z = 6});
        ld1 -= ld2;
        CHECK(ld1 == Circa(LinearDisplacement::meters({.x = -3, .y = -3, .z = -3})));
    }

    TEST_CASE("angular difference and difference")
    {
        AngularDisplacement ad1 =
            AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90});
        AngularDisplacement const ad2 =
            AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90});
        ad1 -= ad2;
        CHECK(ad1 == Circa(AngularDisplacement::degrees(
                         {.axis = {.x = 1 / sqrt(3), .y = -1 / sqrt(3), .z = -1 / sqrt(3)},
                          .angle = 120})));
    }
    TEST_CASE("spatial difference and difference")
    {
        SpatialDisplacement sd1 = SpatialDisplacement(
            LinearDisplacement::meters({.x = 1, .y = 2, .z = 3}),
            AngularDisplacement::degrees({.axis = {.x = 1, .y = 0, .z = 0}, .angle = 90}));
        SpatialDisplacement const sd2 = SpatialDisplacement(
            LinearDisplacement::meters({.x = 4, .y = 5, .z = 6}),
            AngularDisplacement::degrees({.axis = {.x = 0, .y = 1, .z = 0}, .angle = 90}));
        sd1 -= sd2;
        CHECK(sd1 == Circa(SpatialDisplacement(
                         LinearDisplacement::meters({.x = 7, .y = 6, .z = -2}),
                         AngularDisplacement::degrees(
                             {.axis = {.x = 1 / sqrt(3), .y = -1 / sqrt(3), .z = -1 / sqrt(3)},
                              .angle = 120}))));
    }
}
#endif

TEST_SUITE("Test angular state and its difference for SO3 and others")
{
    TEST_CASE("orientations can only have an angle between 0 and 360 degrees")
    {
        auto test = [](double angle)
        {
            auto const aa = AxisAngle{.axis = Vector::from_eigen(Eigen::Vector3d::Random() * 2000 -
                                                                 Eigen::Vector3d::Constant(1000)),
                                      .angle = angle};
            auto const eigen = aa.to_eigen();
            auto const ori = Orientation::degrees(aa);
            CHECK(ori.to_degrees().angle >= 0);
            CHECK(ori.to_degrees().angle < 360);
            CHECK(ori.to_degrees().axis.norm() == doctest::Approx(1));
        };
        test(0);
        test(90);
        test(360);
        test(720);
        test(-360);
        test(-720);
    }

    TEST_CASE("angular differences can have more than 360 degrees")
    {
        auto test = [](double angle)
        {
            auto const aa = AxisAngle{.axis = Vector::from_eigen(Eigen::Vector3d::Random() * 2000 -
                                                                 Eigen::Vector3d::Constant(1000)),
                                      .angle = angle};
            auto const ad = AngularDisplacement::degrees(aa);
            auto const avd = AngularVelocityDifference::degrees_per_second(aa);
            // CHECK(ad.to_degrees().angle == doctest::Approx(angle)); // TODO: Fix this
            CHECK(ad.to_degrees().axis.norm() == doctest::Approx(1));
            CHECK(avd.to_degrees_per_second().angle == doctest::Approx(angle));
            CHECK(avd.to_degrees_per_second().axis.norm() == doctest::Approx(1));
        };
        test(0);
        test(90);
        test(360);
        test(720);
        test(-360);
        test(-720);
    }
}