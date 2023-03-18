#pragma once


#include <quant/geometry/ScalarQuantity.h>
#include <quant/geometry/common.h>

#include <Eigen/Geometry>

#include <ostream>
#include <typeinfo>

namespace quant::geometry
{

    template <typename VectorType>
    class Magnitude : public ScalarQuantity<Magnitude<VectorType>>
    {
    public:
        using geometry::ScalarQuantity<Magnitude<VectorType>>::ScalarQuantity;

        Magnitude(double value) :
            geometry::ScalarQuantity<Magnitude<VectorType>>::ScalarQuantity(value)
        {
            ;  // TODO: Why is this required?!
        }
    };


    template <typename T, typename DifferenceType>
    class VectorQuantity;


    template <typename T, typename DifferenceType>
    T operator+(Difference<T> const& lhs, VectorQuantity<T, DifferenceType> const& rhs);


    template <typename T, typename DifferenceType>
    DifferenceType operator-(VectorQuantity<T, DifferenceType> const& lhs,
                             VectorQuantity<T, DifferenceType> const& rhs);

    template <typename T, typename DifferenceType = Difference<T>>
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

        Magnitude<T>
        toMagnitude() const
        {
            return Magnitude<T>(representation_.norm());
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

        Difference<T>
        deltaToOrigin() const
        {
            return Difference<T>(static_cast<const T&>(*this));
        }

        // Convert.

        std::string
        toString(std::string const& quantityName = "", std::string const& unit = "") const
        {
            const Vector v = toVector();
            std::stringstream out;
            out << "<";

            if (not quantityName.empty())
            {
                out << quantityName << " ";
            }

            out << io::toString(v, unit) << ">";
            return out.str();
        }

        // Transform.

        template <typename T_, typename DifferenceType_>
        friend T_ operator+(Difference<T_> const& lhs,
                            VectorQuantity<T_, DifferenceType_> const& rhs);

        template <typename T_, typename DifferenceType_>
        friend DifferenceType_ operator-(VectorQuantity<T_, DifferenceType_> const& lhs,
                                         VectorQuantity<T_, DifferenceType_> const& rhs);

        // Compare.

        bool
        operator==(const T& rhs) const
        {
            return representation_ == rhs.representation_;
        }

        bool
        operator!=(const T& rhs) const
        {
            return representation_ != rhs.representation_;
        }

        bool
        isApprox(const T& rhs, double precision) const
        {
            return representation_.isApprox(rhs.representation_, precision);
        }

        using QuantityType = T;
        using QuantityDifferenceType = DifferenceType;

    protected:
        Eigen::Vector3d representation_;
    };

}  // namespace quant::geometry

namespace quant
{

    template <typename T, typename DifferenceType>
    T
    geometry::operator+(Difference<T> const& lhs, VectorQuantity<T, DifferenceType> const& rhs)
    {
        return T(lhs.pointFromOrigin().representation_ + rhs.representation_);
    }

    template <typename T, typename DifferenceType>
    DifferenceType
    geometry::operator-(VectorQuantity<T, DifferenceType> const& lhs,
                        VectorQuantity<T, DifferenceType> const& rhs)
    {
        return DifferenceType(T(lhs.representation_ - rhs.representation_));
    }

}  // namespace quant
