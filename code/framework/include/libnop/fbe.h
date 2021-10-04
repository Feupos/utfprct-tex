// C++ Framework NOP 4.0
//
// Copyright (c) 2020 - present, Felipe dos Santos Neves
// All rights reserved.
//
// For the license information refer to framework.h

#include <optional>
#include <string>

#include "libnop/logger.h"

namespace NOP
{
class FBE DERIVE_DEBUG_ENTITY
{
   public:
#ifdef LIBNOP_LOG_ENABLE
    explicit FBE(const std::string_view name = "") : DebugEntity(name, nullptr)
    {
    }
#else
    explicit FBE([[maybe_unused]] const std::string_view name = "")
    {
    }
#endif

};
}  // namespace NOP
