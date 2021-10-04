#pragma once
#include <memory>
#include <functional>
#include "BasePremise.h"
#include "Condition.h"

#define CONDITION(expression) [&]() { return bool(expression); }

namespace NOP
{
	class Condition final : public Observable, public Observer
	{

	public:
		Condition() = default;
		Condition(Condition&) = delete;
		Condition(Condition&&) = delete;
		explicit Condition(std::function<bool(void)> operation);
		Condition& operator=(Condition&) = delete;
		Condition& operator=(Condition&&) = delete;
		~Condition() override = default;

		void Update(const bool reNotify = false) override;
		[[nodiscard]] bool Approved(void) const;

		// Overloaded functions to work with fold expression in builder
		void AddElement(std::shared_ptr<Condition> condition);
		void AddElement(std::shared_ptr<BasePremise> premise);

		void SetOperation(std::function<bool(void)> operation);

		// Overload operator for boolean logic
		explicit operator bool() const { return operation_(); }

	private:
		std::function<bool(void)> operation_;
		NOPContainer<std::shared_ptr<BasePremise>> premises_;
		NOPContainer<std::shared_ptr<Condition>> sub_conditions_;
		bool approved_{ false };
	};

	template<typename ...Args>
	auto BuildCondition(std::function<bool(void)> operation, Args... args)
	{
		auto condition = std::make_shared<NOP::Condition>(operation);
		(condition->AddElement(std::move(args)), ...);
		condition->Update();
		return condition;
	}
}

