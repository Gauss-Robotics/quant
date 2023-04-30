#pragma once

#include <quant/geometry/detail/QuantityAccessor.h>

#include <Eigen/Geometry>

namespace quant::geometry
{

    template <typename BaseQuantityT>
    class SpatialIsometricState
    {
        // Construct.
    public:
        SpatialIsometricState() : _representation(Eigen::Isometry3d::Identity())
        {
            ;
        }

        static BaseQuantityT
        zero()
        {
            return BaseQuantityT{Eigen::Isometry3d::Identity()};
        }

        // Compare.

        bool
        operator==(BaseQuantityT const& rhs) const
        {
            return _representation == rhs._representation;
        }

        bool
        operator!=(BaseQuantityT const& rhs) const
        {
            return _representation != rhs._representation;
        }

        bool
        is_approx(BaseQuantityT const& rhs, double const tolerance) const
        {
            return _representation.isApprox(rhs._representation, tolerance);
        }

        using GeometricRepresentationType = Eigen::Isometry3d const&;
        using GeometricType = traits::StateType;

    protected:
        SpatialIsometricState(Eigen::Isometry3d const& tf) : _representation(tf)
        {
            ;
        }

        SpatialIsometricState(Eigen::Ref<const Eigen::Matrix4f> const& tf) :
            _representation(tf.cast<double>())
        {
            ;
        }

        SpatialIsometricState(Eigen::Ref<const Eigen::Matrix4d> const& tf) : _representation(tf)
        {
            ;
        }

        Eigen::Isometry3d _representation;
        
        friend class detail::StateAccessor<BaseQuantityT>;
    };

}  // namespace quant::geometry
