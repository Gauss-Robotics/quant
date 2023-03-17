#pragma once


#include <ostream>
#include <typeinfo>

#include <Eigen/Geometry>

#include <quant/geometry/ScalarQuantity.h>
#include <quant/geometry/common.h>


namespace quant::geometry
{

    template <typename VectorType>
    class Magnitude : public ScalarQuantity<Magnitude<VectorType>>
    {
    public:
        using geometry::ScalarQuantity<Magnitude<VectorType>>::ScalarQuantity;

        Magnitude(double value) : geometry::ScalarQuantity<Magnitude<VectorType>>::ScalarQuantity(value)
        {
            ;  // TODO: Why is this required?!
        }
    };


    template <typename T, typename DifferenceType>
    class VectorQuantity;


    template <typename T, typename DifferenceType>
    T operator+(const Difference<T>& lhs, const VectorQuantity<T, DifferenceType>& rhs);


    template <typename T, typename DifferenceType>
    DifferenceType operator-(const VectorQuantity<T, DifferenceType>& lhs,
                             const VectorQuantity<T, DifferenceType>& rhs);


    template <typename T, typename DifferenceType = Difference<T>>
    class VectorQuantity
    {
    protected:
        // Construct.

        VectorQuantity(double x, double y, double z) : representation_(x, y, z)
        {
            ;
        }

        VectorQuantity(const Vector& xyz) : representation_(xyz.x, xyz.y, xyz.z)
        {
            ;
        }

        VectorQuantity(const Eigen::Vector3d& vector) : representation_(vector)
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

        VectorQuantity(const Difference<T>& deltaP) : VectorQuantity(deltaP.pointFromOrigin())
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
        toString(const std::string& quantityName = "", const std::string& unit = "") const
        {
            const Vector v = toVector();
            std::stringstream out;
            out << "<";

            if (quantityName.size() > 0)
            {
                out << quantityName << " ";
            }

            out << io::toString(v, unit) << ">";
            return out.str();
        }

        // Transform.

        template <typename T_, typename DifferenceType_>
        friend T_ operator+(const Difference<T_>& lhs,
                            const VectorQuantity<T_, DifferenceType_>& rhs);

        template <typename T_, typename DifferenceType_>
        friend DifferenceType_ operator-(const VectorQuantity<T_, DifferenceType_>& lhs,
                                         const VectorQuantity<T_, DifferenceType_>& rhs);

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

} // namespace quant::geometry


namespace quant
{

    template <typename T, typename DifferenceType>
    T
    geometry::operator+(const Difference<T>& lhs, const VectorQuantity<T, DifferenceType>& rhs)
    {
        return T(lhs.pointFromOrigin().representation_ + rhs.representation_);
    }

    template <typename T, typename DifferenceType>
    DifferenceType
    geometry::operator-(const VectorQuantity<T, DifferenceType>& lhs,
                        const VectorQuantity<T, DifferenceType>& rhs)
    {
        return DifferenceType(T(lhs.representation_ - rhs.representation_));
    }

} // namespace quant
