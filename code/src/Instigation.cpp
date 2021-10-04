#include "Instigation.h"

namespace NOP
{
	void Instigation::AddMethod(Method method)
	{
		methods_.insert(methods_.end(), std::move(method));
	}

	void Instigation::Instigate()
	{
		for(const auto& method: methods_)
		{
			method();
		}
	};
}
