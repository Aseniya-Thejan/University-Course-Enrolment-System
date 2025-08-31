// UnitOfWork.cpp
// Purpose: Implementation of Unit of Work pattern
#include "../../include/nexus/patterns/UnitOfWork.hpp"
#include <stdexcept>

namespace nexus {

void UnitOfWork::registerAction(const std::function<void()>& commitAction, const std::function<void()>& rollbackAction) {
    commitActions_.push_back(commitAction);
    rollbackActions_.push(rollbackAction);
}

void UnitOfWork::commit() {
    for (const auto& action : commitActions_) {
        action();
    }
    clear();
}

void UnitOfWork::rollback() {
    while (!rollbackActions_.empty()) {
        rollbackActions_.top()();
        rollbackActions_.pop();
    }
    clear();
}

void UnitOfWork::clear() {
    commitActions_.clear();
    while (!rollbackActions_.empty()) rollbackActions_.pop();
}

} // namespace nexus
