// Program.hpp
// Purpose: Represents a degree program.
// Patterns: SRP, DIP
#pragma once
#include <string>
#include <vector>

namespace nexus {

class Program {
public:
    Program(int id, const std::string& name, const std::vector<int>& requiredCourses)
        : id_(id), name_(name), requiredCourses_(requiredCourses) {}
    int getId() const { return id_; }
    const std::string& getName() const { return name_; }
    const std::vector<int>& getRequiredCourses() const { return requiredCourses_; }
    void setRequiredCourses(const std::vector<int>& req) { requiredCourses_ = req; }
private:
    int id_;
    std::string name_;
    std::vector<int> requiredCourses_;
};

} // namespace nexus
