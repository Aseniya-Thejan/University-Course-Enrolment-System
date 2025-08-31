// Repositories.hpp
// Purpose: Repository interfaces for all domain entities.
// Patterns: Repository, DIP, SRP
#pragma once
#include <vector>
#include <memory>
#include <string>
#include "../domain/User.hpp"
#include "../domain/Student.hpp"
#include "../domain/Faculty.hpp"
#include "../domain/Admin.hpp"
#include "../domain/Course.hpp"
#include "../domain/Enrollment.hpp"
#include "../domain/GradeRecord.hpp"
#include "../domain/Program.hpp"

namespace nexus {

class IUserRepository {
public:
    virtual ~IUserRepository() = default;
    virtual std::shared_ptr<User> findById(int id) const = 0;
    virtual std::vector<std::shared_ptr<User>> findAll() const = 0;
    virtual void add(std::shared_ptr<User> user) = 0;
    virtual void remove(int id) = 0;
    virtual std::shared_ptr<User> findByEmail(const std::string& email) const = 0;
};

class ICourseRepository {
public:
    virtual ~ICourseRepository() = default;
    virtual std::shared_ptr<Course> findById(int id) const = 0;
    virtual std::shared_ptr<Course> findByCode(const std::string& code) const = 0;
    virtual std::vector<std::shared_ptr<Course>> findAll() const = 0;
    virtual std::vector<std::shared_ptr<Course>> findByInstructor(int instructorId) const = 0;
    virtual void add(std::shared_ptr<Course> course) = 0;
    virtual void remove(int id) = 0;
};

class IEnrollmentRepository {
public:
    virtual ~IEnrollmentRepository() = default;
    virtual std::shared_ptr<Enrollment> findById(int id) const = 0;
    virtual std::vector<std::shared_ptr<Enrollment>> findByStudent(int studentId) const = 0;
    virtual std::vector<std::shared_ptr<Enrollment>> findByCourse(int courseId) const = 0;
    virtual std::vector<std::shared_ptr<Enrollment>> findAll() const = 0;
    virtual void add(std::shared_ptr<Enrollment> enrollment) = 0;
    virtual void remove(int id) = 0;
};

class IGradeRepository {
public:
    virtual ~IGradeRepository() = default;
    virtual std::shared_ptr<GradeRecord> findById(int id) const = 0;
    virtual std::vector<std::shared_ptr<GradeRecord>> findByEnrollment(int enrollmentId) const = 0;
    virtual std::vector<std::shared_ptr<GradeRecord>> findAll() const = 0;
    virtual void add(std::shared_ptr<GradeRecord> grade) = 0;
    virtual void remove(int id) = 0;
};

class IProgramRepository {
public:
    virtual ~IProgramRepository() = default;
    virtual std::shared_ptr<Program> findById(int id) const = 0;
    virtual std::vector<std::shared_ptr<Program>> findAll() const = 0;
    virtual void add(std::shared_ptr<Program> program) = 0;
    virtual void remove(int id) = 0;
};

} // namespace nexus
