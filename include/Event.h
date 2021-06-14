#ifndef EVENT_H
#define EVENT_H

#include <list>
#include <mutex>
#include "EventHandler.h"

template <typename... Args> class Event {

public:

    typedef EventHandler<Args...> HandlerType;

    Event() {
        
    }

    Event(const Event& src) {
        std::lock_guard<std::mutex> lock(_handlersLocker);

        _handlers = src._handlers;
    }

    Event(Event&& src) {
        std::lock_guard<std::mutex> lock(_handlersLocker);

        _handlers = std::move(src._handlers);
    }

    Event& operator=(const Event& src) {
        std::lock_guard<std::mutex> lock(_handlersLocker);
        std::lock_guard<std::mutex> lock2(src._handlersLocker);

        _handlers = src._handlers;

        return *this;
    }

    Event& operator=(Event&& src) {
        std::lock_guard<std::mutex> lock(_handlersLocker);
        std::lock_guard<std::mutex> lock2(src._handlersLocker);

        std::swap(_handlers, src._handlers);

        return *this;
    }

    void operator()(Args... params) const {
        call(params...);
    }

    typename HandlerType::HandlerIdType operator+=(const HandlerType& handler) {
        return add(handler);
    }

    typename HandlerType::HandlerIdType operator+=(const typename HandlerType::HandlerFuncType& handler) {
        return add(handler);
    }

    bool operator-=(const HandlerType& handler) {
        return remove(handler);
    }

protected:

    typedef std::list<HandlerType> HandlerCollectionType;

private:

    HandlerCollectionType _handlers;

    typename HandlerType::HandlerIdType add(const HandlerType& handler) {
        std::lock_guard<std::mutex> lock(_handlersLocker);

        _handlers.push_back(handler);
        return handler.getId();
    }

    typename HandlerType::HandlerIdType add(const typename HandlerType::HandlerFuncType& handler) {
        return add(HandlerType(handler));
    }

    bool remove(const HandlerType& handler) {
        std::lock_guard<std::mutex> lock(_handlersLocker);

        auto it = std::find(_handlers.begin(), _handlers.end(), handler);
        if (it != _handlers.end()) {
            _handlers.erase(it);
            return true;
        }

        return false;
    }

    bool remove_id(const typename HandlerType::HandlerIdType& handlerId) {
        std::lock_guard<std::mutex> lock(_handlersLocker);

        auto it = std::find_if(_handlers.begin(), _handlers.end(), [handlerId](const HandlerType& handler) {
            return (handler.getId() == handlerId);
        });

        if (it != _handlers.end()) {
            _handlers.erase(it);
            return true;
        }
        
        return false;
    }

    void call(Args... params) const {
        HandlerCollectionType handlersCopy = getHandlersCopy();
        call_impl(handlersCopy, params...);
    }

    void call_impl(const HandlerCollectionType& handlers, Args... params) const {
        for (const auto& handler : handlers) {
            handler(params...);
        }
    }

    HandlerCollectionType getHandlersCopy() const {
        std::lock_guard<std::mutex> lock(_handlersLocker);

        return _handlers;
    }

    mutable std::mutex _handlersLocker;
};



#endif