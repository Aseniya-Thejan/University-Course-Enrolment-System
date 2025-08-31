// main.cpp
// Purpose: Scripted CLI demo for NexusEnroll
// Patterns: Facade, Observer, Strategy, State, Factory, Singleton, UnitOfWork
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "include/nexus/domain/Student.hpp"
#include "include/nexus/domain/Faculty.hpp"
#include "include/nexus/domain/Admin.hpp"
#include "include/nexus/domain/Course.hpp"
#include "include/nexus/domain/Program.hpp"
#include "include/nexus/repo/InMemoryRepositories.hpp"
#include "include/nexus/patterns/UserFactory.hpp"
#include "include/nexus/patterns/IdGenerator.hpp"
#include "include/nexus/patterns/Notification.hpp"
#include "include/nexus/facade/EnrolmentFacade.hpp"

using namespace nexus;

void printSeparator(const std::string& title) {
    std::cout << "\n=== " << title << " ===\n";
}

int main() {
    // Setup repositories
    InMemoryUserRepository userRepo;
    InMemoryCourseRepository courseRepo;
    InMemoryEnrollmentRepository enrollmentRepo;
    InMemoryGradeRepository gradeRepo;
    InMemoryProgramRepository programRepo;

    // Setup notification observers
    auto emailNotifier = std::make_shared<EmailNotifier>();
    auto advisorNotifier = std::make_shared<AdvisorNotifier>();
    auto adminNotifier = std::make_shared<AdminErrorNotifier>();
    NotificationBus::instance().addObserver(NotificationEvent::EnrollmentConfirmed, emailNotifier);
    NotificationBus::instance().addObserver(NotificationEvent::CourseSeatOpened, advisorNotifier);
    NotificationBus::instance().addObserver(NotificationEvent::CourseDropped, adminNotifier);

    // Setup facade
    EnrolmentFacade facade(userRepo, courseRepo, enrollmentRepo, gradeRepo, programRepo);

    // Seed Programs
    int progId = IdGenerator::instance().nextId();
    auto csProgram = std::make_shared<Program>(progId, "BSc CS", std::vector<int>{}); // Will fill required courses after seeding courses
    programRepo.add(csProgram);

    // Seed Users
    int stuAId = IdGenerator::instance().nextId();
    int stuBId = IdGenerator::instance().nextId();
    int stuCId = IdGenerator::instance().nextId();
    int facXId = IdGenerator::instance().nextId();
    int facYId = IdGenerator::instance().nextId();
    int adminId = IdGenerator::instance().nextId();
    userRepo.add(UserFactory::create(User::Role::Student, stuAId, "Student A", "a@uni.edu", progId));
    userRepo.add(UserFactory::create(User::Role::Student, stuBId, "Student B", "b@uni.edu", progId));
    userRepo.add(UserFactory::create(User::Role::Student, stuCId, "Student C", "c@uni.edu", progId));
    userRepo.add(UserFactory::create(User::Role::Faculty, facXId, "Prof X", "x@uni.edu"));
    userRepo.add(UserFactory::create(User::Role::Faculty, facYId, "Prof Y", "y@uni.edu"));
    userRepo.add(UserFactory::create(User::Role::Admin, adminId, "Admin", "admin@uni.edu"));

    // Seed Courses
    int cs101Id = IdGenerator::instance().nextId();
    int cs201Id = IdGenerator::instance().nextId();
    ScheduleSlot slot1{"Mon", 9, 11};
    ScheduleSlot slot2{"Mon", 10, 12};
    auto cs101 = std::make_shared<Course>(cs101Id, "CS101", "Intro", "Intro to CS", facXId, 2, std::vector<ScheduleSlot>{slot1}, std::vector<int>{});
    auto cs201 = std::make_shared<Course>(cs201Id, "CS201", "Data Structures", "Data Structures", facYId, 1, std::vector<ScheduleSlot>{slot2}, std::vector<int>{cs101Id});
    courseRepo.add(cs101);
    courseRepo.add(cs201);
    // Update program required courses
    csProgram->setRequiredCourses({cs101Id, cs201Id});

    // Seed completed courses
    // Student A and C have completed CS101 (simulate by adding confirmed enrollment)
    auto enrollA_CS101 = std::make_shared<Enrollment>(IdGenerator::instance().nextId(), stuAId, cs101Id);
    enrollA_CS101->setState(std::make_unique<ConfirmedState>());
    enrollmentRepo.add(enrollA_CS101);
    auto enrollC_CS101 = std::make_shared<Enrollment>(IdGenerator::instance().nextId(), stuCId, cs101Id);
    enrollC_CS101->setState(std::make_unique<ConfirmedState>());
    enrollmentRepo.add(enrollC_CS101);

    printSeparator("Student browse: search by keyword 'Data'");
    for (const auto& c : courseRepo.findAll()) {
        if (c->getTitle().find("Data") != std::string::npos) {
            std::cout << c->getCode() << ": " << c->getTitle() << "\n";
        }
    }
    printSeparator("Student browse: by instructor Prof Y");
    for (const auto& c : courseRepo.findByInstructor(facYId)) {
        std::cout << c->getCode() << ": " << c->getTitle() << "\n";
    }

    printSeparator("Student B tries to enroll in CS201 (should fail: prerequisite)");
    try {
        facade.enroll(stuBId, cs201Id);
    } catch (const std::exception& e) {
        std::cout << "[Result] " << e.what() << "\n";
    }

    printSeparator("Student A enrolls in CS201 (should succeed)");
    try {
        facade.enroll(stuAId, cs201Id);
    } catch (const std::exception& e) {
        std::cout << "[Result] " << e.what() << "\n";
    }

    printSeparator("Student C tries to enroll in CS201 (should fail: capacity)");
    try {
        facade.enroll(stuCId, cs201Id);
    } catch (const std::exception& e) {
        std::cout << "[Result] " << e.what() << "\n";
    }

    printSeparator("Student A enrolls in CS101 (should fail: time conflict)");
    try {
        facade.enroll(stuAId, cs101Id);
    } catch (const std::exception& e) {
        std::cout << "[Result] " << e.what() << "\n";
    }

    printSeparator("Student A drops CS201 (seat opens, notify waitlist)");
    try {
        facade.drop(stuAId, cs201Id);
    } catch (const std::exception& e) {
        std::cout << "[Result] " << e.what() << "\n";
    }

    printSeparator("Student C enrolls in CS201 (should succeed after seat opened)");
    try {
        facade.enroll(stuCId, cs201Id);
    } catch (const std::exception& e) {
        std::cout << "[Result] " << e.what() << "\n";
    }

    printSeparator("Prof Y views roster for CS201");
    for (const auto& e : enrollmentRepo.findByCourse(cs201Id)) {
        std::cout << "Student ID: " << e->getStudentId() << ", State: " << e->getStateName() << "\n";
    }

    printSeparator("Prof Y submits grades (batch: one valid, one invalid)");
    // For demo, just print simulation
    std::cout << "[Grade Submission] Student C: A (valid)\n";
    std::cout << "[Grade Submission] Student B: Z (invalid, error simulated)\n";

    printSeparator("Admin increases capacity of CS101");
    cs101->setCapacity(3);
    std::cout << "CS101 new capacity: " << cs101->getCapacity() << "\n";

    printSeparator("Admin generates report: courses over 90% capacity");
    if (cs101->getEnrolledCount() > 0.9 * cs101->getCapacity()) {
        std::cout << cs101->getCode() << " is over 90% capacity\n";
    }
    if (cs201->getEnrolledCount() > 0.9 * cs201->getCapacity()) {
        std::cout << cs201->getCode() << " is over 90% capacity\n";
    }

    printSeparator("Admin performs override to force-add Student B into full CS201");
    try {
        facade.overrideEnrolment(stuBId, cs201Id);
    } catch (const std::exception& e) {
        std::cout << "[Result] " << e.what() << "\n";
    }

    printSeparator("Student A's degree progress");
    auto completed = std::vector<int>{cs101Id};
    auto required = csProgram->getRequiredCourses();
    std::cout << "Completed: ";
    for (int cid : completed) std::cout << cid << " ";
    std::cout << "\nRequired: ";
    for (int cid : required) std::cout << cid << " ";
    std::cout << "\n";

    printSeparator("Demo complete");
    return 0;
}
