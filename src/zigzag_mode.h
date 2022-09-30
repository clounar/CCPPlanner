#ifndef CCP_PLANNER_ZIGZAGMODE_H
#define CCP_PLANNER_ZIGZAGMODE_H

#include "mode_base.h"
#include <list>

namespace ccp {

class ZigzagMode : public ModeBase {
    // void division_area_discription_;
    MultiPolygon::iterator current_area_;
    MultiPolygon inflate_area_;
    Box edge_;

    bool is_move_up_;

public:
    explicit ZigzagMode(const g_float& pathBias);
    LineString prepare(const MultiPolygon& work_area) override;

    LineString calculate_next_seg() override;

    bool is_complete() override;

    LineString replan_current(const Point& pose) override;

    MultiPolygon get_remaining_area() override;

    void devide_area();

    LineString go_step(g_float step);

    std::list<LineString> make_path_seg(const std::vector<std::vector<Ring>::const_iterator>& obstruction, const Box& hack_box);
};
}  // namespace ccp
#endif  // CCP_PLANNER_ZIGZAGMODE_H
