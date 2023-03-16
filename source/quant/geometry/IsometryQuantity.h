#pragma once


#include <ostream>
#include <typeinfo>

#include <Eigen/Geometry>


namespace simox::core::geometry
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
        isApprox(const T& rhs, const double precision) const
        {
            return representation_.isApprox(rhs._representation, precision);
        }

    protected:
        IsometryQuantity(const Eigen::Isometry3d& tf) : representation_(tf)
        {
            ;
        }

        IsometryQuantity(const Eigen::Ref<const Eigen::Matrix4f>& tf) :
            representation_(tf.cast<double>())
        {
            ;
        }

        IsometryQuantity(const Eigen::Ref<const Eigen::Matrix4d>& tf) : representation_(tf)
        {
            ;
        }

        Eigen::Isometry3d representation_;
    };

} // namespace simox::core::geometry::representation
