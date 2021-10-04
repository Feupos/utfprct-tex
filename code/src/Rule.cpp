#include <memory>
#include "Rule.h"
#include "Condition.h"
#include "Action.h"

namespace NOP
{
	void Rule::Update(const bool reNotify)
	{
		const std::lock_guard<std::recursive_mutex> lock{ mutex_ };
		const bool approve{ condition_->Approved() };
		const bool changed{ approve != approved_ };
		approved_ = approve;
		if (approve && (changed || reNotify))
		{
			action_->Activate();
		}
	}

	void Rule::SetCondition(std::shared_ptr<Condition> condition)
	{
		condition_ = std::move(condition);
		condition_->Attach(shared_from_this());
	}

	void Rule::SetAction(std::shared_ptr<Action> action)
	{
		action_ = std::move(action);
	}

	bool Rule::Approved(void) const
	{
		return approved_;
	}

}
