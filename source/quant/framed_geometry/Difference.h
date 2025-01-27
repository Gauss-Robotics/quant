#pragma once

#include <quant/framed_geometry/BaseChange.h>
#include <quant/framed_geometry/FrameMismatch.h>
#include <quant/framed_geometry/forward_declarations.h>
#include <quant/geometry/Difference.h>
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
        Difference(QuantityT const& object_to_frame,
                         std::string_view const& base_frame_name) :
            _framed_object{object_to_frame}
        {
            // NOLINTBEGIN(cppcoreguidelines-pro-type-vararg)
            std::snprintf(
                _base_frame_name.data(), _base_frame_name.size(), "%s", base_frame_name.data());
            // NOLINTEND(cppcoreguidelines-pro-type-vararg)
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

            return  "(" + in_frame + ") at " + _framed_object.to_string();
        }

    protected:
        /**
         * @brief Default constructs a framed geometric object.
         */
        Difference() :
            Difference(QuantityT::zero(),
                             "::")  // prohibits the creation of Base objects, which is UB
        {
            ;
        }

    private:
        /**
         * @brief Name of the base frame of the held geometric object.
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
#ifdef QUANT_ENABLE_EXCEPTIONS
        if (transform.from_frame != quantity.get_base_frame())
        {
            throw FrameMismatchException(transform.from_frame, quantity.get_base_frame());
        }
#endif

        return FramedT{Traits::basis_change_function(quantity.get_framed_object(), transform),
                       transform.to_frame};
    }

#ifdef QUANT_ENABLE_DIFFERENCE_ADDITION
    /**
     * @brief State difference operator.
     *
     * @param lhs
     * @param rhs
     * @return
     */
    template <typename FramedDifferenceType>
        requires traits::framed_difference<FramedDifferenceType>
    FramedDifferenceType
    operator-(FramedDifferenceType const& lhs, FramedDifferenceType const& rhs)
    {
#ifdef QUANT_ENABLE_EXCEPTIONS
        if (lhs.get_base_frame() != rhs.get_base_frame())
        {
            throw FrameMismatchException(lhs.get_base_frame(), rhs.get_base_frame());
        }
#endif

        return FramedDifferenceType(lhs.get_framed_object() - rhs.get_framed_object(),
                                    rhs.get_base_frame());
    }

    /**
     * @brief Translation application operator.
     *
     * @param state
     * @param difference
     * @return
     */
    template <typename FramedDifferenceType>
        requires traits::framed_difference<FramedDifferenceType>
    FramedDifferenceType
    operator+(FramedDifferenceType const& lhs, FramedDifferenceType const& rhs)
    {
        using StateType = typename FramedDifferenceType::FramedGeometricObject;

#ifdef QUANT_ENABLE_EXCEPTIONS
        if (lhs.get_base_frame() != rhs.get_base_frame())
        {
            throw FrameMismatchException(lhs.get_base_frame(), rhs.get_base_frame());
        }
#endif
        return traits::framed_type_of<StateType>(lhs.get_framed_object() + rhs.get_framed_object(),
                                                 lhs.get_base_frame());
    }
#endif

    template <typename FramedDifferenceType>
        requires traits::framed_scalar_difference<FramedDifferenceType>
    FramedDifferenceType
    operator-(FramedDifferenceType const& object)
    {
        return FramedDifferenceType{
            -object.get_framed_object(),
            FrameIdentifier{.name = object.get_name(), .base_frame = object.get_base_frame()}};
    }

}  // namespace quant::framed_geometry
