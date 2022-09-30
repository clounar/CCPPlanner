#ifndef CCP_PLANNER_SAVE_SVG_HPP
#define CCP_PLANNER_SAVE_SVG_HPP

#include <string>
#include <fstream>
#include <boost/geometry/io/svg/svg_mapper.hpp>

#define SVG_STYLE_STRING(fc, sc) "fill-rule:nonzero;fill-opacity:0.3;stroke-width:2;fill:" #fc ";stroke:" #sc ";"
static constexpr const char* svg_style_set[] = {
    SVG_STYLE_STRING(blue, navy),
    SVG_STYLE_STRING(yellow, gold),
    SVG_STYLE_STRING(lime, limegreen),
    SVG_STYLE_STRING(red, maroon),
    SVG_STYLE_STRING(gray, black),
    SVG_STYLE_STRING(green, darkgreen),
    SVG_STYLE_STRING(aqua, turquoise),
    SVG_STYLE_STRING(darkorchid, purple),
};

template <typename Point, typename Geometry, typename... Geometries>
void save_svg_expand(boost::geometry::svg_mapper<Point>& mapper, const char* const* style, Geometry const& geometry, Geometries const&... geometries) {
    mapper.add(geometry);
    if constexpr (sizeof...(Geometries))
        save_svg_expand(mapper, style + 1, geometries...);
    mapper.map(geometry, *style);
}

template <typename Geometry, typename... Geometries>
void save_svg(std::string const& file_path, Geometry const& geometry, Geometries const&... geometries) {
    static_assert(sizeof(svg_style_set) / sizeof(char*) > sizeof...(Geometries), "ops");
    std::ofstream svg_file(file_path.c_str());
    boost::geometry::svg_mapper<typename boost::geometry::point_type<Geometry>::type> mapper(svg_file, 500, 500);
    save_svg_expand(mapper, svg_style_set, geometry, geometries...);
}

#endif  // CCP_PLANNER_SAVE_SVG_HPP
