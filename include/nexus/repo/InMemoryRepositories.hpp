// InMemoryRepositories.hpp
// Purpose: In-memory implementations of repository interfaces.
// Patterns: Repository, DIP, SRP
#pragma once
#include "Repositories.hpp"
#include <unordered_map>

namespace nexus {

class InMemoryUserRepository : public IUserRepository {
public:
    std::shared_ptr<User> findById(int id) const override;
    std::vector<std::shared_ptr<User>> findAll() const override;
    void add(std::shared_ptr<User> user) override;
    void remove(int id) override;
    std::shared_ptr<User> findByEmail(const std::string& email) const override;
private:
    std::unordered_map<int, std::shared_ptr<User>> users_;
};

class InMemoryCourseRepository : public ICourseRepository {
public:
    std::shared_ptr<Course> findById(int id) const override;
    std::shared_ptr<Course> findByCode(const std::string& code) const override;
    std::vector<std::shared_ptr<Course>> findAll() const override;
    std::vector<std::shared_ptr<Course>> findByInstructor(int instructorId) const override;
    void add(std::shared_ptr<Course> course) override;
    void remove(int id) override;
private:
    std::unordered_map<int, std::shared_ptr<Course>> courses_;
};

class InMemoryEnrollmentRepository : public IEnrollmentRepository {
public:
    std::shared_ptr<Enrollment> findById(int id) const override;
    std::vector<std::shared_ptr<Enrollment>> findByStudent(int studentId) const override;
    std::vector<std::shared_ptr<Enrollment>> findByCourse(int courseId) const override;
    std::vector<std::shared_ptr<Enrollment>> findAll() const override;
    void add(std::shared_ptr<Enrollment> enrollment) override;
    void remove(int id) override;
private:
    std::unordered_map<int, std::shared_ptr<Enrollment>> enrollments_;
};

class InMemoryGradeRepository : public IGradeRepository {
public:
    std::shared_ptr<GradeRecord> findById(int id) const override;
    std::vector<std::shared_ptr<GradeRecord>> findByEnrollment(int enrollmentId) const override;
    std::vector<std::shared_ptr<GradeRecord>> findAll() const override;
    void add(std::shared_ptr<GradeRecord> grade) override;
    void remove(int id) override;
private:
    std::unordered_map<int, std::shared_ptr<GradeRecord>> grades_;
};

class InMemoryProgramRepository : public IProgramRepository {
public:
    std::shared_ptr<Program> findById(int id) const override;
    std::vector<std::shared_ptr<Program>> findAll() const override;
    void add(std::shared_ptr<Program> program) override;
    void remove(int id) override;
private:
    std::unordered_map<int, std::shared_ptr<Program>> programs_;
};

} // namespace nexus
