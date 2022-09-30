#ifndef CCP_PLANNER_GEOMETRY_TYPEDEF_HPP
#define CCP_PLANNER_GEOMETRY_TYPEDEF_HPP

#include <Eigen/Core>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/multi_point.hpp>
#include <boost/geometry/geometries/multi_linestring.hpp>
#include <boost/geometry/geometries/multi_polygon.hpp>
#include <eigen_adapted.hpp>

namespace ccp {
typedef ::Eigen::Vector2d Point;
typedef ::boost::geometry::model::box<Point> Box;
typedef ::boost::geometry::model::linestring<Point> LineString;
typedef ::boost::geometry::model::ring<Point> Ring;
typedef ::boost::geometry::model::polygon<Point> Polygon;
typedef ::boost::geometry::model::multi_point<Point> MultiPoint;
typedef ::boost::geometry::model::multi_linestring<LineString> MultiLineString;
typedef ::boost::geometry::model::multi_polygon<Polygon> MultiPolygon;
typedef ::boost::geometry::traits::coordinate_type<Point>::type NumericType;

typedef NumericType g_float;

}  // namespace ccp

#endif  // CCP_PLANNER_GEOMETRY_TYPEDEF_HPP
