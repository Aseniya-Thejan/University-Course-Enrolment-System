// UnitOfWork.hpp
// Purpose: Simulates a transaction (Unit of Work) for atomic operations.
// Patterns: Unit of Work, Command (optional), SRP
#pragma once
#include <vector>
#include <functional>
#include <stack>

namespace nexus {

class UnitOfWork {
public:
    void registerAction(const std::function<void()>& commitAction, const std::function<void()>& rollbackAction);
    void commit();
    void rollback();
    void clear();
private:
    std::vector<std::function<void()>> commitActions_;
    std::stack<std::function<void()>> rollbackActions_;
};

} // namespace nexus
