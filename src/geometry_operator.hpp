#ifndef CCP_PLANNER_GEOMETRY_OPERATOR_HPP
#define CCP_PLANNER_GEOMETRY_OPERATOR_HPP

#include <boost/geometry.hpp>
#include <geometry_typedef.hpp>
#include <cmath>

namespace ccp {
struct Parameter {
    constexpr static inline g_float path_bias = .5;
    constexpr static inline size_t circle_point_num = 50;
};

template <typename GeometryIn, typename MultiPolygon>
static inline void buffer(const GeometryIn& geometry_in, MultiPolygon& geometry_out, NumericType dis) {
    size_t point_pre_circle = static_cast<size_t>(Parameter::circle_point_num * std::abs(dis));
    boost::geometry::buffer(geometry_in, geometry_out,
                            boost::geometry::strategy::buffer::distance_symmetric<NumericType>{dis},
                            boost::geometry::strategy::buffer::side_straight{},
                            boost::geometry::strategy::buffer::join_round{point_pre_circle},
                            boost::geometry::strategy::buffer::end_round{point_pre_circle},
                            boost::geometry::strategy::buffer::point_circle{point_pre_circle});
}

template <typename GeometryIn, typename Selector>
auto select(const GeometryIn& geometry_in, const Selector& selector) {
    using namespace boost::geometry;
    //static_assert(std::is_base_of_v<multi_tag, typename traits::tag<GeometryIn>::type>, "input type must have multi_tag");
    std::vector<typename GeometryIn::const_iterator> res;
    for (auto it= geometry_in.cbegin(); it!=geometry_in.cend();++it) {
        if (!disjoint(*it, selector))
            res.push_back(it);
    }
    return res;
}

}  // namespace ccp
#endif  // CCP_PLANNER_GEOMETRY_OPERATOR_HPP
