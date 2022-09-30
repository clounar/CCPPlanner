#ifndef CCP_PLANNER_CONTOURMODE_H
#define CCP_PLANNER_CONTOURMODE_H

#include "mode_base.h"
#include <stack>

namespace ccp {

class ContourMode : public ModeBase {
    class SubArea {
    };

    ::std::stack<SubArea> sub_area_;

public:
    explicit ContourMode(const g_float& pathBias);

    LineString prepare(const MultiPolygon& work_area) override;

    LineString calculate_next_seg() override;

    LineString replan_current(const Point& pose) override;

    MultiPolygon get_remaining_area() override;

    void check_subarea();
};
}  // namespace ccp
#endif  // CCP_PLANNER_CONTOURMODE_H
