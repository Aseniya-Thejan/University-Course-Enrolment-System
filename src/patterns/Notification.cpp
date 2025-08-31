// Notification.cpp
// Purpose: Implementation of Observer pattern and NotificationBus
#include "../../include/nexus/patterns/Notification.hpp"
#include <iostream>
#include <algorithm>

namespace nexus {

NotificationBus& NotificationBus::instance() {
    static NotificationBus instance;
    return instance;
}

void NotificationBus::addObserver(NotificationEvent event, std::shared_ptr<IObserver> observer) {
    observers_[event].push_back(observer);
}

void NotificationBus::removeObserver(NotificationEvent event, std::shared_ptr<IObserver> observer) {
    auto& vec = observers_[event];
    vec.erase(std::remove_if(vec.begin(), vec.end(),
        [&](const std::weak_ptr<IObserver>& wptr) {
            auto sptr = wptr.lock();
            return !sptr || sptr == observer;
        }), vec.end());
}

void NotificationBus::notify(NotificationEvent event, const std::string& message) {
    auto& vec = observers_[event];
    for (auto it = vec.begin(); it != vec.end(); ) {
        if (auto sptr = it->lock()) {
            sptr->onNotify(event, message);
            ++it;
        } else {
            it = vec.erase(it);
        }
    }
}

void EmailNotifier::onNotify(NotificationEvent event, const std::string& message) {
    std::cout << "[EmailNotifier] " << message << std::endl;
}

void AdvisorNotifier::onNotify(NotificationEvent event, const std::string& message) {
    std::cout << "[AdvisorNotifier] " << message << std::endl;
}

void AdminErrorNotifier::onNotify(NotificationEvent event, const std::string& message) {
    std::cout << "[AdminErrorNotifier] " << message << std::endl;
}

} // namespace nexus
