#include <optional>
#include <string>

#include "libnop/logger.h"

namespace NOP
{
class FBE : public DebugEntity
{
   public:
    explicit FBE(const std::string_view name = "") : DebugEntity(name, nullptr)
    {
    }
};
}  // namespace NOP
