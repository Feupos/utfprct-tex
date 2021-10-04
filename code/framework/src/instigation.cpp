#include "libnop/instigation.h"

#include <execution>

namespace NOP
{
void Instigation::AddMethod(Method method)
{
    methods_.insert(methods_.end(), std::move(method));
}

void Instigation::Instigate()
{
    LOG(this, "Instigated");
    for (const auto& method : methods_)
    {
        method();
    }
}

void ParallelInstigation::Instigate()
{
    LOG(this, "Instigated");
    std::for_each(std::execution::par_unseq, methods_.begin(),
                  methods_.end(),
                  [](auto& method) { method(); });
}
}  // namespace NOP
