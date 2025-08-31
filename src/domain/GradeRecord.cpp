// GradeRecord.cpp
// Purpose: Implementation for GradeRecord class and State transitions
#include "../../include/nexus/domain/GradeRecord.hpp"
#include "../../include/nexus/domain/GradeState.hpp"
#include <stdexcept>

namespace nexus {

GradeRecord::GradeRecord(int id, int enrollmentId, const std::string& grade)
    : id_(id), enrollmentId_(enrollmentId), grade_(grade), state_(std::make_unique<PendingState>()) {}

std::string GradeRecord::getStateName() const {
    return state_ ? state_->name() : "Unknown";
}

void GradeRecord::setState(std::unique_ptr<GradeState> state) {
    state_ = std::move(state);
}

} // namespace nexus
