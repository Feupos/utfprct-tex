#pragma once
#include <memory>
#include "Instigation.h"

namespace NOP
{
	class Action final
	{
	public:
		Action() = default;
		Action(Action&) = delete;
		Action(Action&&) = delete;
		Action& operator=(Action&) = delete;
		Action& operator=(Action&&) = delete;
		~Action() = default;

		void AddInstigation(std::shared_ptr<Instigation> instigation);
		void Activate();
	private:
		NOPContainer<std::shared_ptr<Instigation>> instigations_;
	};

	template<typename ...Args>
	auto BuildAction(Args... instigation)
	{
		auto action = std::make_shared<Action>();
		(action->AddInstigation(instigation), ...);
		return action;
	}
}



