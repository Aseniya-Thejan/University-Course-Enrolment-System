// StudentService.hpp
// Purpose: Interface for student-related operations.
// Patterns: SRP, DIP, ISP
#pragma once
#include <vector>
#include <string>
#include <memory>
#include "../domain/Course.hpp"
#include "../domain/Enrollment.hpp"
#include "../domain/Program.hpp"

namespace nexus {

class IStudentService {
public:
    virtual ~IStudentService() = default;
    virtual std::vector<std::shared_ptr<Course>> browseCourses(const std::string& keyword) const = 0;
    virtual std::vector<std::shared_ptr<Course>> browseByInstructor(int instructorId) const = 0;
    virtual void enroll(int studentId, int courseId) = 0;
    virtual void drop(int studentId, int courseId) = 0;
    virtual std::vector<std::shared_ptr<Enrollment>> viewSchedule(int studentId) const = 0;
    virtual std::vector<int> completedCourses(int studentId) const = 0;
    virtual std::vector<int> remainingRequiredCourses(int studentId) const = 0;
};

} // namespace nexus
