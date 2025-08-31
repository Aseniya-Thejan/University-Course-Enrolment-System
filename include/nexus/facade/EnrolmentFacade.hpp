// EnrolmentFacade.hpp
// Purpose: Facade for enrolment orchestration, validation, and notifications.
// Patterns: Facade, Strategy, Observer, UnitOfWork, SRP, DIP
#pragma once
#include <vector>
#include <memory>
#include "../repo/Repositories.hpp"
#include "../patterns/EnrolmentRules.hpp"
#include "../patterns/UnitOfWork.hpp"
#include "../patterns/Notification.hpp"

namespace nexus {

class EnrolmentFacade {
public:
    EnrolmentFacade(IUserRepository& userRepo,
                    ICourseRepository& courseRepo,
                    IEnrollmentRepository& enrollmentRepo,
                    IGradeRepository& gradeRepo,
                    IProgramRepository& programRepo);

    // Enrolment and drop flows
    void enroll(int studentId, int courseId, bool adminOverride = false);
    void drop(int studentId, int courseId);
    void overrideEnrolment(int studentId, int courseId);

    // For demo/testing
    void setEnrolmentRules(const std::vector<std::shared_ptr<IEnrolmentRule>>& rules);

private:
    IUserRepository& userRepo_;
    ICourseRepository& courseRepo_;
    IEnrollmentRepository& enrollmentRepo_;
    IGradeRepository& gradeRepo_;
    IProgramRepository& programRepo_;
    std::vector<std::shared_ptr<IEnrolmentRule>> rules_;
    UnitOfWork uow_;
};

} // namespace nexus
