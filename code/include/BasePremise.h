#pragma once
#include "Observable.h"
#include "Observer.h"

namespace NOP
{
	using Equal = std::equal_to<>;
	using Different = std::not_equal_to<>;
	using Greater = std::greater<>;
	using GreaterEqual = std::greater_equal<>;
	using Less = std::less<>;
	using LessEqual = std::less_equal<>;

	// This class is used to provide acces to the Approved method
	// without requiring to specify the Premise template arguments
	class BasePremise : public Observer, public Observable
	{

	public:
		BasePremise() = default;
		BasePremise(BasePremise&) = delete;
		BasePremise(BasePremise&&) = delete;
		BasePremise& operator=(BasePremise&) = delete;
		BasePremise& operator=(BasePremise&&) = delete;
		~BasePremise() override = default;

		bool Approved() const { return approved_; }
		// Overload operator for boolean logic
		virtual explicit operator bool() = 0;

	protected:
		bool approved_{false};
	};
}