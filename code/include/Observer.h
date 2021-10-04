#pragma once
#include <memory>
namespace NOP
{
    class Observer: public std::enable_shared_from_this<Observer>
    {
    public:
        Observer() = default;
        Observer(Observer&) = delete;
        Observer(Observer&&) = delete;
        Observer& operator=(Observer&) = delete;
        Observer& operator=(Observer&&) = delete;
        virtual ~Observer() = default;
        virtual void Update(const bool reNotify = false) = 0;
    };
}