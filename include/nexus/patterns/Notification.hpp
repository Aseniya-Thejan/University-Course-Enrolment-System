// Notification.hpp
// Purpose: Observer pattern interfaces and NotificationBus for event-driven notifications.
// Patterns: Observer, Singleton, SRP, OCP
#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <functional>

namespace nexus {

// Event types
enum class NotificationEvent {
    CourseSeatOpened,
    EnrollmentConfirmed,
    CourseDropped,
    GradeSubmitted
};

// Observer interface
class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onNotify(NotificationEvent event, const std::string& message) = 0;
};

// Subject interface
class ISubject {
public:
    virtual ~ISubject() = default;
    virtual void addObserver(NotificationEvent event, std::shared_ptr<IObserver> observer) = 0;
    virtual void removeObserver(NotificationEvent event, std::shared_ptr<IObserver> observer) = 0;
    virtual void notify(NotificationEvent event, const std::string& message) = 0;
};

// NotificationBus (Singleton, Subject)
class NotificationBus : public ISubject {
public:
    static NotificationBus& instance();
    void addObserver(NotificationEvent event, std::shared_ptr<IObserver> observer) override;
    void removeObserver(NotificationEvent event, std::shared_ptr<IObserver> observer) override;
    void notify(NotificationEvent event, const std::string& message) override;
private:
    NotificationBus() = default;
    std::map<NotificationEvent, std::vector<std::weak_ptr<IObserver>>> observers_;
};

// Concrete observers
class EmailNotifier : public IObserver {
public:
    void onNotify(NotificationEvent event, const std::string& message) override;
};

class AdvisorNotifier : public IObserver {
public:
    void onNotify(NotificationEvent event, const std::string& message) override;
};

class AdminErrorNotifier : public IObserver {
public:
    void onNotify(NotificationEvent event, const std::string& message) override;
};

} // namespace nexus
