#pragma once

#include <concepts>
#include <type_traits>

namespace quant::geometry
{

    struct Scalar;
    struct Vector;
    struct AxisAngle;

    template <typename StateType, typename RepresentationType>
    class ScalarState;

    template <typename BaseQuantityT>
    class LinearState;

    template <typename BaseQuantityT>
    class AngularState;

    template <typename BaseQuantityT>
    class SpatialIsometricState;

    template <typename Domain>
    class SpatialState;

    template <typename BaseQuantityT>
    class Difference;

    template <typename Domain>
    class ScalarDifference;

    template <typename Domain>
    class SpatialDifference;

    template <typename T>
    class Circa;

}  // namespace quant::geometry

namespace quant::traits
{

    struct StateType
    {
    };

    struct ScalarStateType : public StateType
    {
    };

    struct LinearStateType : public StateType
    {
    };

    struct AngularStateType : public StateType
    {
    };

    struct SpatialStateType : public StateType
    {
    };

    struct DifferenceType
    {
    };

    struct ScalarDifferenceType : public DifferenceType
    {
    };

    struct LinearDifferenceType : public DifferenceType
    {
    };

    struct AngularDifferenceType : public DifferenceType
    {
    };

    struct SpatialDifferenceType : public DifferenceType
    {
    };

    struct OneDimensionalDomainType
    {
    };

    struct ThreeDimensionalDomainType
    {
    };

    template <typename StateType, typename DifferenceType>
    struct Define1DDomain
    {
        using DomainType = OneDimensionalDomainType;
        using State = StateType;
        using Difference = DifferenceType;
    };

    template <typename LinearStateType,
              typename AngularStateType,
              typename SpatialStateType,
              typename LinearDifferenceType,
              typename AngularDifferenceType,
              typename SpatialDifferenceType>
    struct Define3DDomain
    {
        using DomainType = ThreeDimensionalDomainType;
        using LinearState = LinearStateType;
        using AngularState = AngularStateType;
        using SpatialState = SpatialStateType;
        using LinearDifference = LinearDifferenceType;
        using AngularDifference = AngularDifferenceType;
        using SpatialDifference = SpatialDifferenceType;
        using R3 = Define1DDomain<LinearStateType, LinearDifferenceType>;
        using SO3 = Define1DDomain<AngularStateType, AngularDifferenceType>;
        using SE3 = Define1DDomain<SpatialStateType, SpatialDifferenceType>;
    };

    template <typename Type>
    struct DefineTraits
    {
    };

    template <typename Type>
    using traits_of = DefineTraits<Type>;

    template <typename Type>
    concept state = std::derived_from<typename traits_of<Type>::GeometricType, StateType>;

    template <typename Type>
    concept scalar_state =
        std::derived_from<typename traits_of<Type>::GeometricType, ScalarStateType>;

    template <typename Type>
    concept linear_state =
        std::derived_from<typename traits_of<Type>::GeometricType, LinearStateType>;

    template <typename Type>
    concept angular_state =
        std::derived_from<typename traits_of<Type>::GeometricType, AngularStateType>;

    template <typename Type>
    concept spatial_state =
        std::derived_from<typename traits_of<Type>::GeometricType, SpatialStateType>;

    template <typename Type>
    concept difference = std::derived_from<typename traits_of<Type>::GeometricType, DifferenceType>;

    template <typename Type>
    concept scalar_difference =
        std::derived_from<typename traits_of<Type>::GeometricType, ScalarDifferenceType>;

    template <typename Type>
    concept linear_difference =
        std::derived_from<typename traits_of<Type>::GeometricType, LinearDifferenceType>;

    template <typename Type>
    concept angular_difference =
        std::derived_from<typename traits_of<Type>::GeometricType, AngularDifferenceType>;

    template <typename Type>
    concept spatial_difference =
        std::derived_from<typename traits_of<Type>::GeometricType, SpatialDifferenceType>;

    template <typename Type>
    using domain_type_of = typename traits_of<Type>::Domain;

    template <typename StateT>
        requires state<StateT>
    using difference_type_of = typename traits_of<StateT>::Difference;

    template <typename DifferenceT>
        requires difference<DifferenceT>
    using state_type_of = typename traits_of<DifferenceT>::State;

    template <typename Type1, typename Type2>
    concept same_domain = std::same_as<domain_type_of<Type1>, domain_type_of<Type2>>;

    template <typename Type>
    using linear_state_in_domain_of = domain_type_of<Type>::LinearState;

    template <typename Type>
    using angular_state_in_domain_of = domain_type_of<Type>::AngularState;

    template <typename Type>
    using linear_difference_in_domain_of = domain_type_of<Type>::LinearDifference;

    template <typename Type>
    using angular_difference_in_domain_of = domain_type_of<Type>::AngularDifference;

    template <typename Type>
    using r3_in_domain_of = domain_type_of<Type>::R3;

    template <typename Type>
    using so3_in_domain_of = domain_type_of<Type>::SO3;

    template <typename Type>
    using se3_in_domain_of = domain_type_of<Type>::SE3;

    template <typename Type>
    concept three_dimensional_domain =
        std::same_as<typename domain_type_of<Type>::DomainType, ThreeDimensionalDomainType>;

    template <typename Type>
    concept one_dimensional_domain =
        std::same_as<typename domain_type_of<Type>::DomainType, OneDimensionalDomainType>;

}  // namespace quant::traits

namespace quant
{

    using geometry::AxisAngle;
    using geometry::Circa;
    using geometry::Vector;

}  // namespace quant
