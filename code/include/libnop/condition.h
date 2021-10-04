#pragma once
#include <functional>
#include <memory>

#include "libnop/observer.h"

// use = to copy shared pointers by value and ensure a valid reference exists
#define CONDITION(expression) [=, this]() { return bool(expression); }

namespace NOP
{
enum EConditionType
{
    Single,
    Conjunction,
    Disjunction
};

class Condition final : public Observer
{
   public:
    Condition() = default;
    explicit Condition(std::function<bool(void)> operation);
    bool Approved() override;

    // Overload operator for boolean logic
    explicit operator bool() const { return approved_; }

   private:
    std::function<bool(void)> operation_;
};

template <typename... Args>
auto BuildCondition(std::function<bool(void)> operation, Args... args)
{
    auto condition = std::make_shared<NOP::Condition>(operation);
    auto attach = [&](auto element) { element->Attach(condition); };
    (attach(args), ...);
    condition->Update();
    return condition;
}

template <typename... Args>
auto BuildConditionNamed(const std::string_view name, DebugEntity* fbe, Args... args)
{
    auto condition = BuildCondition(args...);
    if constexpr (std::is_base_of_v<DebugEntity, Condition>)
    {
        condition->SetName(name);
        condition->SetFBE(fbe);
    }
    return condition;
}

template <EConditionType type, typename... Args>
auto BuildCondition(Args... args)
{
    std::shared_ptr<Condition> condition{nullptr};
    if constexpr (Single == type)
    {
        // Explicit operator bool
        condition = std::make_shared<Condition>(
            [=]() { return ((*args && true), ...); });
    }
    else if constexpr (Conjunction == type)
    {
        condition =
            std::make_shared<Condition>([=]() { return (*args && ...); });
    }
    else if constexpr (Disjunction == type)
    {
        condition =
            std::make_shared<Condition>([=]() { return (*args || ...); });
    }
    auto attach = [&](auto element) { element->Attach(condition); };
    (attach(args), ...);
    return condition;
}

template <EConditionType type, typename... Args>
auto BuildConditionNamed(const std::string_view name, DebugEntity* fbe, Args... args)
{
    auto condition = BuildCondition<EConditionType>(args...);
    if constexpr (std::is_base_of_v<DebugEntity, Condition>)
    {
        condition->SetName(name);
        condition->SetFBE(fbe);
    }
    return condition;
}

}  // namespace NOP
