#pragma once

#include "libnop/action.h"
#include "libnop/attribute.h"
#include "libnop/condition.h"
#include "libnop/fbe.h"
#include "libnop/instigation.h"
#include "libnop/logger.h"
#include "libnop/premise.h"
#include "libnop/rule.h"
#include "libnop/scheduler.h"

namespace NOP
{
template <typename T>
using SharedAttribute = std::shared_ptr<Attribute<T>>;
using SharedPremise = std::shared_ptr<Premise>;
using SharedCondition = std::shared_ptr<Condition>;
using SharedRule = std::shared_ptr<Rule>;
using SharedInstigation = std::shared_ptr<Instigation>;
using SharedAction = std::shared_ptr<Action>;
}  // namespace NOP
