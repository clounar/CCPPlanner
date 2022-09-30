#include "complete_coverage_planner.h"

namespace ccp {
void CompleteCoveragePlanner::send_reference_line(LineString rl) {
}

/**
 * this function impl in interface file
 * @param res
 */
void CompleteCoveragePlanner::send_complete_sig(bool res) {
}

void CompleteCoveragePlanner::replan() {
}

void CompleteCoveragePlanner::replan_current() {
}

void CompleteCoveragePlanner::initial() {
}

CompleteCoveragePlanner& CompleteCoveragePlanner::singleton() {
    return singleton_;
}

CompleteCoveragePlanner CompleteCoveragePlanner::singleton_;

}  // namespace ccp
