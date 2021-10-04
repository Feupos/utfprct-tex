#pragma once
#include <memory>
#include <mutex>

#include "libnop/action.h"
#include "libnop/condition.h"
#include "libnop/observer.h"
#include "libnop/scheduler.h"

#ifdef LIBNOP_SCHEDULER_ENABLE
static constexpr bool USE_SCHEDULER{true};
#else
static constexpr bool USE_SCHEDULER{false};
#endif

namespace NOP
{
class Rule final : public Observer, public std::enable_shared_from_this<Rule>
{
   public:
    explicit Rule(const int priority = 0);
    bool Approved() override;
    void SetCondition(std::shared_ptr<class Condition> condition);
    void SetAction(std::shared_ptr<Action> action);
    void Execute() const;
    void Approve() override;

    // Overload operator for boolean logic
    explicit operator bool() const { return approved_; }

    int priority_;

   private:
    std::shared_ptr<Condition> condition_;
    std::shared_ptr<Action> action_;
    std::recursive_mutex mutex_;
};

inline void Rule::Approve()
{
    Observer::Approve();
    if constexpr (USE_SCHEDULER)
    {
        Scheduler::Instance().Schedule(shared_from_this());
    }
    else
    {
        Execute();
    }
}

inline void Rule::SetCondition(std::shared_ptr<Condition> condition)
{
    condition_ = std::move(condition);
}

inline void Rule::SetAction(std::shared_ptr<Action> action)
{
    action_ = std::move(action);
}

inline void Rule::Execute() const { action_->Activate(); }

inline Rule::Rule(const int priority) : priority_{priority} {}

inline bool Rule::Approved() { return condition_->Approved(); }

inline std::shared_ptr<Rule> BuildRule(std::shared_ptr<Condition> condition,
                                       std::shared_ptr<Action> action,
                                       const int priority = 0)
{
    auto rule = std::make_shared<NOP::Rule>(priority);
    condition->Attach(rule);
    rule->SetAction(std::move(action));
    rule->SetCondition(std::move(condition));
    if (rule->Approved())
    {
        rule->Execute();
    }
    return rule;
}

inline std::shared_ptr<Rule> BuildRuleNamed(const std::string_view name,
                                            DebugEntity* fbe,
                                            std::shared_ptr<Condition> condition,
                                            std::shared_ptr<Action> action,
                                            const int priority = 0)
{
    auto rule = BuildRule(condition, action, priority);
    SET_DEBUG_PROPERTIES(rule, name, fbe);
    return rule;
}

}  // namespace NOP
