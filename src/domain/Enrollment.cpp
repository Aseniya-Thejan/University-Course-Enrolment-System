// Enrollment.cpp
// Purpose: Implementation for Enrollment class and State transitions
#include "../../include/nexus/domain/Enrollment.hpp"
#include "../../include/nexus/domain/EnrollmentState.hpp"
#include <stdexcept>

namespace nexus {

Enrollment::Enrollment(int id, int studentId, int courseId)
    : id_(id), studentId_(studentId), courseId_(courseId), state_(std::make_unique<RequestedState>()) {}

std::string Enrollment::getStateName() const {
    return state_ ? state_->name() : "Unknown";
}

void Enrollment::setState(std::unique_ptr<EnrollmentState> state) {
    state_ = std::move(state);
}

} // namespace nexus
