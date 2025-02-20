#pragma once

#include <quant/units/position/SpatialDisplacement.h>

#include "forward_declarations.h"

namespace quant::framed_geometry
{
    class SkewSymmetric3d
    {
    public:
        SkewSymmetric3d(units::position::LinearDisplacement const& linear_displacement);
        SkewSymmetric3d(Eigen::Vector3d const& vector);

        Eigen::Matrix3d
        operator*(AngularDisplacement const& angular_displacement) const;

        Eigen::Matrix3d
        operator*(Eigen::Matrix3d const& rhs) const;

        Eigen::Matrix3d
        matrix() const;

    private:
        Eigen::Matrix3d _matrix;
    };

    class SkewSymmetric6d
    {
    public:
        template <typename StateT>
            requires traits::state<StateT>
        SkewSymmetric6d(geometry::SE3TangentState<StateT> const& state) :
            SkewSymmetric6d(geometry::detail::StateAccessor<StateT>::representation(state))
        {
            ;
        }

        template <typename StateT>
            requires traits::framed_spatial_state<StateT>
        SkewSymmetric6d(StateT const& state) :
            SkewSymmetric6d(geometry::detail::StateAccessor<traits::unframed_type_of<StateT>>::representation(state.get_framed_object()))
        {
            ;
        }

        SkewSymmetric6d(Eigen::Vector<double, 6> const& vector);

        Eigen::Matrix4d
        matrix() const;

    private:
        Eigen::Matrix4d _matrix;
    };

    class Adjoint
    {
        using Matrix6d = Eigen::Matrix<double, 6, 6>;

    public:
        Adjoint(units::position::SpatialDisplacement const& spatial_displacement);
        Adjoint(Eigen::Isometry3d const& transformation);

        Matrix6d
        matrix() const;

        Eigen::Vector<double, 6>
        operator*(Eigen::Vector<double, 6> const& rhs) const;

    private:
        Matrix6d _matrix;
    };
}  // namespace quant::framed_geometry