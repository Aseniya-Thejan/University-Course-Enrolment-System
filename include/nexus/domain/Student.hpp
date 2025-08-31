// Student.hpp
// Purpose: Represents a student user.
// Patterns: Factory Method, SRP, LSP
#pragma once
#include "User.hpp"
#include <vector>

namespace nexus {

class Student : public User {
public:
    Student(int id, const std::string& name, const std::string& email, int programId)
        : User(id, name, email, Role::Student), programId_(programId) {}
    int getProgramId() const { return programId_; }
    std::string getRoleString() const override { return "Student"; }
private:
    int programId_;
};

} // namespace nexus
