// EnrolmentFacade.cpp
// Purpose: Implementation of EnrolmentFacade
#include "../../include/nexus/facade/EnrolmentFacade.hpp"
#include "../../include/nexus/patterns/IdGenerator.hpp"
#include <iostream>
#include <stdexcept>

namespace nexus {

EnrolmentFacade::EnrolmentFacade(IUserRepository& userRepo,
                                 ICourseRepository& courseRepo,
                                 IEnrollmentRepository& enrollmentRepo,
                                 IGradeRepository& gradeRepo,
                                 IProgramRepository& programRepo)
    : userRepo_(userRepo), courseRepo_(courseRepo), enrollmentRepo_(enrollmentRepo), gradeRepo_(gradeRepo), programRepo_(programRepo) {
    // Default rules
    rules_.push_back(std::make_shared<PrerequisiteRule>());
    rules_.push_back(std::make_shared<CapacityRule>());
    rules_.push_back(std::make_shared<TimeConflictRule>());
}

void EnrolmentFacade::setEnrolmentRules(const std::vector<std::shared_ptr<IEnrolmentRule>>& rules) {
    rules_ = rules;
}

void EnrolmentFacade::enroll(int studentId, int courseId, bool adminOverride) {
    uow_.clear();
    try {
        auto student = userRepo_.findById(studentId);
        auto course = courseRepo_.findById(courseId);
        if (!student || !course) throw std::runtime_error("Student or course not found");
        // Check for duplicate enrollment
        for (const auto& e : enrollmentRepo_.findByStudent(studentId)) {
            if (e->getCourseId() == courseId && e->getStateName() != "Dropped")
                throw std::runtime_error("Already enrolled");
        }
        // Create Enrollment
        int enrollId = IdGenerator::instance().nextId();
        auto enrollment = std::make_shared<Enrollment>(enrollId, studentId, courseId);
        // Validation
        std::vector<int> completed; // For demo, assume none completed
        std::vector<const Course*> currentCourses;
        for (const auto& e : enrollmentRepo_.findByStudent(studentId)) {
            if (e->getStateName() == "Confirmed") {
                completed.push_back(e->getCourseId());
                currentCourses.push_back(courseRepo_.findById(e->getCourseId()).get());
            }
        }
        for (const auto& rule : rules_) {
            if (adminOverride && dynamic_cast<CapacityRule*>(rule.get())) continue;
            rule->validate(*enrollment, *course, completed, currentCourses);
        }
        // Register actions
        uow_.registerAction(
            [this, enrollment]() { enrollmentRepo_.add(enrollment); },
            [this, enrollment]() { enrollmentRepo_.remove(enrollment->getId()); }
        );
        uow_.registerAction(
            [course]() { const_cast<Course*>(course.get())->incrementEnrolled(); },
            [course]() { const_cast<Course*>(course.get())->decrementEnrolled(); }
        );
        uow_.registerAction(
            [enrollment]() { enrollment->setState(std::make_unique<ConfirmedState>()); },
            [enrollment]() { enrollment->setState(std::make_unique<DroppedState>()); }
        );
        // Commit
        uow_.commit();
        NotificationBus::instance().notify(NotificationEvent::EnrollmentConfirmed, "Enrollment confirmed for student " + std::to_string(studentId) + " in course " + course->getCode());
    } catch (const std::exception& e) {
        uow_.rollback();
        NotificationBus::instance().notify(NotificationEvent::CourseDropped, std::string("Enrollment failed: ") + e.what());
        throw;
    }
}

void EnrolmentFacade::drop(int studentId, int courseId) {
    uow_.clear();
    try {
        auto enrollments = enrollmentRepo_.findByStudent(studentId);
        std::shared_ptr<Enrollment> enrollment = nullptr;
        for (const auto& e : enrollments) {
            if (e->getCourseId() == courseId && e->getStateName() == "Confirmed") {
                enrollment = e;
                break;
            }
        }
        if (!enrollment) throw std::runtime_error("Enrollment not found");
        auto course = courseRepo_.findById(courseId);
        if (!course) throw std::runtime_error("Course not found");
        uow_.registerAction(
            [enrollment]() { enrollment->setState(std::make_unique<DroppedState>()); },
            [enrollment]() { enrollment->setState(std::make_unique<ConfirmedState>()); }
        );
        uow_.registerAction(
            [course]() { const_cast<Course*>(course.get())->decrementEnrolled(); },
            [course]() { const_cast<Course*>(course.get())->incrementEnrolled(); }
        );
        uow_.commit();
        NotificationBus::instance().notify(NotificationEvent::CourseSeatOpened, "Seat opened in course " + course->getCode());
    } catch (const std::exception& e) {
        uow_.rollback();
    NotificationBus::instance().notify(NotificationEvent::CourseDropped, std::string("Drop failed: ") + e.what());
        throw;
    }
}

void EnrolmentFacade::overrideEnrolment(int studentId, int courseId) {
    enroll(studentId, courseId, true);
}

} // namespace nexus
