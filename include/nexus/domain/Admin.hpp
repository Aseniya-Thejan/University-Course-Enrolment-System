// Admin.hpp
// Purpose: Represents an admin user.
// Patterns: Factory Method, SRP, LSP
#pragma once
#include "User.hpp"

namespace nexus {

class Admin : public User {
public:
    Admin(int id, const std::string& name, const std::string& email)
        : User(id, name, email, Role::Admin) {}
    std::string getRoleString() const override { return "Admin"; }
};

} // namespace nexus
