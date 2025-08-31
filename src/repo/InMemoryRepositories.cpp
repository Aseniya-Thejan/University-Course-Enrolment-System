// InMemoryRepositories.cpp
// Purpose: In-memory implementations of repository interfaces
#include "../../include/nexus/repo/InMemoryRepositories.hpp"
#include <algorithm>

namespace nexus {

// InMemoryUserRepository
std::shared_ptr<User> InMemoryUserRepository::findById(int id) const {
    auto it = users_.find(id);
    return it != users_.end() ? it->second : nullptr;
}
std::vector<std::shared_ptr<User>> InMemoryUserRepository::findAll() const {
    std::vector<std::shared_ptr<User>> result;
    for (const auto& kv : users_) result.push_back(kv.second);
    return result;
}
void InMemoryUserRepository::add(std::shared_ptr<User> user) {
    users_[user->getId()] = user;
}
void InMemoryUserRepository::remove(int id) {
    users_.erase(id);
}
std::shared_ptr<User> InMemoryUserRepository::findByEmail(const std::string& email) const {
    for (const auto& kv : users_) {
        if (kv.second->getEmail() == email) return kv.second;
    }
    return nullptr;
}

// InMemoryCourseRepository
std::shared_ptr<Course> InMemoryCourseRepository::findById(int id) const {
    auto it = courses_.find(id);
    return it != courses_.end() ? it->second : nullptr;
}
std::shared_ptr<Course> InMemoryCourseRepository::findByCode(const std::string& code) const {
    for (const auto& kv : courses_) {
        if (kv.second->getCode() == code) return kv.second;
    }
    return nullptr;
}
std::vector<std::shared_ptr<Course>> InMemoryCourseRepository::findAll() const {
    std::vector<std::shared_ptr<Course>> result;
    for (const auto& kv : courses_) result.push_back(kv.second);
    return result;
}
std::vector<std::shared_ptr<Course>> InMemoryCourseRepository::findByInstructor(int instructorId) const {
    std::vector<std::shared_ptr<Course>> result;
    for (const auto& kv : courses_) {
        if (kv.second->getInstructorId() == instructorId) result.push_back(kv.second);
    }
    return result;
}
void InMemoryCourseRepository::add(std::shared_ptr<Course> course) {
    courses_[course->getId()] = course;
}
void InMemoryCourseRepository::remove(int id) {
    courses_.erase(id);
}

// InMemoryEnrollmentRepository
std::shared_ptr<Enrollment> InMemoryEnrollmentRepository::findById(int id) const {
    auto it = enrollments_.find(id);
    return it != enrollments_.end() ? it->second : nullptr;
}
std::vector<std::shared_ptr<Enrollment>> InMemoryEnrollmentRepository::findByStudent(int studentId) const {
    std::vector<std::shared_ptr<Enrollment>> result;
    for (const auto& kv : enrollments_) {
        if (kv.second->getStudentId() == studentId) result.push_back(kv.second);
    }
    return result;
}
std::vector<std::shared_ptr<Enrollment>> InMemoryEnrollmentRepository::findByCourse(int courseId) const {
    std::vector<std::shared_ptr<Enrollment>> result;
    for (const auto& kv : enrollments_) {
        if (kv.second->getCourseId() == courseId) result.push_back(kv.second);
    }
    return result;
}
std::vector<std::shared_ptr<Enrollment>> InMemoryEnrollmentRepository::findAll() const {
    std::vector<std::shared_ptr<Enrollment>> result;
    for (const auto& kv : enrollments_) result.push_back(kv.second);
    return result;
}
void InMemoryEnrollmentRepository::add(std::shared_ptr<Enrollment> enrollment) {
    enrollments_[enrollment->getId()] = enrollment;
}
void InMemoryEnrollmentRepository::remove(int id) {
    enrollments_.erase(id);
}

// InMemoryGradeRepository
std::shared_ptr<GradeRecord> InMemoryGradeRepository::findById(int id) const {
    auto it = grades_.find(id);
    return it != grades_.end() ? it->second : nullptr;
}
std::vector<std::shared_ptr<GradeRecord>> InMemoryGradeRepository::findByEnrollment(int enrollmentId) const {
    std::vector<std::shared_ptr<GradeRecord>> result;
    for (const auto& kv : grades_) {
        if (kv.second->getEnrollmentId() == enrollmentId) result.push_back(kv.second);
    }
    return result;
}
std::vector<std::shared_ptr<GradeRecord>> InMemoryGradeRepository::findAll() const {
    std::vector<std::shared_ptr<GradeRecord>> result;
    for (const auto& kv : grades_) result.push_back(kv.second);
    return result;
}
void InMemoryGradeRepository::add(std::shared_ptr<GradeRecord> grade) {
    grades_[grade->getId()] = grade;
}
void InMemoryGradeRepository::remove(int id) {
    grades_.erase(id);
}

// InMemoryProgramRepository
std::shared_ptr<Program> InMemoryProgramRepository::findById(int id) const {
    auto it = programs_.find(id);
    return it != programs_.end() ? it->second : nullptr;
}
std::vector<std::shared_ptr<Program>> InMemoryProgramRepository::findAll() const {
    std::vector<std::shared_ptr<Program>> result;
    for (const auto& kv : programs_) result.push_back(kv.second);
    return result;
}
void InMemoryProgramRepository::add(std::shared_ptr<Program> program) {
    programs_[program->getId()] = program;
}
void InMemoryProgramRepository::remove(int id) {
    programs_.erase(id);
}

} // namespace nexus
