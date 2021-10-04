#pragma once
#include <memory>
#include <mutex>

#include "libnop/logger.h"
#include "libnop/observable.h"

namespace NOP
{
template <typename T>
class Attribute final : public Observable
{
   public:
    Attribute() = delete;
    Attribute(Attribute&) = delete;
    Attribute(Attribute&&) = delete;
    explicit Attribute(const T value);
    Attribute& operator=(Attribute&) = delete;
    Attribute& operator=(Attribute&&) = delete;
    ~Attribute() = default;

    template <NOPFlag Flag = Default>
    void SetValue(T value);

    void SetValue(const T value, const bool renotify);

    T GetValue(void) const;

   private:
    T value_;
    template <NOPFlag Flag = Default>
    void SetValueInternal(T value);
};

template <typename T>
Attribute<T>::Attribute(const T value) : value_{value}
{
}

template <typename T>
void Attribute<T>::SetValue(T value, const bool renotify)
{
    if (renotify)
    {
        SetValue<ReNotify>(value);
    }
    else
    {
        SetValue<Default>(value);
    }
}

template <typename T>
template <NOPFlag Flag>
void Attribute<T>::SetValue(T value)
{
    if constexpr (0 < (Exclusive & Flag))
    {
        static std::recursive_mutex mutex_;
        const std::lock_guard<std::recursive_mutex> lock{mutex_};
        SetValueInternal<Flag>(value);
    }
    else
    {
        SetValueInternal<Flag>(value);
    }
}

template <typename T>
T Attribute<T>::GetValue(void) const
{
    return value_;
}

template <typename T>
template <NOPFlag Flag>
void Attribute<T>::SetValueInternal(T value)
{
    const bool changed = (value != value_);
    value_ = value;
    if constexpr (0 < (ReNotify & Flag))
    {
        Notify<Flag>();
    }
    else if (changed)
    {
#ifdef LIBNOP_LOG_ENABLE
        if constexpr (fmt::has_formatter<T, fmt::format_context>::value)
        {
            LOG(this, "Value changed to {}", value_);
        }
        else
        {
            LOG(this, "Value changed");
        }
#endif
        Notify<Flag>();
    }
}

template <typename T>
auto BuildAttribute(const T value)
{
    return std::make_shared<Attribute<T>>(value);
}

template <typename T>
auto BuildAttributeNamed(const std::string_view name, DebugEntity* fbe,
                         const T value)
{
    auto attr = BuildAttribute(value);
    if constexpr (std::is_base_of_v<DebugEntity, Attribute<T>>)
    {
        attr->SetName(name);
        attr->SetFBE(fbe);
    }
    return attr;
}
}  // namespace NOP
