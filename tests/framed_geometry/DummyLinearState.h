#pragma once
#include <quant/framed_geometry/Framed.h>
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
            using Difference = DummyLinearDiff;
            using GeometricType = LinearStateType;
        };

        template <>
        struct DefineTraits<DummyLinearDiff>
        {
            using Domain = DummyDomain;
            using State = DummyLinearState;
            using GeometricType = LinearDifferenceType;
        };

        template <>
        struct DefineTraits<DummyAngularState>
        {
            using Domain = DummyDomain;
            using Difference = DummyAngularDiff;
            using GeometricType = AngularStateType;
        };

        template <>
        struct DefineTraits<DummyAngularDiff>
        {
            using Domain = DummyDomain;
            using State = DummyAngularState;
            using GeometricType = AngularDifferenceType;
        };

        template <>
        struct DefineTraits<DummySpatialState>
        {
            using Domain = DummyDomain;
            using Difference = DummySpatialDiff;
            using GeometricType = SpatialStateType;
        };

        template <>
        struct DefineTraits<DummySpatialDiff>
        {
            using Domain = DummyDomain;
            using State = DummySpatialState;
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
        struct DefineFramedTraits<DummyLinearState>
        {
            using FramedDomain = FramedDummyDomain;
            using FramedDifference = FramedDummyLinearDiff;
            using Framed = FramedDummyLinearState;
            static constexpr auto basis_change_function =
                [](DummyLinearState const&, units::position::SpatialDisplacement const&)
            { return DummyLinearState{}; };
        };

        template <>
        struct DefineFramedTraits<DummyLinearDiff>
        {
            using FramedDomain = FramedDummyDomain;
            using FramedState = FramedDummyLinearState;
            using Framed = FramedDummyLinearDiff;
            static constexpr auto basis_change_function =
                [](DummyLinearDiff const&, units::position::SpatialDisplacement const&)
            { return DummyLinearDiff{}; };
        };

        template <>
        struct DefineFramedTraits<DummyAngularState>
        {
            using FramedDomain = FramedDummyDomain;
            using FramedDifference = FramedDummyAngularDiff;
            using Framed = FramedDummyAngularState;
            static constexpr auto basis_change_function =
                [](DummyAngularState const&, units::position::SpatialDisplacement const&)
            { return DummyAngularState{}; };
        };

        template <>
        struct DefineFramedTraits<DummyAngularDiff>
        {
            using FramedDomain = FramedDummyDomain;
            using FramedState = FramedDummyAngularState;
            using Framed = FramedDummyAngularDiff;
            static constexpr auto basis_change_function =
                [](DummyAngularDiff const&, units::position::SpatialDisplacement const&)
            { return DummyAngularDiff{}; };
        };

        template <>
        struct DefineFramedTraits<DummySpatialState>
        {
            using FramedDomain = FramedDummyDomain;
            using FramedDifference = FramedDummySpatialDiff;
            using Framed = FramedDummySpatialState;
            static constexpr auto basis_change_function =
                [](DummySpatialState const&, units::position::SpatialDisplacement const&)
            { return DummySpatialState::zero(); };
        };

        template <>
        struct DefineFramedTraits<DummySpatialDiff>
        {
            using FramedDomain = FramedDummyDomain;
            using FramedState = FramedDummySpatialState;
            using Framed = FramedDummySpatialDiff;
            static constexpr auto basis_change_function =
                [](DummySpatialDiff const&, units::position::SpatialDisplacement const&)
            { return DummySpatialDiff{}; };
        };
    }  // namespace traits

    class FramedDummyLinearState : public Framed<DummyLinearState>
    {
    public:
        using Framed<DummyLinearState>::Framed;
    };

    class FramedDummyLinearDiff : public Framed<DummyLinearDiff>
    {
    public:
        using Framed<DummyLinearDiff>::Framed;
    };

    inline std::ostream&
    operator<<(std::ostream& os, FramedDummyLinearDiff const& rhs)
    {
        return os << rhs.to_string();
    }

    class FramedDummyAngularState : public Framed<DummyAngularState>
    {
    public:
        using Framed<DummyAngularState>::Framed;
    };

    class FramedDummyAngularDiff : public Framed<DummyAngularDiff>
    {
    public:
        using Framed::Framed;
    };

    class FramedDummySpatialState : public Framed<DummySpatialState>
    {
    public:
        using Framed::Framed;
    };

    class FramedDummySpatialDiff : public Framed<DummySpatialDiff>
    {
    public:
        using Framed::Framed;
    };

}  // namespace quant
