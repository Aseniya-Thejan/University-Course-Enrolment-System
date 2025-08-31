// IdGenerator.hpp
// Purpose: Singleton for generating unique IDs.
// Patterns: Singleton, SRP
#pragma once

namespace nexus {

class IdGenerator {
public:
    static IdGenerator& instance();
    int nextId();
private:
    IdGenerator() : currentId_(1) {}
    int currentId_;
};

} // namespace nexus
