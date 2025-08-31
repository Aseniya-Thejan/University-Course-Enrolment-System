// GradeState.hpp
// Purpose: State pattern for GradeRecord (Pending, Submitted)
// Patterns: State, OCP, SRP

#pragma once
#include <string>
#include <stdexcept>

namespace nexus {

class GradeRecord;

class GradeState {
public:
    virtual ~GradeState() = default;
    virtual std::string name() const = 0;
    virtual void submit(GradeRecord& record) { throw std::logic_error("Invalid state transition"); }
};

class PendingState : public GradeState {
public:
    std::string name() const override { return "Pending"; }
    void submit(GradeRecord& record) override;
};

class SubmittedState : public GradeState {
public:
    std::string name() const override { return "Submitted"; }
};

} // namespace nexus
