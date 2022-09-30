#ifndef CCP_PLANNER_ASSETS_H
#define CCP_PLANNER_ASSETS_H

#include "../src/geometry_operator.hpp"

auto raw_wkt="MULTIPOLYGON(((26.328 38.450,49.902 44.524,55.449 16.268,37.96875 -8.205,30 5,-33.242 -4.884,-20.410 20.157,-18.476 45.711,20.000 36.072,26.328 38.450),(21.035 28.483,15.781 24.680,12.089 19.335,14.375 11.406,21.748 11.651,25.957 21.479,23.496 27.864,21.035 28.483),(-1.464 25.508,-6.191 22.262,-5.136 14.319,3.808 12.582,4.335 20.987,-1.464 25.508),(-3.618 35.555,-1.577 38.060,-3.291 38.627,-5.595 38.844,-7.749 36.408,-3.618 35.555),(4.160 33.857,-1.708 32.430,-5.224 28.277,23.540 31.302,11.103 32.977,4.160 33.857)))";
inline ccp::MultiPolygon gen_test_area1()
{
    using namespace ccp;
    using namespace boost::geometry;
    namespace trans = boost::geometry::strategy::transform;
    MultiPolygon temp_mpl;
    MultiPoint temp_mpt;
    MultiPolygon temp_buff;
    MultiPolygon raw_area;

    MultiPolygon work_area;
    read_wkt("MULTIPOLYGON(((0 0,0 16,16 16,16 0,0 0)))", temp_mpl);
    read_wkt("MULTIPOINT((2 3),(5 9),(6 3),(10 7))", temp_mpt);
    buffer(temp_mpt,temp_buff,0.7);
    difference(temp_mpl,temp_buff,raw_area);
    trans::rotate_transformer<boost::geometry::degree, double, 2, 2> rotate(30.0);
    boost::geometry::transform(raw_area, work_area, rotate);
    return work_area;
}

#endif  // CCP_PLANNER_ASSETS_H
