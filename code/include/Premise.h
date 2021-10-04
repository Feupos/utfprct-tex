#pragma once
#include <iostream>
#include <memory>
#include <functional>
#include <cstdio>
#include "Attribute.h"
#include "BasePremise.h"

namespace NOP
{
	template <typename T>
	class Premise final : public BasePremise
	{

	public:
		Premise() = delete;
		Premise(Premise&) = delete;
		Premise(Premise&&) = delete;
		Premise& operator=(Premise&) = delete;
		Premise& operator=(Premise&&) = delete;
		Premise(std::shared_ptr<Attribute<T>> at1, std::shared_ptr<Attribute<T>> at2, std::function<bool(T, T)> op);
		Premise(std::shared_ptr<Attribute<T>> at1, T val, std::function<bool(T, T)> op);
		~Premise() = default;

		void Update(const bool reNotify = false) override;
		void AttachAttributes(void);

		// Overload operator for boolean logic
		explicit operator bool(){ return operation_(attribute1_->GetValue(), attribute2_->GetValue()); }

	private:
		std::shared_ptr<Attribute<T>> attribute1_;
		std::shared_ptr<Attribute<T>> attribute2_;
		std::function<bool(T, T)> operation_;
	};

	template <typename T>
	Premise<T>::Premise(std::shared_ptr<Attribute<T>> at1, std::shared_ptr<Attribute<T>> at2, std::function<bool(T, T)> op) :
		attribute1_{std::move(at1)}, attribute2_{std::move(at2)}, operation_{std::move(op)}
	{
		
	}

	template <typename T>
	Premise<T>::Premise(std::shared_ptr<Attribute<T>> at1, T val, std::function<bool(T, T)> op) :
		Premise(at1, std::make_shared<Attribute<T>>( val ), op)
	{
		
	}

	template <typename T>	
	void Premise<T>::AttachAttributes(void)
	{
		attribute1_->Attach(shared_from_this());
		attribute2_->Attach(shared_from_this());
	}

	template <typename T>
	void Premise<T>::Update(const bool reNotify)
	{
		const bool approve{ operation_(attribute1_->GetValue(), attribute2_->GetValue()) };
		const bool changed{ approve != approved_ };
		approved_ = approve;
		if (changed || reNotify)
		{
			Notify(reNotify);
		}
	}

	template<typename T, typename ...Args>
	auto BuildPremise(Args... args)
	{
		auto premise = std::make_shared<Premise<T>>(args...);
		premise->AttachAttributes();
		premise->Update();
		return std::dynamic_pointer_cast<BasePremise>(premise);
	}
}



