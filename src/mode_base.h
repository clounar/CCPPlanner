#ifndef CCP_PLANNER_MODEBASE_H
#define CCP_PLANNER_MODEBASE_H

#include <geometry_typedef.hpp>

namespace ccp {
// prepare->gen first path
// loop: calculate_next_seg->is_complete
// get_remaining_area
class ModeBase {
public:
    MultiPolygon remaining_area_;  /// 剩余待工作区域，不包括当前正在执行的路径，结果保存在remaining_area_中
    LineString current_path_;      /// 当前正在执行的路径，稀疏路径
    g_float path_bias_;

    explicit ModeBase(g_float path_bias)
        : path_bias_(path_bias) {}

    /**
     * 计算下一段路径，调用此函数必须确保当前路径已执行完毕
     * @return
     */
    virtual LineString calculate_next_seg() = 0;

    /**
     * 判断当前策略是否已执行完毕
     */
    virtual bool is_complete();

    /**
     * 根据机器人当前位置，重新规划当前路径，调用此函数会刷新地图并检查碰撞，并根据检查结果对当前路径重规划
     * @param pose
     */
    virtual LineString replan_current(const Point& pose) = 0;

    /**
     * 假设当前路径执行完毕，计算未工作区域，此函数一旦调用，当前对象即失效
     */
    virtual MultiPolygon get_remaining_area() = 0;

    /**
     * 初始化工作区域并返回第一条路径
     * @param work_area
     */
    virtual LineString prepare(const MultiPolygon& work_area) = 0;

    /**
     * 平滑算法
     * @param path
     */
    static LineString smooth(LineString path);

    virtual ~ModeBase() = default;
};
}  // namespace ccp
#endif  // CCP_PLANNER_MODEBASE_H
