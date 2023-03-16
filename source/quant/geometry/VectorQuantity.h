#pragma once


#include <ostream>
#include <typeinfo>

#include <Eigen/Geometry>

#include <quant/geometry/ScalarQuantity.h>
#include <quant/geometry/common.h>


namespace simox::core::geometry
{

    template <typename VectorType>
    class Magnitude : public ScalarQuantity<Magnitude<VectorType>>
    {
    protected:
        using geometry::ScalarQuantity<Magnitude<VectorType>>::ScalarQuantity;
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
        toString(const std::string& unit = "") const
        {
            const std::string className = simox::meta::get_type_name(typeid(T));

            const Vector v = toVector();
            std::stringstream out;
            out << "<" << className << " " << io::toString(v, unit) << ">";
            return out.str();
        }

        // Transform.

        template <typename _T, typename _DifferenceType>
        friend _T operator+(const Difference<_T>& lhs,
                            const VectorQuantity<_T, _DifferenceType>& rhs);

        template <typename _T, typename _DifferenceType>
        friend _DifferenceType operator-(const VectorQuantity<_T, _DifferenceType>& lhs,
                                         const VectorQuantity<_T, _DifferenceType>& rhs);

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

    protected:
        Eigen::Vector3d representation_;
    };

} // namespace simox::core::geometry


namespace simox::core
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

} // namespace simox::core
