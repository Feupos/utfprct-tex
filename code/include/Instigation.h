#pragma once
#include <functional>
#include "Definitions.h"

#define METHOD(expression) [&]() { expression }

namespace NOP
{
	using Method = std::function<void(void)>;

	class Instigation final
	{
	public:
		Instigation() = default;
		Instigation(Instigation&) = delete;
		Instigation(Instigation&&) = delete;
		Instigation& operator=(Instigation&) = delete;
		Instigation& operator=(Instigation&&) = delete;
		~Instigation() = default;

		void AddMethod(Method method);
		void Instigate();
	private:
		NOPContainer<Method> methods_;
	};

	template<typename ...Args>
	auto BuildInstigation(Args... methods)
	{
		auto instigation = std::make_shared<Instigation>();
		(instigation->AddMethod(methods), ...);
		return instigation;
	}
}



#pragma once
