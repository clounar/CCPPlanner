#ifndef CCP_PLANNER_COMPLETECOVERAGEPLANNER_H
#define CCP_PLANNER_COMPLETECOVERAGEPLANNER_H
#include "mode_base.h"
namespace ccp {
class CompleteCoveragePlanner {
public:
    MultiPolygon work_area_set_;
    static CompleteCoveragePlanner singleton_;

    /**
     * this function impl in interface file
     */
    void send_reference_line(LineString rl);

    /**
     * this function impl in interface file
     */
    void send_complete_sig(bool res);

    void replan();

    void replan_current();

    void initial();

    static CompleteCoveragePlanner& singleton();

private:
    size_t state_;
    ::std::vector<std::unique_ptr<ModeBase> > strategy_pipeline_;
};
}  // namespace ccp
#endif  // CCP_PLANNER_COMPLETECOVERAGEPLANNER_H
