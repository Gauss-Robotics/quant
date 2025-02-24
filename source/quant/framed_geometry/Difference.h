#pragma once

#include <quant/framed_geometry/BaseChange.h>
#include <quant/framed_geometry/FrameMismatch.h>
#include <quant/framed_geometry/forward_declarations.h>
#include <quant/geometry/Difference.h>
#include <quant/geometry/constants.h>
#include <quant/geometry/forward_declarations.h>

#include <Eigen/Core>

#include <array>
#include <cassert>
#include <compare>
#include <cstdio>
#include <string>
#include <string_view>

namespace quant::framed_geometry
{

    /**
     * @brief Wrapper to associate a named difference object with a base frame.
     *
     * On construction, the base frame strings referred to the string_views in a `Frame`
     * are copied into own internal private members (`_name_data` and `_base_frame_data`) on the
     * stack with a maximum number of chars defined in `frame_data_max_string_size`. The names can
     * be accessed using the accessors `name()` and `base_frame()`.
     *
     * @tparam QuantityT Geometric State or difference object type.
     */
    template <typename QuantityT>
        requires traits::is_frameable<QuantityT> and traits::difference<QuantityT>
    class Difference
    {
    public:
        using FramedGeometricObject = QuantityT;

        /**name and
         * @brief Constructs a framed geometric object given a geometric object and a frame header
         * consisting of a base frame and name.
         *
         * @param object_to_frame Geometric object to frame.
         * @param base_frame_name name of the frame this difference is sítuated in.
         */
        Difference(QuantityT const& object_to_frame, std::string_view const& base_frame_name) :
            _framed_object{object_to_frame}
        {

            // NOLINTBEGIN(cppcoreguidelines-pro-type-vararg)
            std::snprintf(
                _base_frame_name.data(), _base_frame_name.size(), "%s", base_frame_name.data());
            // NOLINTEND(cppcoreguidelines-pro-type-vararg)
        }

        template <typename... Args>
        Difference(std::string_view const& base_frame_name, Args&&... args) :
            _framed_object{std::forward<Args>(args)...}
        {
            // NOLINTBEGIN(cppcoreguidelines-pro-type-vararg)
            std::snprintf(
                _base_frame_name.data(), _base_frame_name.size(), "%s", base_frame_name.data());
            // NOLINTEND(cppcoreguidelines-pro-type-vararg)
        }

        Difference(typename traits::framed_traits_of<QuantityT>::FramedState const& state) :
            Difference(static_cast<QuantityT>(state.get_framed_object()), state.get_base_frame())
        {
            ;
        }

        std::string_view
        get_base_frame() const
        {
            return _base_frame_name.data();
        }

        QuantityT const&
        get_framed_object() const
        {
            return _framed_object;
        }

        bool
        is_approx(Difference const& rhs,
                  double const tolerance = geometry::constants::floating_point_tolerance) const
        {
            std::string const lhs_base_frame{get_base_frame()};
            std::string const rhs_base_frame{rhs.get_base_frame()};
            return lhs_base_frame == rhs_base_frame and
                   _framed_object.is_approx(rhs._framed_object, tolerance);
        }

        std::string
        to_string() const
        {
            std::string in_frame{get_base_frame()};  // Base frame might be empty for global frame.

            if (not in_frame.empty())
            {
                in_frame = "w.r.t. " + in_frame;
            }
            else
            {
                in_frame = "global";
            }

            return "(" + in_frame + ") at " + _framed_object.to_string();
        }

        static traits::framed_type_of<QuantityT>
        zero(std::string_view const& base_frame_name)
        {
            return traits::framed_type_of<QuantityT>{QuantityT::zero(), base_frame_name};
        }

        /**
         * @brief Default constructs a framed geometric object.
         */
        Difference() = delete;

    private:
        /**
         * @brief Name of the base frame of the held geometric object.
         *
         * This is not the same thing as a tangent space at a point in a manifold, but rather the
         * frame in which two states have been subtracted. It is only used to ascertain that a
         * difference is allowed to be added to a certain framed state.
         */
        const_size_string _base_frame_name;

        /**
         * @brief Framed geometric object.
         */
        QuantityT _framed_object;
    };

    template <typename FramedT>
        requires traits::framed_difference<FramedT>
    FramedT
    operator*(BaseChange const& transform, FramedT const& quantity)
    {
        using Traits = traits::framed_traits_of<traits::unframed_type_of<FramedT>>;
        if (transform.from_frame != quantity.get_base_frame())
        {
            throw FrameMismatchException(transform.from_frame, quantity.get_base_frame());
        }

        return FramedT{Traits::basis_change_function(quantity.get_framed_object(), transform),
                       transform.to_frame};
    }

    template <typename FramedDifferenceType>
        requires traits::framed_difference<FramedDifferenceType>
    std::ostream&
    operator<<(std::ostream& os, FramedDifferenceType const& rhs)
    {
        return os << rhs.to_string();
    }

}  // namespace quant::framed_geometry
