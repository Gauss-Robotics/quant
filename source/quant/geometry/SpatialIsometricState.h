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
        SpatialIsometricState() : representation_(Eigen::Isometry3d::Identity())
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
            return representation_ == rhs._representation;
        }

        bool
        operator!=(BaseQuantityT const& rhs) const
        {
            return representation_ != rhs._representation;
        }

        bool
        is_approx(BaseQuantityT const& rhs, double const precision) const
        {
            return representation_.isApprox(rhs._representation, precision);
        }

        using GeometricRepresentationType = Eigen::Isometry3d const&;
        using GeometricType = traits::StateType;

    protected:
        SpatialIsometricState(Eigen::Isometry3d const& tf) : representation_(tf)
        {
            ;
        }

        SpatialIsometricState(Eigen::Ref<const Eigen::Matrix4f> const& tf) :
            representation_(tf.cast<double>())
        {
            ;
        }

        SpatialIsometricState(Eigen::Ref<const Eigen::Matrix4d> const& tf) : representation_(tf)
        {
            ;
        }

        Eigen::Isometry3d representation_;

        friend class detail::QuantityAccessor<BaseQuantityT>;
    };

}  // namespace quant::geometry
