#include "libnop/condition.h"

#include <algorithm>
#include <functional>

namespace NOP
{
Condition::Condition(std::function<bool()> operation)
    : operation_{std::move(operation)}
{
}

bool Condition::Approved() { return operation_(); }
}  // namespace NOP
