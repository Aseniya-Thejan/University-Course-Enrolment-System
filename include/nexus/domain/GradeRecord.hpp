// GradeRecord.hpp
// Purpose: Represents a grade record for an enrollment.
// Patterns: State, SRP, DIP
#pragma once
#include <memory>
#include <string>
#include "GradeState.hpp"

namespace nexus {

class GradeRecord {
public:
    GradeRecord(int id, int enrollmentId, const std::string& grade);
    int getId() const { return id_; }
    int getEnrollmentId() const { return enrollmentId_; }
    const std::string& getGrade() const { return grade_; }
    std::string getStateName() const;
    void setState(std::unique_ptr<GradeState> state);
    GradeState* getState() const { return state_.get(); }
    void setGrade(const std::string& grade) { grade_ = grade; }
private:
    int id_;
    int enrollmentId_;
    std::string grade_;
    std::unique_ptr<GradeState> state_;
};

} // namespace nexus
