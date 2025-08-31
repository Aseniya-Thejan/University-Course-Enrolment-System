// GradeState.cpp
// Purpose: Implementation for GradeState and concrete states
#include "../../include/nexus/domain/GradeState.hpp"
#include "../../include/nexus/domain/GradeRecord.hpp"
#include <memory>

namespace nexus {

void PendingState::submit(GradeRecord& record) {
    record.setState(std::make_unique<SubmittedState>());
}

} // namespace nexus
