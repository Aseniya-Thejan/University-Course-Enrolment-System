// UserFactory.hpp
// Purpose: Factory Method for creating User objects by role.
// Patterns: Factory Method, SRP, OCP
#pragma once
#include <memory>
#include <string>
#include "../domain/User.hpp"
#include "../domain/Student.hpp"
#include "../domain/Faculty.hpp"
#include "../domain/Admin.hpp"

namespace nexus {

class UserFactory {
public:
    static std::unique_ptr<User> create(User::Role role, int id, const std::string& name, const std::string& email, int programId = -1);
};

} // namespace nexus
