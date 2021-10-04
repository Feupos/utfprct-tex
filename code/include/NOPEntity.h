#pragma once

#include "Definitions.h"
#include "Observable.h"
#include "Observer.h"

namespace NOP
{
class NOPEntity : public Observer
{
   public:
    NOPEntity() = default;
    NOPEntity(NOPEntity&) = delete;
    NOPEntity(NOPEntity&&) = delete;
    NOPEntity& operator=(NOPEntity&) = delete;
    NOPEntity& operator=(NOPEntity&&) = delete;
    virtual ~NOPEntity() = default;

   private:
};
}  // namespace NOP
