// C++ Framework NOP 4.0
//
// Copyright (c) 2020 - present, Felipe dos Santos Neves
// All rights reserved.
//
// For the license information refer to framework.h

#pragma once
#include <algorithm>
#include <execution>

#include "libnop/definitions.h"
#include "libnop/logger.h"

namespace NOP
{
class Observable DERIVE_DEBUG_ENTITY
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
    auto notify_entities = [](auto& observer)
    {
        bool ret{false};
        if (const auto& observer_ptr = observer.lock(); observer_ptr)
        {
            ret = observer_ptr->template Update<Flag>();
        }
        return ret;
    };
    if constexpr (0 < (NoNotify & Flag))
    {
        // Does not notify
    }
    else if constexpr (0 < (Parallel & Flag))
    {
        if constexpr (0 < (Exclusive & Flag))
        {
            // Notifies until first return true
            const bool ret =
                std::none_of(std::execution::par_unseq, observers_.begin(),
                             observers_.end(), notify_entities);
        }
        else
        {
            std::for_each(std::execution::par_unseq, observers_.begin(),
                          observers_.end(), notify_entities);
        }
    }
    else if constexpr (0 < (Exclusive & Flag))
    {
        // Notifies until first return true
        const bool ret =
            std::none_of(observers_.begin(), observers_.end(), notify_entities);
    }
    else
    {
        std::for_each(observers_.begin(), observers_.end(), notify_entities);
    }
}
}  // namespace NOP
