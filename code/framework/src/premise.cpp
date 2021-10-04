#include "libnop/premise.h"

namespace NOP
{
Premise::Premise(std::function<bool()> op) : operation_{std::move(op)} {}

bool Premise::Approved() { return operation_(); }
}  // namespace NOP
