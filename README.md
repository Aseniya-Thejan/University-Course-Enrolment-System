# NexusEnroll

## Overview

NexusEnroll is a modern, modular C++17 university course enrolment system, designed as a proof-of-concept for scalable, maintainable academic administration. It demonstrates a 3-Tier architecture, strong adherence to SOLID principles, and explicit use of classic design patterns.

## Architecture

- **Presentation Layer:** `main.cpp` provides a scripted CLI demo, simulating user flows for students, faculty, and admins.
- **Business/Domain Layer:** Services, domain entities, and patterns (Observer, Strategy, Facade, Factory, Singleton, State, UnitOfWork, Command).
- **Data Layer:** In-memory repositories with interfaces, supporting CRUD and queries.

**Diagram:**
```
Presentation (CLI)
        ↓
  EnrolmentFacade (Facade)
        ↓
  Services (Student, Faculty, Admin, Reporting, Notification)
        ↓
  Repositories (Interfaces → InMemory Implementations)
```

## Design Patterns Used

- **Observer:** NotificationBus and observers for events (enrolment, seat open, grade submission).
- **Strategy:** Enrolment validation rules (prerequisite, capacity, time conflict).
- **Facade:** EnrolmentFacade coordinates enrolment flows, validation, and notifications.
- **Factory Method:** UserFactory for user creation by role.
- **Singleton:** IdGenerator, NotificationBus.
- **State:** Enrollment and GradeRecord state transitions.
- **Unit of Work:** Transactional enrolment/drop with rollback.
- **Command (optional):** Audit log and undo simulation in UnitOfWork.

## Quick Start

```sh
mkdir build
cd build
cmake ..
cmake --build .

./NexusEnroll
```

## Transactions & Rollback

All enrolment and drop operations are atomic. If any step fails (e.g., validation, capacity), all changes are rolled back, ensuring data consistency.

## Demo Script Outline

- Seed users, programs, courses, and completed courses.
- Students browse and attempt to enroll (showing validation failures and successes).
- Faculty views rosters and submits grades (with error handling).
- Admin manages courses, generates reports, and performs overrides.
- Notifications and state transitions are printed throughout.

**Sample Output:**
```
=== Student B attempts to enroll in CS201 ===
[Validation] Prerequisite not met: CS101 required.
[Result] Enrollment failed.

=== Student A enrolls in CS201 ===
[State] Requested → Validated → Confirmed
[Notification] Enrollment confirmed for Student A in CS201.
...
```

## Extending the System

- **Add a new validation rule:** Implement `IEnrolmentRule`, add to the rule chain in `EnrolmentFacade`.
- **Add new entity/service:** Define interface in `include/nexus/`, implement in `src/`, register in Facade or Service as needed.

## Principles

- **SRP:** Each class has a single responsibility (e.g., notification, repository, service).
- **OCP:** Validation rules are pluggable.
- **LSP:** User subclasses are substitutable.
- **ISP:** Service interfaces are fine-grained.
- **DIP:** Services depend on interfaces, not implementations.
- **DRY/KISS:** Utilities and helpers are reused; code is simple and clear.
