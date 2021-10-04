#pragma once
#include "Observer.h"
#include "Definitions.h"
#include <algorithm>

namespace NOP
{
    class Observable
    {
    public:
        Observable() = default;
        Observable(Observable&) = delete;
        Observable(Observable&&) = delete;
        virtual Observable& operator=(Observable&) = delete;
        virtual Observable& operator=(Observable&&) = delete;
        virtual ~Observable() = default;

        void Attach(const std::shared_ptr<Observer>& observer);
        auto Detach(const std::weak_ptr<Observer>& observer);
        void Notify(const bool reNotify = false);

    private:
        NOPContainer<std::weak_ptr<Observer>> observers_;
    };
}