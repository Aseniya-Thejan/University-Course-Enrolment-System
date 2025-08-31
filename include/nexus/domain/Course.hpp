// Course.hpp
// Purpose: Represents a university course.
// Patterns: SRP, DIP
#pragma once
#include <string>
#include <vector>
#include <utility>

namespace nexus {

struct ScheduleSlot {
    std::string day; // e.g., "Mon"
    int startHour;   // 24h format
    int endHour;
    bool conflictsWith(const ScheduleSlot& other) const {
        return day == other.day &&
               ((startHour < other.endHour) && (endHour > other.startHour));
    }
};

class Course {
public:
    Course(int id, const std::string& code, const std::string& title, const std::string& desc,
           int instructorId, int capacity, const std::vector<ScheduleSlot>& schedule,
           const std::vector<int>& prereqs)
        : id_(id), code_(code), title_(title), description_(desc), instructorId_(instructorId),
          capacity_(capacity), schedule_(schedule), prereqs_(prereqs), enrolledCount_(0) {}
    int getId() const { return id_; }
    const std::string& getCode() const { return code_; }
    const std::string& getTitle() const { return title_; }
    const std::string& getDescription() const { return description_; }
    int getInstructorId() const { return instructorId_; }
    int getCapacity() const { return capacity_; }
    int getEnrolledCount() const { return enrolledCount_; }
    const std::vector<ScheduleSlot>& getSchedule() const { return schedule_; }
    const std::vector<int>& getPrereqs() const { return prereqs_; }
    void setCapacity(int c) { capacity_ = c; }
    void setDescription(const std::string& d) { description_ = d; }
    void setPrereqs(const std::vector<int>& p) { prereqs_ = p; }
    void incrementEnrolled() { ++enrolledCount_; }
    void decrementEnrolled() { if (enrolledCount_ > 0) --enrolledCount_; }
    void resetEnrolled() { enrolledCount_ = 0; }
private:
    int id_;
    std::string code_;
    std::string title_;
    std::string description_;
    int instructorId_;
    int capacity_;
    std::vector<ScheduleSlot> schedule_;
    std::vector<int> prereqs_;
    int enrolledCount_;
};

} // namespace nexus
