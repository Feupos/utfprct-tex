#pragma once
#include <functional>
#include <future>
#include <memory>

#include "libnop/definitions.h"
#include "libnop/logger.h"

#define METHOD(expression) [&]() { expression }
#define ASYNC_METHOD(expression) \
    METHOD(std::thread async_method{METHOD(expression)}; async_method.detach();)

namespace NOP
{
using Method = std::function<void(void)>;

class Instigation
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
    SET_DEBUG_PROPERTIES(instigation, name, fbe);
    return instigation;
}
}  // namespace NOP

#pragma once
