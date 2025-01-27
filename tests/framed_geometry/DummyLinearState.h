#pragma once
#include <quant/framed_geometry/Difference.h>
#include <quant/framed_geometry/State.h>
#include <quant/framed_geometry/forward_declarations.h>
#include <quant/geometry/AngularState.h>
#include <quant/geometry/Difference.h>
#include <quant/geometry/LinearState.h>
#include <quant/geometry/SpatialState.h>
#include <quant/geometry/forward_declarations.h>
#include <quant/units/position/SpatialDisplacement.h>

namespace quant
{
    class DummyLinearState;
    class DummyLinearDiff;
    class DummyAngularState;
    class DummyAngularDiff;
    class DummySpatialState;
    class DummySpatialDiff;

    class FramedDummyLinearState;
    class FramedDummyLinearDiff;
    class FramedDummyAngularState;
    class FramedDummyAngularDiff;
    class FramedDummySpatialState;
    class FramedDummySpatialDiff;

    namespace traits
    {
        using DummyDomain = Define3DDomain<DummyLinearState,
                                           DummyAngularState,
                                           DummySpatialState,
                                           DummyLinearDiff,
                                           DummyAngularDiff,
                                           DummySpatialDiff>;

        template <>
        struct DefineTraits<DummyLinearState>
        {
            using Domain = DummyDomain;
            using State = DummyLinearState;
            using Difference = DummyLinearDiff;
            using GeometricType = LinearStateType;
        };

        template <>
        struct DefineTraits<DummyLinearDiff>
        {
            using Domain = DummyDomain;
            using State = DummyLinearState;
            using Difference = DummyLinearDiff;
            using GeometricType = LinearDifferenceType;
        };

        template <>
        struct DefineTraits<DummyAngularState>
        {
            using Domain = DummyDomain;
            using State = DummyAngularState;
            using Difference = DummyAngularDiff;
            using GeometricType = AngularStateType;
        };

        template <>
        struct DefineTraits<DummyAngularDiff>
        {
            using Domain = DummyDomain;
            using State = DummyAngularState;
            using Difference = DummyAngularDiff;
            using GeometricType = AngularDifferenceType;
        };

        template <>
        struct DefineTraits<DummySpatialState>
        {
            using Domain = DummyDomain;
            using State = DummySpatialState;
            using Difference = DummySpatialDiff;
            using GeometricType = SpatialStateType;
        };

        template <>
        struct DefineTraits<DummySpatialDiff>
        {
            using Domain = DummyDomain;
            using State = DummySpatialState;
            using Difference = DummySpatialDiff;
            using GeometricType = SpatialDifferenceType;
        };
    }  // namespace traits

    class DummyLinearState : public geometry::LinearState<DummyLinearState>
    {
    public:
        using LinearState<DummyLinearState>::LinearState;
    };

    class DummyLinearDiff : public geometry::Difference<DummyLinearState>
    {
    public:
        std::string
        to_string() const
        {
            return "DummyLinearDiff";
        }

        using geometry::Difference<DummyLinearState>::Difference;
    };

    class DummyAngularState : public geometry::AngularState<DummyAngularState>
    {
    public:
        using geometry::AngularState<DummyAngularState>::AngularState;
    };

    class DummyAngularDiff : public geometry::Difference<DummyAngularState>
    {
    public:
        using geometry::Difference<DummyAngularState>::Difference;
    };

    class DummySpatialState : public geometry::SpatialState<DummySpatialState>
    {
    public:
        DummySpatialState() : SpatialState<DummySpatialState>{zero()}
        {
            ;
        }

        using SpatialState<DummySpatialState>::SpatialState;
    };

    class DummySpatialDiff : public geometry::Difference<DummySpatialState>
    {
    public:
        using Difference<DummySpatialState>::Difference;
    };

