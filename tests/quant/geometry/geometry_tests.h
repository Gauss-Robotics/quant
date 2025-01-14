#pragma once

#include <quant/units/position.h>
#include <quant/units/velocity.h>
#include <quant/units/acceleration.h>
#include <quant/units/time.h>

#include <doctest/doctest.h>

#include <type_traits>

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
            test_inplace(int) -> decltype(std::declval<X&>() += std::declval<Y>(), std::true_type());

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
            test_inplace(int) -> decltype(std::declval<X&>() -= std::declval<Y>(), std::true_type());

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
            test_inplace(int) -> decltype(std::declval<X&>() *= std::declval<Y>(), std::true_type());

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
            test_inplace(int) -> decltype(std::declval<X&>() /= std::declval<Y>(), std::true_type());

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
    void check_arithmetics()
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
            static_assert(
                not multiplication::is_possible_inplace_v<StateT, DifferenceT>,
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
            static_assert(
                not subtraction::is_possible_inplace_v<DifferenceT, StateT>,
                "Difference and State types should not be subtractable inplace");
            static_assert(not multiplication::is_possible_v<DifferenceT, StateT>,
                          "Difference and State types should not be multiplicative");
            static_assert(
                not multiplication::is_possible_inplace_v<DifferenceT, StateT>,
                "Difference and State types should not be multiplicative inplace");
            static_assert(not division::is_possible_v<DifferenceT, StateT>,
                          "Difference and State types should not be dividable");
            static_assert(not division::is_possible_inplace_v<DifferenceT, StateT>,
                          "Difference and State types should not be dividable inplace");
        }
        SUBCASE("math operators are defined for Difference vs Difference")
        {
            // Difference with Difference
            static_assert(addition::is_possible_v<DifferenceT, DifferenceT>,
                          "Difference and Difference types should be addable");
            static_assert(
                addition::is_possible_inplace_v<DifferenceT, DifferenceT>,
                "Difference and Difference types should be addable inplace");
            static_assert(
                subtraction::is_possible_v<DifferenceT, DifferenceT>,
                "Difference and Difference types should be subtractable");
            static_assert(
                subtraction::is_possible_inplace_v<DifferenceT, DifferenceT>,
                "Difference and Difference types should be subtractable inplace");
            static_assert(
                not multiplication::is_possible_v<DifferenceT, DifferenceT>,
                "Difference and Difference types should not be multiplicative");
            static_assert(not multiplication::is_possible_inplace_v<DifferenceT,
                                                                            DifferenceT>,
                          "Difference and Difference types should not be multiplicative inplace");
            // static_assert(division::is_possible_v<DifferenceT, DifferenceT>,
            //               "Difference and Difference types should be dividable"); TODO: this should only be possible partially (e.g. not for poses or orientations)
            static_assert(
                not division::is_possible_inplace_v<DifferenceT, DifferenceT>,
                "Difference and Difference types should not be dividable inplace");
        }
        auto state = StateT();
        auto diff = DifferenceT();
        state - state;
        state += diff;
        state -= diff;
        state + diff;
        state - diff;

        diff + diff;
        diff += diff;
        diff - diff;
        diff -= diff;

    }

    template <typename Quantity1, typename Quantity2>
    void check_differing_domains()
    {
        static_assert(not addition::is_possible_v<Quantity1, Quantity2>,
                          "Different domains should not be addable");
        static_assert(not
            addition::is_possible_inplace_v<Quantity1, Quantity2>,
            "Different domains should not be addable inplace");
        static_assert(not
            subtraction::is_possible_v<Quantity1, Quantity2>,
            "Different domains should not be subtractable");
        static_assert(not
            subtraction::is_possible_inplace_v<Quantity1, Quantity2>,
            "Different domains should not be subtractable inplace");
        static_assert(
            not multiplication::is_possible_v<Quantity1, Quantity2>,
            "Different domains should not be multiplicative");
        static_assert(not multiplication::is_possible_inplace_v<Quantity1,
                                                                        Quantity2>,
                      "Different domains should not be multiplicative inplace");
        static_assert(not division::is_possible_v<Quantity1, Quantity2>,
                      "Different domains should not be dividable");
        static_assert(
            not division::is_possible_inplace_v<Quantity1, Quantity2>,
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

        // TODO: Tests for scaling with float, double, long double, int, long, long long
        // TODO: Tests for Position + Velocity, Position + Acceleration, Position + Force, etc.
        // TODO: Tests for negation

        LinearDisplacement const diff = p2 - p1;
        LinearDisplacement const diff2 = diff + diff;
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
