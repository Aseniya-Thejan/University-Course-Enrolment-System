// IdGenerator.cpp
// Purpose: Implementation of Singleton IdGenerator
#include "../../include/nexus/patterns/IdGenerator.hpp"

namespace nexus {

IdGenerator& IdGenerator::instance() {
    static IdGenerator instance;
    return instance;
}

int IdGenerator::nextId() {
    return currentId_++;
}

} // namespace nexus
