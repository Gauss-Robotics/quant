#pragma once

#include <quant/geometry/detail/Accessors.h>

#include <Eigen/Geometry>

#include <ostream>
#include <typeinfo>

namespace quant::geometry
{

    template <typename BaseQuantityT>
    class IsometryQuantity
    {
        // Construct.
    public:
        IsometryQuantity() : representation_(Eigen::Isometry3d::Identity())
        {
            ;
        }

        static BaseQuantityT
        Origin()
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
        isApprox(BaseQuantityT const& rhs, double const precision) const
        {
            return representation_.isApprox(rhs._representation, precision);
        }

        using Representation = Eigen::Isometry3d const&;

    protected:
        IsometryQuantity(Eigen::Isometry3d const& tf) : representation_(tf)
        {
            ;
        }

        IsometryQuantity(Eigen::Ref<const Eigen::Matrix4f> const& tf) :
            representation_(tf.cast<double>())
        {
            ;
        }

        IsometryQuantity(Eigen::Ref<const Eigen::Matrix4d> const& tf) : representation_(tf)
        {
            ;
        }

        Eigen::Isometry3d representation_;

        friend class detail::Accessor<BaseQuantityT>;
    };

}  // namespace quant::geometry
