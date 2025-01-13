#pragma once

#include <quant/units/position.h>

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
}  // namespace quant::traits::arithmetics

using namespace quant;

TEST_SUITE("concrete instantiation using position")
{
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
        SUBCASE("math operators are defined for State vs State")
        {
            // State with State
            static_assert(not traits::addition::is_possible_v<Position, Position>,
                          "Position types should not be addable");
            static_assert(not traits::addition::is_possible_inplace_v<Position, Position>,
                          "Position types should not be addable inplace");
            static_assert(traits::subtraction::is_possible_v<Position, Position>,
                          "Position types should not be subtractable");
            static_assert(not traits::subtraction::is_possible_inplace_v<Position, Position>,
                          "Position types should not be subtractable inplace");
            static_assert(not traits::multiplication::is_possible_v<Position, Position>,
                          "Position types should not be multiplicative");
            static_assert(not traits::multiplication::is_possible_inplace_v<Position, Position>,
                          "Position types should not be multiplicative inplace");
            static_assert(traits::division::is_possible_v<Position, Position>,
                          "Position types should be dividable");
            static_assert(not traits::division::is_possible_inplace_v<Position, Position>,
                          "Position types should be dividable inplace");
        }
        SUBCASE("math operators are defined for State vs Difference")
        {
            // State with Difference
            static_assert(traits::addition::is_possible_v<Position, LinearDisplacement>,
                          "State and Difference types should be addable");
            static_assert(traits::addition::is_possible_inplace_v<Position, LinearDisplacement>,
                          "State and Difference types should be addable inplace");
            static_assert(traits::subtraction::is_possible_v<Position, LinearDisplacement>,
                          "State and Difference types should be subtractable");
            static_assert(traits::subtraction::is_possible_inplace_v<Position, LinearDisplacement>,
                          "State and Difference types should be subtractable inplace");
            static_assert(not traits::multiplication::is_possible_v<Position, LinearDisplacement>,
                          "State and Difference types should not be multiplicative");
            static_assert(
                not traits::multiplication::is_possible_inplace_v<Position, LinearDisplacement>,
                "State and Difference types should not be multiplicative inplace");
            static_assert(not traits::division::is_possible_v<Position, LinearDisplacement>,
                          "State and Difference types should not be dividable");
            static_assert(not traits::division::is_possible_inplace_v<Position, LinearDisplacement>,
                          "State and Difference types should not be dividable inplace");
        }
        SUBCASE("math operators are defined for Difference vs State")
        {
            // Difference with State
            static_assert(not traits::addition::is_possible_v<LinearDisplacement, Position>,
                          "Difference and State types should not be addable");
            static_assert(not traits::addition::is_possible_inplace_v<LinearDisplacement, Position>,
                          "Difference and State types should not be addable inplace");
            static_assert(not traits::subtraction::is_possible_v<LinearDisplacement, Position>,
                          "Difference and State types should not be subtractable");
            static_assert(
                not traits::subtraction::is_possible_inplace_v<LinearDisplacement, Position>,
                "Difference and State types should not be subtractable inplace");
            static_assert(not traits::multiplication::is_possible_v<LinearDisplacement, Position>,
                          "Difference and State types should not be multiplicative");
            static_assert(
                not traits::multiplication::is_possible_inplace_v<LinearDisplacement, Position>,
                "Difference and State types should not be multiplicative inplace");
            static_assert(not traits::division::is_possible_v<LinearDisplacement, Position>,
                          "Difference and State types should not be dividable");
            static_assert(not traits::division::is_possible_inplace_v<LinearDisplacement, Position>,
                          "Difference and State types should not be dividable inplace");
        }
        SUBCASE("math operators are defined for Difference vs Difference")
        {
            // Difference with Difference
            static_assert(traits::addition::is_possible_v<LinearDisplacement, LinearDisplacement>,
                          "Difference and State types should be addable");
            static_assert(
                traits::addition::is_possible_inplace_v<LinearDisplacement, LinearDisplacement>,
                "Difference and State types should be addable inplace");
            static_assert(
                traits::subtraction::is_possible_v<LinearDisplacement, LinearDisplacement>,
                "Difference and State types should be subtractable");
            static_assert(
                traits::subtraction::is_possible_inplace_v<LinearDisplacement, LinearDisplacement>,
                "Difference and State types should be subtractable inplace");
            static_assert(
                not traits::multiplication::is_possible_v<LinearDisplacement, LinearDisplacement>,
                "Difference and State types should not be multiplicative");
            static_assert(not traits::multiplication::is_possible_inplace_v<LinearDisplacement,
                                                                            LinearDisplacement>,
                          "Difference and State types should not be multiplicative inplace");
            static_assert(traits::division::is_possible_v<LinearDisplacement, LinearDisplacement>,
                          "Difference and State types should be dividable");
            static_assert(
                traits::division::is_possible_inplace_v<LinearDisplacement, LinearDisplacement>,
                "Difference and State types should be dividable inplace");
        }

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
        CHECK(p5 == -p1);
        p5 += diff;
        CHECK(p5 == p2);
        p5 -= diff;
        CHECK(p5 == -p1);
    }
}
