#pragma once

#include <quant/geometry/Difference.h>
#include <quant/geometry/Vector.h>

#include <Eigen/Geometry>

#include <ostream>
#include <typeinfo>

namespace quant::geometry
{

    template <typename T>
    class VectorQuantity
    {
    protected:
        // Construct.

        VectorQuantity(double x, double y, double z) : representation_(x, y, z)
        {
            ;
        }

        VectorQuantity(Vector const& xyz) : representation_(xyz.x, xyz.y, xyz.z)
        {
            ;
        }

        VectorQuantity(Eigen::Vector3d const& vector) : representation_(vector)
        {
            ;
        }

        // Convert.

        Vector
        toVector() const
        {
            return Vector::FromEigen(representation_);
        }

    public:
        // Construct.

        VectorQuantity() : representation_(0, 0, 0)
        {
            ;
        }

        VectorQuantity(Difference<T> const& deltaP) : VectorQuantity(deltaP.pointFromOrigin())
        {
            ;
        }

        static T
        Origin()
        {
            return T(0, 0, 0);
        }

        // Convert.

        std::string
        toString(std::string const& quantityName = "", std::string const& unit = "") const
        {
            std::stringstream out;
            out << "<";

            if (not quantityName.empty())
            {
                out << quantityName << " ";
            }

            out << toVector().toString(unit) << ">";
            return out.str();
        }

        // Compare.

        bool
        operator==(T const& rhs) const
        {
            return representation_ == rhs.representation_;
        }

        bool
        operator!=(T const& rhs) const
        {
            return representation_ != rhs.representation_;
        }

        bool
        isApprox(T const& rhs, double precision) const
        {
            return representation_.isApprox(rhs.representation_, precision);
        }

    public:  // TODO(dreher): Make protected.
        Eigen::Vector3d representation_;

        friend class Difference<T>;
        friend class AngularDisplacement;
    };

}  // namespace quant::geometry
