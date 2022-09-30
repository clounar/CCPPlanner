#include "mode_base.h"
namespace ccp {

LineString ModeBase::smooth(LineString path) {
    return LineString();
}
bool ModeBase::is_complete() {
    return remaining_area_.empty();
}
}  // namespace ccp
