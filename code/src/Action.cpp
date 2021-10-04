#include "Action.h"
#include "Instigation.h"

namespace NOP
{
	void Action::AddInstigation(std::shared_ptr<Instigation> instigation)
	{
		instigations_.insert(instigations_.end(), std::move(instigation));
	}

	void Action::Activate()
	{
		for(const auto& instigation : instigations_)
		{
			instigation->Instigate();
		}
	}
}
