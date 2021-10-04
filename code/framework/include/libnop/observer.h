// C++ Framework NOP 4.0
//
// Copyright (c) 2020 - present, Felipe dos Santos Neves
// All rights reserved.
//
// For the license information refer to framework.h

#pragma once

#include "libnop/definitions.h"
#include "libnop/logger.h"
#include "libnop/observable.h"

namespace NOP
{
class Observer : public Observable
{
   public:
    virtual bool Approved() = 0;
    template <NOPFlag Flag = Default>
    bool Update();
    virtual void Approve();
    virtual void Disapprove();

   protected:
    bool approved_{false};
};

template <NOPFlag Flag>
bool Observer::Update()
{
    const bool new_state = Approved();
    const bool changed = new_state != approved_;

    if (new_state)
    {
        Approve();
        LOG(this, "Approved");
    }
    else
    {
        Disapprove();
        LOG(this, "Disapproved");
    }

    if constexpr (0 < (ReNotify & Flag))
    {
        Notify<Flag>();
    }
    else if (changed)
    {
        Notify<Flag>();
    }
    return approved_;
}

inline void Observer::Approve() { approved_ = true; }

inline void Observer::Disapprove() { approved_ = false; }
}  // namespace NOP
