// EnrolmentRules.cpp
// Purpose: Implementation of Strategy pattern for enrolment validation
#include "../../include/nexus/patterns/EnrolmentRules.hpp"
#include <stdexcept>
#include <algorithm>

namespace nexus {

void PrerequisiteRule::validate(const Enrollment& /*enrollment*/, const Course& course, const std::vector<int>& completedCourses, const std::vector<const Course*>& /*currentCourses*/) const {
    for (int prereq : course.getPrereqs()) {
        if (std::find(completedCourses.begin(), completedCourses.end(), prereq) == completedCourses.end()) {
            throw std::runtime_error("Prerequisite not met: " + std::to_string(prereq) + " required.");
        }
    }
}

void CapacityRule::validate(const Enrollment& /*enrollment*/, const Course& course, const std::vector<int>& /*completedCourses*/, const std::vector<const Course*>& /*currentCourses*/) const {
    if (!adminOverride_ && course.getEnrolledCount() >= course.getCapacity()) {
        throw std::runtime_error("Course is full: " + course.getCode());
    }
}

void TimeConflictRule::validate(const Enrollment& /*enrollment*/, const Course& course, const std::vector<int>& /*completedCourses*/, const std::vector<const Course*>& currentCourses) const {
    for (const auto* c : currentCourses) {
        for (const auto& slot1 : course.getSchedule()) {
            for (const auto& slot2 : c->getSchedule()) {
                if (slot1.conflictsWith(slot2)) {
                    throw std::runtime_error("Time conflict with course: " + c->getCode());
                }
            }
        }
    }
}

} // namespace nexus