    namespace traits
    {
        using FramedDummyDomain = Define3DDomain<FramedDummyLinearState,
                                                 FramedDummyAngularState,
                                                 FramedDummySpatialState,
                                                 FramedDummyLinearDiff,
                                                 FramedDummyAngularDiff,
                                                 FramedDummySpatialDiff>;

        template <>
        struct DefineFramedTraits<DummyLinearState> : traits_of<DummyLinearState>
        {
            using FramedDomain = FramedDummyDomain;
            using FramedDifference = FramedDummyLinearDiff;
            using FramedState = FramedDummyLinearState;
            static constexpr auto basis_change_function =
                [](DummyLinearState const&, framed_geometry::BaseChange const&)
            { return DummyLinearState{}; };
        };

        template <>
        struct DefineFramedTraits<DummyLinearDiff> : traits_of<DummyLinearDiff>
        {
            using FramedDomain = FramedDummyDomain;
            using FramedState = FramedDummyLinearState;
            using FramedDifference = FramedDummyLinearDiff;
            static constexpr auto basis_change_function =
                [](DummyLinearDiff const&, framed_geometry::BaseChange const&)
            { return DummyLinearDiff{}; };
        };

        template <>
        struct DefineFramedTraits<DummyAngularState> : traits_of<DummyAngularState>
        {
            using FramedDomain = FramedDummyDomain;
            using FramedDifference = FramedDummyAngularDiff;
            using FramedState = FramedDummyAngularState;
            static constexpr auto basis_change_function =
                [](DummyAngularState const&, framed_geometry::BaseChange const&)
            { return DummyAngularState{}; };
        };

        template <>
        struct DefineFramedTraits<DummyAngularDiff> : traits_of<DummyAngularDiff>
        {
            using FramedDomain = FramedDummyDomain;
            using FramedState = FramedDummyAngularState;
            using FramedDifference = FramedDummyAngularDiff;
            static constexpr auto basis_change_function =
                [](DummyAngularDiff const&, framed_geometry::BaseChange const&)
            { return DummyAngularDiff{}; };
        };

        template <>
        struct DefineFramedTraits<DummySpatialState> : traits_of<DummySpatialState>
        {
            using FramedDomain = FramedDummyDomain;
            using FramedDifference = FramedDummySpatialDiff;
            using FramedState = FramedDummySpatialState;
            static constexpr auto basis_change_function =
                [](DummySpatialState const&, framed_geometry::BaseChange const&)
            { return DummySpatialState::zero(); };
        };

        template <>
        struct DefineFramedTraits<DummySpatialDiff> : traits_of<DummySpatialDiff>
        {
            using FramedDomain = FramedDummyDomain;
            using FramedState = FramedDummySpatialState;
            using FramedDifference = FramedDummySpatialDiff;
            static constexpr auto basis_change_function =
                [](DummySpatialDiff const&, framed_geometry::BaseChange const&)
            { return DummySpatialDiff{}; };
        };
    }  // namespace traits

    class FramedDummyLinearState : public framed_geometry::State<DummyLinearState>
    {
    public:
        using State<DummyLinearState>::State;
    };

    class FramedDummyLinearDiff : public framed_geometry::Difference<DummyLinearDiff>
    {
    public:
        using Difference<DummyLinearDiff>::Difference;
    };

    inline std::ostream&
    operator<<(std::ostream& os, FramedDummyLinearDiff const& rhs)
    {
        return os << rhs.to_string();
    }

    class FramedDummyAngularState : public framed_geometry::State<DummyAngularState>
    {
    public:
        using State<DummyAngularState>::State;
    };

    class FramedDummyAngularDiff : public framed_geometry::Difference<DummyAngularDiff>
    {
    public:
        using Difference::Difference;
    };

    class FramedDummySpatialState : public framed_geometry::State<DummySpatialState>
    {
    public:
        using State::State;
    };

    class FramedDummySpatialDiff : public framed_geometry::Difference<DummySpatialDiff>
    {
    public:
        using Difference::Difference;
    };

}  // namespace quant
