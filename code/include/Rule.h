#pragma once
#include <memory>
#include <mutex>
#include "Observer.h"
#include "Condition.h"
#include "Action.h"

namespace NOP
{
	class Rule final : public Observer
	{

	public:
		Rule() = default;
		Rule(Rule&) = delete;
		Rule(Rule&&) = delete;
		Rule& operator=(Rule&) = delete;
		Rule& operator=(Rule&&) = delete;
		~Rule() override = default;

		[[nodiscard]] bool Approved(void) const;
		void Update(const bool reNotify = false) override;
		void SetCondition(std::shared_ptr<Condition> condition);
		void SetAction(std::shared_ptr<Action> action);

	private:
		bool approved_{ false };
		std::shared_ptr<Condition> condition_;
		std::shared_ptr<Action> action_;
		std::recursive_mutex mutex_;
	};

	inline auto BuildRule(std::shared_ptr<Condition> condition, std::shared_ptr<Action> action)
	{
		auto rule = std::make_shared<NOP::Rule>();
		rule->SetAction(std::move(action));
		rule->SetCondition(std::move(condition));
		rule->Update();
		return rule;
	}
}
