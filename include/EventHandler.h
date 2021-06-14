#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <atomic>
#include <functional>

template <typename... Args> class EventHandler {

public:

    typedef std::function<void(Args...)> HandlerFuncType;
    typedef unsigned int HandlerIdType;
    
    EventHandler(const EventHandler& src) 
        : _handlerFunc(src._handlerFunc), _handlerId(src._handlerId) {

        }

    EventHandler(EventHandler&& src) 
        : _handlerFunc(std::move(src._handlerFunc)), _handlerId(src._handlerId) {

        }

    EventHandler& operator=(const EventHandler& src) {
        _handlerFunc = src._handlerFunc;
        _handlerId = src._handlerId;

        return *this;
    }

    EventHandler& operator=(EventHandler&& src) {
        std::swap(_handlerFunc, src._handlerFunc);
        _handlerId = src._handlerId;

        return *this;
    }

    explicit EventHandler(const HandlerFuncType& handlerFunc)
        : _handlerFunc(handlerFunc) {
            _handlerId = ++_handlerIdCounter;
        }

    void operator()(Args... params) const {
        if (_handlerFunc) {
            _handlerFunc(params...);
        }
    }

    bool operator==(const EventHandler& other) const {
        return _handlerId == other._handlerId;
    }

    HandlerIdType getId() const {
        return _handlerId;
    }

private:

    HandlerFuncType _handlerFunc;
    HandlerIdType _handlerId;
    static std::atomic_uint _handlerIdCounter;

};

template <typename... Args> std::atomic_uint
EventHandler<Args...>::_handlerIdCounter(0);

#endif