#include "libnop/observable.h"
#include "libnop/observer.h"

namespace NOP
{
void Observable::Attach(const std::shared_ptr<Observer>& observer)
{
    observers_.insert(observers_.end(), observer);
}
}  // namespace NOP
