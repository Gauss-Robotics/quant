#pragma once


#include <Eigen/Geometry>

#include <ostream>
#include <typeinfo>

namespace quant::geometry
{

    template <typename T>
    class IsometryQuantity
    {
        // Construct.
    public:
        IsometryQuantity() : representation_(Eigen::Isometry3d::Identity())
        {
            ;
        }

        // Compare.

        bool
        operator==(const T& rhs) const
        {
            return representation_ == rhs._representation;
        }

        bool
        operator!=(const T& rhs) const
        {
            return representation_ != rhs._representation;
        }

        bool
        isApprox(const T& rhs, double const precision) const
        {
            return representation_.isApprox(rhs._representation, precision);
        }

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
    };

}  // namespace quant::geometry