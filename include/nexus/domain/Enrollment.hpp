// Enrollment.hpp
// Purpose: Represents a course enrollment, with State pattern for lifecycle.
// Patterns: State, SRP, DIP
#pragma once
#include <memory>
#include <string>
#include "EnrollmentState.hpp"

namespace nexus {

class Enrollment {
public:
    Enrollment(int id, int studentId, int courseId);
    int getId() const { return id_; }
    int getStudentId() const { return studentId_; }
    int getCourseId() const { return courseId_; }
    std::string getStateName() const;
    void setState(std::unique_ptr<EnrollmentState> state);
    EnrollmentState* getState() const { return state_.get(); }
private:
    int id_;
    int studentId_;
    int courseId_;
    std::unique_ptr<EnrollmentState> state_;
};

} // namespace nexus
