// EnrollmentState.cpp
// Purpose: Implementation for EnrollmentState and concrete states
#include "../../include/nexus/domain/EnrollmentState.hpp"
#include "../../include/nexus/domain/Enrollment.hpp"
#include <memory>

namespace nexus {

void RequestedState::validate(Enrollment& enrollment) {
    enrollment.setState(std::make_unique<ValidatedState>());
}

void ValidatedState::confirm(Enrollment& enrollment) {
    enrollment.setState(std::make_unique<ConfirmedState>());
}

void ConfirmedState::drop(Enrollment& enrollment) {
    enrollment.setState(std::make_unique<DroppedState>());
}

} // namespace nexus
