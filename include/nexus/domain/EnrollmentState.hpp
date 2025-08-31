// EnrollmentState.hpp
// Purpose: State pattern for Enrollment lifecycle (Requested, Validated, Confirmed, Dropped)
// Patterns: State, OCP, SRP

#pragma once
#include <string>
#include <stdexcept>

namespace nexus {

class Enrollment;

class EnrollmentState {
public:
    virtual ~EnrollmentState() = default;
    virtual std::string name() const = 0;
    virtual void validate(Enrollment& enrollment) { throw std::logic_error("Invalid state transition"); }
    virtual void confirm(Enrollment& enrollment) { throw std::logic_error("Invalid state transition"); }
    virtual void drop(Enrollment& enrollment) { throw std::logic_error("Invalid state transition"); }
};

class RequestedState : public EnrollmentState {
public:
    std::string name() const override { return "Requested"; }
    void validate(Enrollment& enrollment) override;
};

class ValidatedState : public EnrollmentState {
public:
    std::string name() const override { return "Validated"; }
    void confirm(Enrollment& enrollment) override;
};

class ConfirmedState : public EnrollmentState {
public:
    std::string name() const override { return "Confirmed"; }
    void drop(Enrollment& enrollment) override;
};

class DroppedState : public EnrollmentState {
public:
    std::string name() const override { return "Dropped"; }
};

} // namespace nexus
