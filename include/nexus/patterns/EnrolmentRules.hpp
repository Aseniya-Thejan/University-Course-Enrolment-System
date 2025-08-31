// EnrolmentRules.hpp
// Purpose: Strategy pattern for enrolment validation rules.
// Patterns: Strategy, OCP, SRP
#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../domain/Enrollment.hpp"
#include "../domain/Course.hpp"

namespace nexus {

class IEnrolmentRule {
public:
    virtual ~IEnrolmentRule() = default;
    virtual void validate(const Enrollment& enrollment, const Course& course, const std::vector<int>& completedCourses, const std::vector<const Course*>& currentCourses) const = 0;
};

class PrerequisiteRule : public IEnrolmentRule {
public:
    void validate(const Enrollment& enrollment, const Course& course, const std::vector<int>& completedCourses, const std::vector<const Course*>& currentCourses) const override;
};

class CapacityRule : public IEnrolmentRule {
public:
    CapacityRule(bool adminOverride = false) : adminOverride_(adminOverride) {}
    void validate(const Enrollment& enrollment, const Course& course, const std::vector<int>& completedCourses, const std::vector<const Course*>& currentCourses) const override;
private:
    bool adminOverride_;
};

class TimeConflictRule : public IEnrolmentRule {
public:
    void validate(const Enrollment& enrollment, const Course& course, const std::vector<int>& completedCourses, const std::vector<const Course*>& currentCourses) const override;
};

} // namespace nexus
