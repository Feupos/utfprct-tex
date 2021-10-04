#include <memory>
#include <functional>
#include <algorithm>
#include "Condition.h"
#include "BasePremise.h"

namespace NOP
{

	Condition::Condition(std::function<bool()> operation) : operation_{std::move(operation)}
	{
	}

	void Condition::Update(const bool reNotify)
	{
		const bool approve{ operation_() };
		const bool changed{ approve != approved_ };
		approved_ = approve;
		if (changed || reNotify)
		{
			Notify(reNotify);
		}
	}

	bool Condition::Approved(void) const
	{
		return approved_;
	}

	void Condition::AddElement(std::shared_ptr<BasePremise> premise)
	{
		premise->Attach(shared_from_this());
		premises_.push_back(std::move(premise));
	}

	void Condition::SetOperation(std::function<bool()> operation)
	{
		operation_ = std::move(operation);
	}

	void Condition::AddElement(std::shared_ptr<Condition> condition)
	{
		condition->Attach(shared_from_this());
		sub_conditions_.push_back(std::move(condition));
	}
}



