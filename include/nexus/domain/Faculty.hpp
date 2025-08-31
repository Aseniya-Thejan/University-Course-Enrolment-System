// Faculty.hpp
// Purpose: Represents a faculty user.
// Patterns: Factory Method, SRP, LSP
#pragma once
#include "User.hpp"

namespace nexus {

class Faculty : public User {
public:
    Faculty(int id, const std::string& name, const std::string& email)
        : User(id, name, email, Role::Faculty) {}
    std::string getRoleString() const override { return "Faculty"; }
};

} // namespace nexus
