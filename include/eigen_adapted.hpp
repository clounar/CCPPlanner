// clang-format off
#ifndef CCP_PLANNER_EIGEN_ADAPTED_HPP
#define CCP_PLANNER_EIGEN_ADAPTED_HPP

#include <Eigen/Core>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/tags.hpp>

namespace boost::geometry::traits
{
    template <typename T, int... D> struct tag<::Eigen::Matrix<T, D...> > { using type = point_tag; };
    template <typename T, int... D> struct tag<::Eigen::Array<T, D...> > { using type = point_tag; };

    template<typename Scalar, int cols, int options>
    struct dimension<::Eigen::Matrix<Scalar, 1, cols, options, 1, cols> > : boost::mpl::int_<cols> {};
    template<typename Scalar, int cols, int options>
    struct dimension<::Eigen::Array<Scalar, 1, cols, options, 1, cols> > : boost::mpl::int_<cols> {};
    template<typename Scalar, int rows, int options>
    struct dimension<::Eigen::Matrix<Scalar, rows, 1, options, rows, 1> > : boost::mpl::int_<rows> {};
    template<typename Scalar, int rows, int options>
    struct dimension<::Eigen::Array<Scalar, rows, 1, options, rows, 1> > : boost::mpl::int_<rows> {};
    template<typename Scalar, int options>
    struct dimension<::Eigen::Matrix<Scalar, 1, 1, options, 1, 1> > : boost::mpl::int_<1> {};
    template<typename Scalar, int options>
    struct dimension<::Eigen::Array<Scalar, 1, 1, options, 1, 1> > : boost::mpl::int_<1> {};

    template <typename T, int... D> struct coordinate_type<::Eigen::Matrix<T, D...> > { using type = T; };
    template <typename T, int... D> struct coordinate_type<::Eigen::Array<T, D...> > { using type = T; };
    template <typename T, int... D> struct coordinate_system<::Eigen::Matrix<T, D...> > { using type = boost::geometry::cs::cartesian; };
    template <typename T, int... D> struct coordinate_system<::Eigen::Array<T, D...> > { using type = boost::geometry::cs::cartesian; };

    template <typename T, int... D, std::size_t index>
    struct access<::Eigen::Matrix<T, D...>, index> {
        using Point = ::Eigen::Matrix<T, D...>;
        static constexpr size_t dim = dimension<Point>::value;
        static_assert(index < dim, "Out of range");
        using CoordinateType = typename coordinate_type<Point>::type;
        static inline CoordinateType get(Point const& p) { return p(index); }
        static inline void set(Point& p, CoordinateType const& value) { p(index) = value; }
    };
    template <typename T, int... D, std::size_t index>
    struct access<::Eigen::Array<T, D...>, index> {
        using Point = ::Eigen::Array<T, D...>;
        static constexpr size_t dim = dimension<Point>::value;
        static_assert(index < dim, "Out of range");
        using CoordinateType = typename coordinate_type<Point>::type;
        static inline CoordinateType get(Point const& p) { return p(index); }
        static inline void set(Point& p, CoordinateType const& value) { p(index) = value; }
    };
} // namespace boost::geometry::traits
// clang-format on

#endif  // CCP_PLANNER_EIGEN_ADAPTED_HPP
