#include "contour_mode.h"

#include <boost/geometry.hpp>
#include "geometry_operator.hpp"

#include <glog/logging.h>
namespace ccp {

LineString ContourMode::prepare(const MultiPolygon& work_area) {
    MultiPolygon temp;
    buffer(work_area, temp, -path_bias_ / 2.0);
    switch (temp.size()) {
        case 0:
            remaining_area_.clear();
            return {};
        case 1:
            remaining_area_ = std::move(temp);
            if (!remaining_area_.front().inners().empty())
                LOG(FATAL) << "TODO";
            return {remaining_area_.front().outer().begin(), remaining_area_.front().outer().end()};
        default:
            LOG(FATAL) << "TODO";
    }
}

LineString ContourMode::calculate_next_seg() {
    MultiPolygon temp;
    buffer(remaining_area_, temp, -path_bias_);
    switch (temp.size()) {
        case 0:
            remaining_area_.clear();
            return {};
        case 1:
            remaining_area_ = std::move(temp);
            if (!remaining_area_.front().inners().empty())
                LOG(FATAL) << "TODO";
            return {remaining_area_.front().outer().begin(), remaining_area_.front().outer().end()};
        default:
            LOG(FATAL) << "TODO";
    }
}

LineString ContourMode::replan_current(const Point& pose) {
    return {remaining_area_.front().outer().begin(), remaining_area_.front().outer().end()};
}

MultiPolygon ContourMode::get_remaining_area() {
    MultiPolygon res;
    buffer(remaining_area_, res, path_bias_ / 2.0);
    return res;
}

void ContourMode::check_subarea() {
}
ContourMode::ContourMode(const g_float& path_bias) : ModeBase(path_bias) {}
}  // namespace ccp
