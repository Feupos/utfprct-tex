// C++ Framework NOP 4.0
//
// Copyright (c) 2020 - present, Felipe dos Santos Neves
// All rights reserved.
//
// For the license information refer to framework.h

#pragma once
#include <memory>

#include "libnop/instigation.h"

namespace NOP
{
class Action DERIVE_DEBUG_ENTITY
{
   public:
    void AddInstigation(std::shared_ptr<Instigation> instigation);
    virtual void Activate();

   protected:
    NOPContainer<std::shared_ptr<Instigation>> instigations_;
};

class ParallelAction : public Action
{
   public:
    void Activate() override;
};

template <NOPFlag Flag = Default, typename... Args>
auto BuildAction(Args... instigation)
{
    std::shared_ptr<Action> action{};
    if constexpr (NOP::Parallel == Flag)
    {
        action = std::make_shared<ParallelAction>();
    }
    else
    {
        action = std::make_shared<Action>();
    }
    (action->AddInstigation(instigation), ...);
    return action;
}

template <NOPFlag Flag = Default, typename... Args>
auto BuildActionNamed(const std::string_view name, DebugEntity* fbe,
                      Args... instigation)
{
    auto action = BuildAction<Flag>(instigation...);
    SET_DEBUG_PROPERTIES(action, name, fbe);
    return action;
}
}  // namespace NOP
