// StudentService.cpp
// Purpose: Implementation of IStudentService
#include "../../include/nexus/service/StudentService.hpp"
#include "../../include/nexus/repo/Repositories.hpp"
#include "../../include/nexus/domain/Student.hpp"
#include "../../include/nexus/domain/Program.hpp"
#include <algorithm>
#include <stdexcept>

namespace nexus {

class StudentService : public IStudentService {
public:
    StudentService(const IUserRepository& userRepo, const ICourseRepository& courseRepo, const IEnrollmentRepository& enrollmentRepo, const IProgramRepository& programRepo)
        : userRepo_(userRepo), courseRepo_(courseRepo), enrollmentRepo_(enrollmentRepo), programRepo_(programRepo) {}

    std::vector<std::shared_ptr<Course>> browseCourses(const std::string& keyword) const override {
        std::vector<std::shared_ptr<Course>> result;
        for (const auto& course : courseRepo_.findAll()) {
            if (course->getTitle().find(keyword) != std::string::npos ||
                course->getCode().find(keyword) != std::string::npos ||
                course->getDescription().find(keyword) != std::string::npos) {
                result.push_back(course);
            }
        }
        return result;
    }

    std::vector<std::shared_ptr<Course>> browseByInstructor(int instructorId) const override {
        return courseRepo_.findByInstructor(instructorId);
    }

    void enroll(int studentId, int courseId) override {
        // Actual orchestration is handled by EnrolmentFacade in this architecture
        throw std::logic_error("Use EnrolmentFacade for enroll operation");
    }

    void drop(int studentId, int courseId) override {
        // Actual orchestration is handled by EnrolmentFacade in this architecture
        throw std::logic_error("Use EnrolmentFacade for drop operation");
    }

    std::vector<std::shared_ptr<Enrollment>> viewSchedule(int studentId) const override {
        return enrollmentRepo_.findByStudent(studentId);
    }

    std::vector<int> completedCourses(int studentId) const override {
        // For demo, assume all enrollments with Confirmed state are completed
        std::vector<int> completed;
        for (const auto& enrollment : enrollmentRepo_.findByStudent(studentId)) {
            if (enrollment->getStateName() == "Confirmed") {
                completed.push_back(enrollment->getCourseId());
            }
        }
        return completed;
    }

    std::vector<int> remainingRequiredCourses(int studentId) const override {
        auto user = userRepo_.findById(studentId);
        auto student = std::dynamic_pointer_cast<Student>(user);
        if (!student) return {};
        auto program = programRepo_.findById(student->getProgramId());
        if (!program) return {};
        auto completed = completedCourses(studentId);
        std::vector<int> remaining;
        for (int req : program->getRequiredCourses()) {
            if (std::find(completed.begin(), completed.end(), req) == completed.end()) {
                remaining.push_back(req);
            }
        }
        return remaining;
    }

private:
    const IUserRepository& userRepo_;
    const ICourseRepository& courseRepo_;
    const IEnrollmentRepository& enrollmentRepo_;
    const IProgramRepository& programRepo_;
};

} // namespace nexus
