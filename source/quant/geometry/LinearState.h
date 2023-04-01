#pragma once

#include <quant/geometry/Vector.h>
#include <quant/geometry/detail/QuantityAccessor.h>

#include <Eigen/Geometry>

#include <ostream>
#include <typeinfo>

namespace quant::geometry
{

    template <typename Domain>
    class LinearState
    {
    public:
        // Construct.

        /**
         * @brief VectorQuantity
         */
        LinearState() : representation_(0, 0, 0)
        {
            ;
        }

        /**
         * @brief Zero
         * @return
         */
        static typename Domain::LinearState
        zero()
        {
            return typename Domain::LinearState(0, 0, 0);
        }

        // Convert.

        /**
         * @brief toString
         * @param quantityName
         * @param unit
         * @return
         */
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
        operator==(typename Domain::LinearState const& rhs) const
        {
            return representation_ == rhs.representation_;
        }

        bool
        operator!=(typename Domain::LinearState const& rhs) const
        {
            return representation_ != rhs.representation_;
        }

        bool
        isApprox(typename Domain::LinearState const& rhs, double precision) const
        {
            return representation_.isApprox(rhs.representation_, precision);
        }

        using GeometricRepresentationType = Eigen::Ref<Eigen::Vector3d const>;
        using GeometricType = traits::StateType;
        using DomainType = Domain;

    protected:
        // Construct.

        LinearState(double x, double y, double z) : representation_(x, y, z)
        {
            ;
        }

        LinearState(Vector const& xyz) : representation_(xyz.x, xyz.y, xyz.z)
        {
            ;
        }

        LinearState(Eigen::Ref<Eigen::Vector3d const> vector) : representation_(vector)
        {
            ;
        }

        // Convert.

        Vector
        toVector() const
        {
            return Vector::fromEigen(representation_);
        }

        Eigen::Vector3d representation_;

        friend class detail::QuantityAccessor<typename Domain::LinearState>;
    };

}  // namespace quant::geometry
