// ReportingService.hpp
// Purpose: Interface for reporting operations.
// Patterns: SRP, DIP, ISP
#pragma once
#include <vector>
#include <string>
#include <memory>
#include "../domain/Course.hpp"
#include "../domain/Enrollment.hpp"
#include "../domain/Program.hpp"

namespace nexus {

struct ReportRow {
    std::vector<std::string> columns;
};

class IReportingService {
public:
    virtual ~IReportingService() = default;
    virtual std::vector<ReportRow> enrollmentStatsByDepartment() const = 0;
    virtual std::vector<ReportRow> facultyWorkload() const = 0;
    virtual std::vector<ReportRow> coursePopularity() const = 0;
    virtual std::vector<ReportRow> coursesOverCapacity(const std::string& deptPrefix) const = 0;
};

} // namespace nexus
