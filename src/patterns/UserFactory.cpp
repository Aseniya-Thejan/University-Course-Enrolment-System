// UserFactory.cpp
// Purpose: Implementation of Factory Method for User creation
#include "../../include/nexus/patterns/UserFactory.hpp"

namespace nexus {

std::unique_ptr<User> UserFactory::create(User::Role role, int id, const std::string& name, const std::string& email, int programId) {
    switch (role) {
        case User::Role::Student:
            return std::make_unique<Student>(id, name, email, programId);
        case User::Role::Faculty:
            return std::make_unique<Faculty>(id, name, email);
        case User::Role::Admin:
            return std::make_unique<Admin>(id, name, email);
        default:
            return nullptr;
    }
}

} // namespace nexus
