#pragma once
#include <functional>
#include <future>
#include <memory>

#include "libnop/definitions.h"
#include "libnop/logger.h"

inline void run_async_method(std::function<void()> method)
{
    static std::future<void> future;
    if (future.valid())
    {
        future.get();
    }
    future =
        std::async(std::launch::async, [mt = std::move(method)]() { mt(); });
}

#define METHOD(expression) [&]() { expression }
#define ASYNC_METHOD(expression) METHOD(run_async_method(METHOD(expression));)

namespace NOP
{
using Method = std::function<void(void)>;

class Instigation : public DebugEntity
{
   public:
    void AddMethod(Method method);
    virtual void Instigate();

   protected:
    NOPContainer<Method> methods_;
};

class ParallelInstigation final : public Instigation
{
    void Instigate() override;
};

template <NOPFlag Flag = Default, typename... Args>
auto BuildInstigation(Args... methods)
{
    std::shared_ptr<Instigation> instigation;
    if constexpr (NOP::Parallel == Flag)
    {
        instigation = std::make_shared<ParallelInstigation>();
    }
    else
    {
        instigation = std::make_shared<Instigation>();
    }
    (instigation->AddMethod(methods), ...);
    return instigation;
}

template <NOPFlag Flag = Default, typename... Args>
auto BuildInstigationNamed(const std::string_view name, DebugEntity* fbe,
                           Args... methods)
{
    auto instigation = BuildInstigation<Flag>(methods...);
    if constexpr (std::is_base_of_v<DebugEntity, Instigation>)
    {
        instigation->SetName(name);
        instigation->SetFBE(fbe);
    }
    return instigation;
}
}  // namespace NOP

#pragma once
