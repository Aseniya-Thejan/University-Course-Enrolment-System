// AdminService.cpp
// Purpose: Implementation of IAdminService
#include "../../include/nexus/service/AdminService.hpp"
#include "../../include/nexus/repo/Repositories.hpp"
#include "../../include/nexus/patterns/UserFactory.hpp"
#include "../../include/nexus/patterns/IdGenerator.hpp"
#include <stdexcept>

namespace nexus {

class AdminService : public IAdminService {
public:
    AdminService(IUserRepository& userRepo, ICourseRepository& courseRepo, IProgramRepository& programRepo)
        : userRepo_(userRepo), courseRepo_(courseRepo), programRepo_(programRepo) {}

    void createCourse(const std::string& code, const std::string& title, const std::string& desc, int instructorId, int capacity, const std::vector<ScheduleSlot>& schedule, const std::vector<int>& prereqs) override {
        int id = IdGenerator::instance().nextId();
        auto course = std::make_shared<Course>(id, code, title, desc, instructorId, capacity, schedule, prereqs);
        courseRepo_.add(course);
    }
    void editCourse(int courseId, int newCapacity, const std::string& newDesc, const std::vector<int>& newPrereqs) override {
        auto course = courseRepo_.findById(courseId);
        if (!course) throw std::runtime_error("Course not found");
        course->setCapacity(newCapacity);
        course->setDescription(newDesc);
        course->setPrereqs(newPrereqs);
    }
    void deleteCourse(int courseId) override {
        courseRepo_.remove(courseId);
    }
    void createProgram(const std::string& name, const std::vector<int>& requiredCourses) override {
        int id = IdGenerator::instance().nextId();
        auto program = std::make_shared<Program>(id, name, requiredCourses);
        programRepo_.add(program);
    }
    void editProgram(int programId, const std::vector<int>& requiredCourses) override {
        auto program = programRepo_.findById(programId);
        if (!program) throw std::runtime_error("Program not found");
        program->setRequiredCourses(requiredCourses);
    }
    void deleteProgram(int programId) override {
        programRepo_.remove(programId);
    }
    void addUser(User::Role role, const std::string& name, const std::string& email, int programId) override {
        int id = IdGenerator::instance().nextId();
        auto user = UserFactory::create(role, id, name, email, programId);
        userRepo_.add(std::move(user));
    }
    void editUser(int userId, const std::string& name, const std::string& email) override {
        auto user = userRepo_.findById(userId);
        if (!user) throw std::runtime_error("User not found");
        // For demo, assume we can set name/email directly
        // (In real code, use setters or reconstruct object)
    }
    void deactivateUser(int userId) override {
        userRepo_.remove(userId);
    }
    void overrideEnrolment(int studentId, int courseId) override {
        // Actual orchestration is handled by EnrolmentFacade
        throw std::logic_error("Use EnrolmentFacade for overrideEnrolment");
    }
private:
    IUserRepository& userRepo_;
    ICourseRepository& courseRepo_;
    IProgramRepository& programRepo_;
};

} // namespace nexus
