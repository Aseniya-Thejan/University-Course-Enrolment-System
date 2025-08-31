// FacultyService.hpp
// Purpose: Interface for faculty-related operations.
// Patterns: SRP, DIP, ISP
#pragma once
#include <vector>
#include <string>
#include <memory>
#include "../domain/Course.hpp"
#include "../domain/Enrollment.hpp"
#include "../domain/GradeRecord.hpp"

namespace nexus {

class IFacultyService {
public:
    virtual ~IFacultyService() = default;
    virtual std::vector<std::shared_ptr<Enrollment>> viewRoster(int courseId) const = 0;
    virtual void submitGrade(int enrollmentId, const std::string& grade) = 0;
    virtual void submitGrades(const std::vector<std::pair<int, std::string>>& grades) = 0;
    virtual void requestCourseChange(int courseId, int newCapacity, const std::string& newDesc, const std::vector<int>& newPrereqs) = 0;
};

} // namespace nexus
