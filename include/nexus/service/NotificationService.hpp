// NotificationService.hpp
// Purpose: Interface for notification operations.
// Patterns: SRP, DIP, ISP, Observer
#pragma once
#include <string>
#include <memory>
#include "../patterns/Notification.hpp"

namespace nexus {

class INotificationService {
public:
    virtual ~INotificationService() = default;
    virtual void subscribe(NotificationEvent event, std::shared_ptr<IObserver> observer) = 0;
    virtual void unsubscribe(NotificationEvent event, std::shared_ptr<IObserver> observer) = 0;
    virtual void publish(NotificationEvent event, const std::string& message) = 0;
};

} // namespace nexus
