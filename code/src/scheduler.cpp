#include "libnop/scheduler.h"
#include "libnop/rule.h"

#include <algorithm>

namespace NOP
{
Scheduler::Scheduler(const EStrategy strategy) : strategy_{strategy}
{
    scheduler_thread_ = std::thread([&]() { Run(); });
}

Scheduler::~Scheduler()
{
    finished_ = true;
    scheduler_thread_.join();
}

Scheduler& Scheduler::Instance()
{
    static const auto instance{std::make_unique<Scheduler>(FIFO)};
    return *instance;
}

void Scheduler::Schedule(const std::shared_ptr<Rule>& rule)
{
    std::lock_guard<std::mutex> lock{rule_mutex_};
    LOG(rule.get(), "Scheduled");
    rules_.push_back(rule);
}

void Scheduler::Run()
{
    while (!finished_)
    {
        std::weak_ptr<Rule> current_rule;
        {
            std::lock_guard<std::mutex> lock{rule_mutex_};
            if (!rules_.empty())
            {
                std::deque<std::weak_ptr<Rule>>::iterator current_rule_it;
                if (FIFO == strategy_)
                {
                    current_rule_it = rules_.begin();
                }
                else if (LIFO == strategy_)
                {
                    current_rule_it = --rules_.end();
                }
                else if (Priority == strategy_)
                {
                    current_rule_it = std::max_element(
                        rules_.begin(), rules_.end(), [&](auto rl1, auto rl2) {
                            auto lock1 = rl1.lock();
                            auto lock2 = rl2.lock();
                            return lock1->priority_ < lock2->priority_;
                        });
                }
                else
                {
                    current_rule_it = rules_.begin();
                }
                current_rule = *current_rule_it;
                rules_.erase(current_rule_it);
                executing_ = true;
            }
        }

        if (const auto& rule_lock = current_rule.lock(); rule_lock)
        {
            
            // Check if it is still approved for execution
            // If the rule is not approved anymore it means
            // there was a conflict that was executed before
            if (rule_lock->Approved() || ignore_conflict_ || (None == strategy_))
            {
                LOG(rule_lock.get(), "Executed by scheduler");
                rule_lock->Execute();
            }
            else
            {
                LOG(rule_lock.get(), "Discarded by scheduler due to conflict");
            }
        }
        executing_ = false;
    }
}

void Scheduler::FinishAll()
{
    // Wait while scheduler is still running
    bool empty{false};
    do
    {
        std::lock_guard<std::mutex> lock{rule_mutex_};
        empty = rules_.empty();
    } while (!empty || executing_);
}

void Scheduler::SetStrategy(const EStrategy strategy, const bool ignore_conflict)
{
    // Need to finish current task before changing strategy
    FinishAll();
    strategy_ = strategy;
    ignore_conflict_ = ignore_conflict;
}
}  // namespace NOP
