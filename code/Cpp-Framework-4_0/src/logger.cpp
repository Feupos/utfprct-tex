#ifdef LIBNOP_LOG_ENABLE
#include "libnop/logger.h"
namespace NOP
{
Logger::Logger()
{
    const auto logger = spdlog::basic_logger_mt("NOP", log_file_name_);
    spdlog::set_default_logger(logger);
    spdlog::set_level(spdlog::level::trace);
}

Logger& Logger::Instance()
{
    static const auto instance{std::make_unique<Logger>()};
    return *instance;
}

void Logger::SetLogFileName(const std::string& file_name)
{
    log_file_name_ = file_name;
    auto logger = spdlog::basic_logger_mt(log_file_name_, log_file_name_);
    spdlog::set_default_logger(logger);
    spdlog::set_level(spdlog::level::trace);
}

void Logger::Log(DebugEntity* ptr, const std::string_view text) const
{
    if (ptr && !ptr->name_.empty())
    {
        if (ptr->parent_ && !ptr->parent_->name_.empty())
        {
            spdlog::info("{} - {}: {}", ptr->parent_->name_, ptr->name_, text);
        }
        else
        {
            spdlog::info("{}: {}", ptr->name_, text);
        }
    }
}
}  // namespace NOP
#endif
