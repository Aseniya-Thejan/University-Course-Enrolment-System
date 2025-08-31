// FacultyService.cpp
// Purpose: Implementation of IFacultyService
#include "../../include/nexus/service/FacultyService.hpp"
#include "../../include/nexus/repo/Repositories.hpp"
#include <stdexcept>

namespace nexus {

class FacultyService : public IFacultyService {
public:
    FacultyService(const IEnrollmentRepository& enrollmentRepo, const ICourseRepository& courseRepo, IGradeRepository& gradeRepo)
        : enrollmentRepo_(enrollmentRepo), courseRepo_(courseRepo), gradeRepo_(gradeRepo) {}

    std::vector<std::shared_ptr<Enrollment>> viewRoster(int courseId) const override {
        return enrollmentRepo_.findByCourse(courseId);
    }

    void submitGrade(int enrollmentId, const std::string& grade) override {
        auto grades = gradeRepo_.findByEnrollment(enrollmentId);
        if (grades.empty()) throw std::runtime_error("No grade record for enrollment");
        grades[0]->setGrade(grade);
        grades[0]->getState()->submit(*grades[0]);
    }

    void submitGrades(const std::vector<std::pair<int, std::string>>& grades) override {
        for (const auto& pair : grades) {
            try {
                submitGrade(pair.first, pair.second);
            } catch (const std::exception& e) {
                // Log error, continue with others
            }
        }
    }

    void requestCourseChange(int courseId, int newCapacity, const std::string& newDesc, const std::vector<int>& newPrereqs) override {
        auto course = courseRepo_.findById(courseId);
        if (!course) throw std::runtime_error("Course not found");
        course->setCapacity(newCapacity);
        course->setDescription(newDesc);
        course->setPrereqs(newPrereqs);
    }

private:
    const IEnrollmentRepository& enrollmentRepo_;
    const ICourseRepository& courseRepo_;
    IGradeRepository& gradeRepo_;
};

} // namespace nexus
