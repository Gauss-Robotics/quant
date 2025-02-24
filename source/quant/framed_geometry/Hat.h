#pragma once
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/units/position/forward_declarations.h>

#include <Eigen/Core>

#include "forward_declarations.h"

namespace quant::framed_geometry
{
    /**
     * @brief Hat operator, transforming an element of linear space to a tangent space element of
     * SO(3).
     *
     * @see Eq. (10) in https://arxiv.org/pdf/1812.01537
     */
    class HatSO3
    {
    public:
        HatSO3(units::position::LinearDisplacement const& linear_displacement);
        HatSO3(Eigen::Vector3d const& vector);

        Eigen::Matrix3d
        operator*(units::position::AngularDisplacement const& angular_displacement) const;

        Eigen::Matrix3d
        operator*(Eigen::Matrix3d const& rhs) const;

        Eigen::Matrix3d
        matrix() const;

    private:
        Eigen::Matrix3d _matrix;
    };

    /**
     * @brief Hat operator, transforming an element of linear space to a tangent space element of
     * SE(3).
     *
     * @see Eq. (10) in https://arxiv.org/pdf/1812.01537
     */
    class HatSE3
    {
    public:
        template <typename StateT>
            requires traits::state<StateT>
        HatSE3(geometry::SE3TangentState<StateT> const& state) :
            HatSE3(geometry::detail::StateAccessor<StateT>::representation(state))
        {
            ;
        };

        template <typename StateT>
            requires traits::framed_spatial_state<StateT>
        HatSE3(StateT const& state) :
            HatSE3(
                geometry::detail::StateAccessor<traits::unframed_type_of<StateT>>::representation(
                    state.get_framed_object()))
        {
            ;
        }

        HatSE3(Eigen::Vector<double, 6> const& vector);

        Eigen::Matrix4d
        matrix() const;

    private:
        Eigen::Matrix4d _matrix;
    };
}  // namespace quant::framed_geometry