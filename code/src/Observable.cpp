#include "Observable.h"

namespace  NOP
{
    void NOP::Observable::Attach(const std::shared_ptr<Observer>& observer)
    {
        observers_.insert(observers_.end(), observer);
    }

    auto Observable::Detach(const std::weak_ptr<Observer>& observer)
    {
        const auto remover = [&observer](const std::weak_ptr<Observer>& ptr) {return ptr.lock() == observer.lock(); };
        return std::remove_if(observers_.begin(), observers_.end(), remover);
    }

    void Observable::Notify(const bool reNotify)
    {
        for (const auto& observer : observers_)
        {
            if (const auto& observer_lock = observer.lock(); observer_lock)
            {
                observer_lock->Update(reNotify);
            }
            else
            {
                Detach(observer);
            }
        }
    }
}