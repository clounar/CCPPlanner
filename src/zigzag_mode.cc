#include "zigzag_mode.h"
#include "geometry_operator.hpp"
#include <algorithm>
#include <glog/logging.h>
#include "../tests/save_svg.hpp"
#include "float_equal.hpp"

namespace ccp {

LineString ZigzagMode::prepare(const MultiPolygon& work_area) {
    is_move_up_ = false;
    remaining_area_ = work_area;
    current_area_ = remaining_area_.end() - 1;
    boost::geometry::envelope(*current_area_, edge_);
    current_path_ = go_step(path_bias_ / 2.0);
    return current_path_;
}

LineString ZigzagMode::calculate_next_seg() {
    edge_.min_corner().x() += path_bias_;
    Point last_end = current_path_.back();
    current_path_ = go_step(path_bias_ / 2.0);
    current_path_.front() = last_end;
    return current_path_;
}

bool ZigzagMode::is_complete() {
    return edge_.max_corner().x() - edge_.min_corner().x() < path_bias_*1.5;
}

LineString ZigzagMode::replan_current(const Point& pose) {
    return current_path_;
}

MultiPolygon ZigzagMode::get_remaining_area() {
    return {};
}

void ZigzagMode::devide_area() {
}

LineString ZigzagMode::go_step(g_float step) {
    LineString ref_line{
        {edge_.min_corner().x() + step, edge_.min_corner().y()},
        {edge_.min_corner().x() + step, edge_.max_corner().y()},
    };
    auto obstruction = select(current_area_->inners(), ref_line);
    MultiPoint intersection_point;
    boost::geometry::intersection(current_area_->outer(), ref_line, intersection_point);
    if (intersection_point.size() != 2)
    {
        save_svg("debug.svg", current_area_->outer(),intersection_point);
        LOG(ERROR) << edge_.min_corner()<<'\n'<<edge_.max_corner()<<'\n'<<boost::geometry::wkt(ref_line)<<'\n'<<boost::geometry::wkt(intersection_point);
        LOG(FATAL) << "impossible case!";
    }

    is_move_up_ = !is_move_up_;
    Box hack_box{intersection_point[0], intersection_point[1]};
    boost::geometry::correct(hack_box);
    hack_box.min_corner().y() + path_bias_ / 2.0;
    hack_box.max_corner().y() - path_bias_ / 2.0;
    if (hack_box.max_corner().y() <= hack_box.min_corner().y())
        return {{intersection_point[0].x(), (intersection_point[0].y() + intersection_point[1].y()) / 2}};
    if (obstruction.empty()) {
        if (is_move_up_)
            return {hack_box.min_corner(), hack_box.min_corner(), hack_box.max_corner()};
        else
            return {hack_box.max_corner(), hack_box.max_corner(), hack_box.min_corner()};
    }

    hack_box.max_corner().x() += 0.000001;
    auto path_seg = make_path_seg(obstruction, hack_box);

    size_t path_size = 3;
    for (const auto& elem : path_seg)
        path_size += elem.size();
    LineString res;
    res.reserve(path_size);
    if (is_move_up_)
        res.push_back(hack_box.min_corner());
    else
        res.push_back({hack_box.min_corner().x(), hack_box.max_corner().y()});
    res.push_back(res.front());
    for (const auto& elem : path_seg)
        res.insert(res.end(), elem.begin(), elem.end());
    if (is_move_up_)
        res.push_back({hack_box.min_corner().x(), hack_box.max_corner().y()});
    else
        res.push_back(hack_box.min_corner());
    return res;
}
std::list<LineString> ZigzagMode::make_path_seg(const std::vector<std::vector<Ring>::const_iterator>& obstruction, const Box& hack_box) {
    std::list<LineString> path_seg;
    for (auto ring : obstruction) {
        MultiPolygon temp;
        Polygon temp_polygon;
        boost::geometry::convert(*ring, temp_polygon);
        boost::geometry::reverse(temp_polygon);
        boost::geometry::difference(temp_polygon, hack_box, temp);
        if (temp.size() != 2) {
            LOG(ERROR) << boost::geometry::wkt(temp_polygon);
            LOG(ERROR) << boost::geometry::wkt(hack_box);
            LOG(FATAL) << "size: " << temp.size() << " impossible case";
        }
        if (boost::geometry::perimeter(temp[0]) < boost::geometry::perimeter(temp[1]))
            temp_polygon = std::move(temp[0]);
        else
            temp_polygon = std::move(temp[1]);
        bool is_left_part = temp_polygon.outer().front().x() < (hack_box.min_corner().x()+hack_box.max_corner().x())/2;
        Polygon::ring_type::iterator it;
        if (is_left_part) {
            it = std::find_if(temp_polygon.outer().begin(), temp_polygon.outer().end(), [&hack_box](auto& it) {
                return feqv::isEqual(it.x(), hack_box.min_corner().x());
            });
        } else {
            it = std::find_if(temp_polygon.outer().begin(), temp_polygon.outer().end(), [&hack_box](auto& it) {
                return feqv::isEqual(it.x(), hack_box.max_corner().x());
            });
        }
        LineString temp_path;
        temp_path.reserve(temp_polygon.outer().size() - 1);
        if (it == temp_polygon.outer().end()) {
            save_svg("debug.svg", temp_polygon.outer());
            LOG(FATAL) << boost::geometry::wkt(temp_polygon.outer()) << '\n'
                       << boost::geometry::wkt(hack_box);
        }
        if (it == temp_polygon.outer().begin()) {
            if (feqv::isEqual(it->x() , it[1].x()))  // begin point at right top or left button
                temp_path.insert(temp_path.end(), it + 1, temp_polygon.outer().end());
            else  // begin point at right button or left top
                temp_path.insert(temp_path.end(), it, temp_polygon.outer().end() - 1);
        } else {
            temp_path.insert(temp_path.end(), it + 1, temp_polygon.outer().end() - 1);
            temp_path.insert(temp_path.end(), temp_polygon.outer().begin(), it + 1);
        }
        if (is_left_part ^ is_move_up_)
            boost::geometry::reverse(temp_path);
        path_seg.push_back(std::move(temp_path));
    }
    path_seg.sort([this](auto& a, auto& b) { return (a.front().y() < b.front().y()) == is_move_up_; });
    return path_seg;
}

ZigzagMode::ZigzagMode(const g_float& pathBias) : ModeBase(pathBias) {}

}  // namespace ccp
