#pragma once

#include <deque>
#include <future>
#include <mutex>

#include "libnop/definitions.h"

namespace NOP
{
enum  EStrategy
{
    None,
    FIFO,
    LIFO,
    Priority
};

class Scheduler
{
   public:
    explicit Scheduler(const EStrategy strategy = FIFO);
    ~Scheduler();
    Scheduler(Scheduler&) = delete;
    Scheduler& operator=(Scheduler) = delete;

    [[nodiscard]] static Scheduler& Instance();
    void Schedule(const std::shared_ptr<class Rule>& rule);
    void Run();
    void FinishAll();
    void SetStrategy(EStrategy strategy, bool ignore_conflict = false);

   private:
    std::thread scheduler_thread_;
    EStrategy strategy_{FIFO};
    bool ignore_conflict_{false};

    std::deque<std::weak_ptr<class Rule>> rules_;

    std::mutex queue_mutex_;
    std::atomic_bool finished_{false};
    std::atomic_bool executing_{false};
};
}  // namespace NOP
