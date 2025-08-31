// User.hpp
// Purpose: Abstract base class for all user types (Student, Faculty, Admin).
// Patterns: Factory Method (UserFactory), SRP, LSP, DIP
#pragma once
#include <string>
#include <memory>

namespace nexus {

class User {
public:
    enum class Role { Student, Faculty, Admin };
    User(int id, const std::string& name, const std::string& email, Role role)
        : id_(id), name_(name), email_(email), role_(role) {}
    virtual ~User() = default;
    int getId() const { return id_; }
    const std::string& getName() const { return name_; }
    const std::string& getEmail() const { return email_; }
    Role getRole() const { return role_; }
    virtual std::string getRoleString() const = 0;
protected:
    int id_;
    std::string name_;
    std::string email_;
    Role role_;
};

} // namespace nexus
