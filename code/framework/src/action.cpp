#include "libnop/action.h"

#include <execution>

#include "libnop/instigation.h"

namespace NOP
{
void Action::AddInstigation(std::shared_ptr<Instigation> instigation)
{
    instigations_.insert(instigations_.end(), std::move(instigation));
}

void Action::Activate()
{
    LOG(this, "Activated");
    for (const auto& instigation : instigations_)
    {
        instigation->Instigate();
    }
}

void ParallelAction::Activate()
{
    LOG(this, "Activated");
    std::for_each(std::execution::par_unseq, instigations_.begin(),
                  instigations_.end(),
                  [](auto& instigation) { instigation->Instigate(); });
}

}  // namespace NOP
