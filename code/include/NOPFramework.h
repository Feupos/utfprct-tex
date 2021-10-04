#pragma once

#include "Action.h"
#include "Attribute.h"
#include "Condition.h"
#include "Instigation.h"
#include "Premise.h"
#include "Rule.h"

namespace  NOP
{
	template<typename T>
	using SharedAttribute = std::shared_ptr<Attribute<T>>;
	using SharedPremise = std::shared_ptr<BasePremise>;
	using SharedCondition = std::shared_ptr<Condition>;
	using SharedRule = std::shared_ptr<Rule>;
	using SharedInstigation = std::shared_ptr<Instigation>;
	using SharedAction = std::shared_ptr<Action>;
}