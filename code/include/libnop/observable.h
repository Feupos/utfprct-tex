#pragma once
#include <algorithm>
#include <execution>

#include "libnop/definitions.h"
#include "libnop/logger.h"

namespace NOP
{
class Observable : public DebugEntity
{
   public:
    void Attach(const std::shared_ptr<class Observer>& observer);
    template <NOPFlag Flag = Default>
    void Notify();

   private:
    NOPContainer<std::weak_ptr<class Observer>> observers_;
};

template <NOPFlag Flag>
inline void Observable::Notify()
{
    if constexpr (0 < (NoNotify & Flag))
    {
        // Skip notifications
    }
    else
    {
        if constexpr (0 < (Parallel & Flag))
        {
            if constexpr (0 < (Exclusive & Flag))
            {
                // none_of will break when returning true
                const bool ret = std::none_of(
                    std::execution::par_unseq, observers_.begin(),
                    observers_.end(), [](auto& observer) {
                        bool ret{false};
                        if (const auto& observer_lock = observer.lock();
                            observer_lock)
                        {
                            ret = observer_lock->template Update<Flag>();
                        }
                        return ret;
                    });
            }
            else
            {
                std::for_each(
                    std::execution::par_unseq, observers_.begin(),
                    observers_.end(), [](auto& observer) {
                        if (const auto& observer_lock = observer.lock();
                            observer_lock)
                        {
                            observer_lock->template Update<Flag>();
                        }
                    });
            }
        }
        else
        {
            if constexpr (0 < (Exclusive & Flag))
            {
                // none_of will break when returning true
                const bool ret = std::none_of(
                    observers_.begin(), observers_.end(), [](auto& observer) {
                        bool ret{false};
                        if (const auto& observer_lock = observer.lock();
                            observer_lock)
                        {
                            ret =  observer_lock->template Update<Flag>();
                        }
                        return ret;
                    });
            }
            else
            {
                std::for_each(
                    observers_.begin(), observers_.end(), [](auto& observer) {
                        if (const auto& observer_lock = observer.lock();
                            observer_lock)
                        {
                            observer_lock->template Update<Flag>();
                        }
                    });
            }
        }
    }
}
}  // namespace NOP
