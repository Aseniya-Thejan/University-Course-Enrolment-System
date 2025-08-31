// ReportingService.cpp
// Purpose: Implementation of IReportingService
#include "../../include/nexus/service/ReportingService.hpp"
#include "../../include/nexus/repo/Repositories.hpp"
#include <map>

namespace nexus {

class ReportingService : public IReportingService {
public:
    ReportingService(const ICourseRepository& courseRepo, const IEnrollmentRepository& enrollmentRepo)
        : courseRepo_(courseRepo), enrollmentRepo_(enrollmentRepo) {}

    std::vector<ReportRow> enrollmentStatsByDepartment() const override {
        std::map<std::string, int> deptCounts;
        for (const auto& course : courseRepo_.findAll()) {
            std::string dept = course->getCode().substr(0, 3);
            deptCounts[dept] += course->getEnrolledCount();
        }
        std::vector<ReportRow> rows;
        for (const auto& kv : deptCounts) {
            rows.push_back({{kv.first, std::to_string(kv.second)}});
        }
        return rows;
    }
    std::vector<ReportRow> facultyWorkload() const override {
        std::map<int, int> facultyCounts;
        for (const auto& course : courseRepo_.findAll()) {
            facultyCounts[course->getInstructorId()] += course->getEnrolledCount();
        }
        std::vector<ReportRow> rows;
        for (const auto& kv : facultyCounts) {
            rows.push_back({{std::to_string(kv.first), std::to_string(kv.second)}});
        }
        return rows;
    }
    std::vector<ReportRow> coursePopularity() const override {
        std::vector<ReportRow> rows;
        for (const auto& course : courseRepo_.findAll()) {
            rows.push_back({{course->getCode(), std::to_string(course->getEnrolledCount())}});
        }
        return rows;
    }
    std::vector<ReportRow> coursesOverCapacity(const std::string& deptPrefix) const override {
        std::vector<ReportRow> rows;
        for (const auto& course : courseRepo_.findAll()) {
            if (course->getCode().find(deptPrefix) == 0 && course->getEnrolledCount() > 0.9 * course->getCapacity()) {
                rows.push_back({{course->getCode(), std::to_string(course->getEnrolledCount()), std::to_string(course->getCapacity())}});
            }
        }
        return rows;
    }
private:
    const ICourseRepository& courseRepo_;
    const IEnrollmentRepository& enrollmentRepo_;
};

} // namespace nexus
