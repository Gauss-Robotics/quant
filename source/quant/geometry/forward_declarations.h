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

    struct ManifoldType
    {
    };

    struct R1Type : ManifoldType
    {
    };

    struct S1Type: ManifoldType
    {
    };

    struct R3Type : ManifoldType
    {
    };

    struct SO3Type : ManifoldType
    {
    };

    struct SE3Type: ManifoldType
    {
    };

    template <typename StateType, typename DifferenceType, typename ManifoldType>
    struct Define1DDomain
    {
        using DomainType = OneDimensionalDomainType;
        using State = StateType;
        using Difference = DifferenceType;
        using Manifold = ManifoldType;
    };

    template <typename StateType, typename DifferenceType, typename ManifoldType>
    struct Define3DSubDomain
    {
        using DomainType = ThreeDimensionalDomainType;
        using State = StateType;
        using Difference = DifferenceType;
        using Manifold = ManifoldType;
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
        using R3 = Define3DSubDomain<LinearStateType, LinearDifferenceType, R3Type>;
        using SO3 = Define3DSubDomain<AngularStateType, AngularDifferenceType, SO3Type>;
        using SE3 = Define3DSubDomain<SpatialStateType, SpatialDifferenceType, SE3Type>;
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

    template <typename Type>
    concept one_dimensional_domain =
        std::same_as<typename domain_type_of<Type>::DomainType, OneDimensionalDomainType>;

    template <typename Type>
    concept three_dimensional_domain =
        std::same_as<typename domain_type_of<Type>::DomainType, ThreeDimensionalDomainType>;

    template <typename StateT>
        requires state<StateT>
    using difference_type_of = typename traits_of<StateT>::Difference;

    template <typename DifferenceT>
        requires difference<DifferenceT>
    using state_type_of = typename traits_of<DifferenceT>::State;

    template <typename Type1, typename Type2>
    concept same_domain = std::same_as<domain_type_of<Type1>, domain_type_of<Type2>>;

    template <typename StateT, typename DifferenceT>
    concept same_group = std::same_as<StateT, state_type_of<DifferenceT>> and
                         std::same_as<DifferenceT, difference_type_of<StateT>>;

    template <typename Type>
    using linear_state_in_domain_of = typename domain_type_of<Type>::LinearState;

    template <typename Type>
    using angular_state_in_domain_of = typename domain_type_of<Type>::AngularState;

    template <typename Type>
    using linear_difference_in_domain_of = typename domain_type_of<Type>::LinearDifference;

    template <typename Type>
    using angular_difference_in_domain_of = typename domain_type_of<Type>::AngularDifference;

    template <typename Type>
    concept in_r1 = one_dimensional_domain<Type> and
                    std::same_as<typename domain_type_of<Type>::Manifold, R1Type>;

    template <typename Type>
    concept in_s1 = one_dimensional_domain<Type> and
                    std::same_as<typename domain_type_of<Type>::Manifold, S1Type>;

    template <typename Type>
    concept in_r3 = three_dimensional_domain<Type> and
                    (std::same_as<linear_state_in_domain_of<Type>, Type> or
                     std::same_as<linear_difference_in_domain_of<Type>, Type>);

    template <typename Type>
    concept in_so3 = three_dimensional_domain<Type> and
                     (std::same_as<angular_state_in_domain_of<Type>, Type> or
                      std::same_as<angular_difference_in_domain_of<Type>, Type>);

    template <typename Type>
    concept in_se3 = three_dimensional_domain<Type> and
                     (std::same_as<typename domain_type_of<Type>::SpatialState, Type> or
                      std::same_as<typename domain_type_of<Type>::SpatialDifference, Type>);

    template <typename Type>
    concept in_flat_space = in_r1<Type> or in_r3<Type>;

    template <typename Type>
    concept in_curved_space = in_so3<Type> or in_se3<Type>; // or in_s1<Type>;

}  // namespace quant::traits

namespace quant
{

    using geometry::AxisAngle;
    using geometry::Circa;
    using geometry::Vector;

}  // namespace quant
