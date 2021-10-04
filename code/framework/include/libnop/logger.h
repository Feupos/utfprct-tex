// C++ Framework NOP 4.0
//
// Copyright (c) 2020 - present, Felipe dos Santos Neves
// All rights reserved.
//
// For the license information refer to framework.h

#pragma once

#ifdef LIBNOP_LOG_ENABLE
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#include <string>

#define DERIVE_DEBUG_ENTITY : public DebugEntity
#define SET_DEBUG_PROPERTIES(entity, name, fbe) \
    entity->SetName(name);                      \
    entity->SetFBE(fbe)

struct DebugEntity
{
    DebugEntity() = default;
    DebugEntity(const std::string_view name, DebugEntity* parent = nullptr)
    {
        name_ = name;
        parent_ = parent;
    }

    std::string name_{};
    void SetName(const std::string_view name) { name_ = name; }
    DebugEntity* parent_{nullptr};
    void SetFBE(DebugEntity* fbe) { parent_ = fbe; }
};

namespace NOP
{
class Logger
{
   public:
    Logger();
    ~Logger() = default;

    [[nodiscard]] static Logger& Instance();
    void Log(DebugEntity* ptr, std::string_view text) const;

    void SetLogFileName(const std::string& file_name);

   private:
    std::string log_file_name_{"nop.log"};
};
}  // namespace NOP

inline void LOG(DebugEntity* ptr, const std::string_view text)
{
    NOP::Logger::Instance().Log(ptr, text);
}

template <typename... Args>
inline void LOG(DebugEntity* ptr, const std::string_view text, Args... args)
{
    NOP::Logger::Instance().Log(ptr, fmt::format(text, args...));
}
#define DEBUG_ENTITY(ptr) entity->SetName(#ptr)
#define DEBUG_ENTITY_NAME_FBE(entity, name) \
    entity->SetName(name);                  \
    entity->SetFBE(this)
#define DEBUG_ENTITY_FBE(entity) DEBUG_ENTITY_NAME_FBE(entity, #entity);
#define DEBUG_FBE_NAME(fbe, name) fbe->SetName(name);
#define DEBUG_FBE(fbe) DEBUG_FBE_NAME(fbe, #fbe)

#else

// Define empty structure as placeholder
struct DebugEntity
{
};

#define DERIVE_DEBUG_ENTITY
#define SET_DEBUG_PROPERTIES(entity, name, fbe) \
    (void)name;                                 \
    (void)fbe
#define LOG(ptr, text)
#define DEBUG_ENTITY(ptr)
#define DEBUG_ENTITY_NAME_FBE(entity, name)
#define DEBUG_ENTITY_FBE(entity)
#define DEBUG_FBE_NAME(fbe, name)
#define DEBUG_FBE(fbe)
#endif
