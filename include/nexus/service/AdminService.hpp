// AdminService.hpp
// Purpose: Interface for admin-related operations.
// Patterns: SRP, DIP, ISP
#pragma once
#include <vector>
#include <string>
#include <memory>
#include "../domain/User.hpp"
#include "../domain/Course.hpp"
#include "../domain/Program.hpp"

namespace nexus {

class IAdminService {
public:
    virtual ~IAdminService() = default;
    virtual void createCourse(const std::string& code, const std::string& title, const std::string& desc, int instructorId, int capacity, const std::vector<ScheduleSlot>& schedule, const std::vector<int>& prereqs) = 0;
    virtual void editCourse(int courseId, int newCapacity, const std::string& newDesc, const std::vector<int>& newPrereqs) = 0;
    virtual void deleteCourse(int courseId) = 0;
    virtual void createProgram(const std::string& name, const std::vector<int>& requiredCourses) = 0;
    virtual void editProgram(int programId, const std::vector<int>& requiredCourses) = 0;
    virtual void deleteProgram(int programId) = 0;
    virtual void addUser(User::Role role, const std::string& name, const std::string& email, int programId) = 0;
    virtual void editUser(int userId, const std::string& name, const std::string& email) = 0;
    virtual void deactivateUser(int userId) = 0;
    virtual void overrideEnrolment(int studentId, int courseId) = 0;
};

} // namespace nexus
