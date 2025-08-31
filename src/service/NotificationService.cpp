// NotificationService.cpp
// Purpose: Implementation of INotificationService
#include "../../include/nexus/service/NotificationService.hpp"
#include "../../include/nexus/patterns/Notification.hpp"

namespace nexus {

class NotificationService : public INotificationService {
public:
    void subscribe(NotificationEvent event, std::shared_ptr<IObserver> observer) override {
        NotificationBus::instance().addObserver(event, observer);
    }
    void unsubscribe(NotificationEvent event, std::shared_ptr<IObserver> observer) override {
        NotificationBus::instance().removeObserver(event, observer);
    }
    void publish(NotificationEvent event, const std::string& message) override {
        NotificationBus::instance().notify(event, message);
    }
};

} // namespace nexus
