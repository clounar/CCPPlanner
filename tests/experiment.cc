#include <boost/geometry/geometry.hpp>
#include "save_svg.hpp"
#include <doctest/doctest.h>
#include <geometry_typedef.hpp>
#include "../src/geometry_operator.hpp"
#include "../src/contour_mode.h"
#include "../src/zigzag_mode.h"
#include "assets.h"
#include <algorithm>
#include <glog/logging.h>

template<class CcpImpl>
void std_ccp_test(CcpImpl impl_ins, ccp::MultiPolygon work_area)
{
    ccp::MultiLineString res;
    ccp::MultiPoint starts;
    res.push_back(impl_ins.prepare(work_area));
    starts.push_back(res.back().front());
    while (!impl_ins.is_complete()) {
        res.push_back(impl_ins.calculate_next_seg());
        starts.push_back(res.back().front());
    }
}

template<class CcpImpl>
void ccp_debug(CcpImpl impl_ins, ccp::MultiPolygon work_area, const std::string& file_name)
{
    ccp::MultiLineString res;
    ccp::MultiPoint starts;
    res.push_back(impl_ins.prepare(work_area));
    starts.push_back(res.back().front());
    save_svg(file_name, work_area, res, starts);
    while (!impl_ins.is_complete()) {
        res.push_back(impl_ins.calculate_next_seg());
        starts.push_back(res.back().front());
        save_svg(file_name, work_area, res, starts);
    }
}

TEST_CASE("contour") {
    using namespace boost::geometry;
    ccp::MultiPolygon work_area;
    read_wkt("MULTIPOLYGON(((0 0,0 16,16 16,16 0,0 0)))", work_area);
    ccp_debug(ccp::ContourMode{1},work_area,"contour.svg");
}

TEST_CASE("zigzag1") {ccp_debug(ccp::ZigzagMode{0.5},gen_test_area1(),"zigzag1.svg");}
TEST_CASE("zigzag2") {
    using namespace boost::geometry;
    ccp::MultiPolygon work_area;
    read_wkt(raw_wkt, work_area);
    ccp_debug(ccp::ZigzagMode{0.5},work_area,"contour.svg");
}

TEST_CASE("zigzag_demo") {
    using namespace ccp;
    using namespace boost::geometry;
    MultiPolygon work_area;
    MultiPolygon inflate;
    model::box<Point> ref_line;
    Polygon inner_polygon;
    MultiPolygon divide_area;
    read_wkt("MULTIPOLYGON(((0 0,0 16,16 16,16 0,0 0),(4 4,12 3,5 8,12 13,4 12,4 4)))", work_area);
    save_svg("zigzag/raw_area.svg", work_area);
    ccp::buffer(work_area, inflate, -1);
    save_svg("zigzag/inflate.svg", work_area, inflate);
    boost::geometry::read_wkt("BOX(8 1,8.00001 15)", ref_line);
    save_svg("zigzag/ref_line_gen.svg", work_area, inflate, ref_line);
    convert(inflate.front().inners().front(), inner_polygon);
    reverse(inner_polygon);
    union_(inner_polygon, ref_line, divide_area);
    Point a = *divide_area.front().outer().begin();
    save_svg("zigzag/divide_area.svg", work_area, divide_area);

    auto it1 = std::find_if(divide_area.front().outer().begin(), divide_area.front().outer().end(), [](const Point& p) {
        return p.y() == 1 || p.y() == 15;
    });
    decltype(it1) it2;
    if (it1->y() == 15) {
        it2 = std::find_if(it1, divide_area.front().outer().end(), [](const Point& p) {
            return p.y() == 1;
        });
    } else {
        it2 = std::find_if(it1, divide_area.front().outer().end(), [](const Point& p) {
            return p.y() == 15;
        });
    }
    LineString path1{it1, it2 + 1};
    LineString path2{it2, divide_area.front().outer().end()};
    path2.insert(path2.end(), divide_area.front().outer().begin(), it1 + 1);
    save_svg("zigzag/path_gen1.svg", work_area, path1);
    save_svg("zigzag/path_gen2.svg", work_area, path2);
}

/*TEST_CASE("box") {
    ccp::Box a{{1,2},{1,1}};
    LOG(INFO)<<a.max_corner().x()<<','<<a.max_corner().y();
    boost::geometry::correct(a);
    LOG(INFO)<<a.max_corner().x()<<','<<a.max_corner().y();
    ccp::Box b{{1,2},{2,1}};
    LOG(INFO)<<b.max_corner().x()<<','<<b.max_corner().y();
    boost::geometry::correct(b);
    LOG(INFO)<<b.max_corner().x()<<','<<b.max_corner().y();
    b.max_corner().x()=0;
    b.max_corner().y()=0;
    LOG(INFO)<<b.max_corner().x()<<','<<b.max_corner().y();
}*/
