#pragma once
#include <functional>
#include <memory>

#include "libnop/attribute.h"
#include "libnop/observer.h"

namespace NOP
{
using Equal = std::equal_to<>;
using Different = std::not_equal_to<>;
using Greater = std::greater<>;
using GreaterEqual = std::greater_equal<>;
using Less = std::less<>;
using LessEqual = std::less_equal<>;

class Premise final : public Observer
{
   public:
    template <typename T>
    Premise(std::shared_ptr<Attribute<T>> at1,
            std::shared_ptr<Attribute<T>> at2, std::function<bool()> op);
    bool Approved() override;

    // Overload operator for boolean logic
    explicit operator bool() const { return approved_; }

   private:
    std::function<bool()> operation_;
};

template <typename T>
Premise::Premise(std::shared_ptr<Attribute<T>> at1,
                 std::shared_ptr<Attribute<T>> at2, std::function<bool()> op)
    : operation_{std::move(op)}
{
}

inline bool Premise::Approved() { return operation_(); }

template <typename T, typename Func>
auto BuildPremise(std::shared_ptr<Attribute<T>> lhs,
                  std::shared_ptr<Attribute<T>> rhs, Func op)
{
    auto premise = std::make_shared<Premise>(
        lhs, rhs, [=]() { return op(lhs->GetValue(), rhs->GetValue()); });
    lhs->Attach(premise);
    rhs->Attach(premise);
    premise->Update();
    return premise;
}

template <typename T, typename Func>
auto BuildPremise(std::shared_ptr<Attribute<T>> lhs, T value, Func op)
{
    auto rhs = BuildAttribute(value);
    auto premise = std::make_shared<Premise>(
        lhs, rhs, [=]() { return op(lhs->GetValue(), rhs->GetValue()); });
    lhs->Attach(premise);
    rhs->Attach(premise);
    premise->Update();
    return premise;
}

template <typename T, typename Func>
auto BuildPremiseNamed(const std::string_view name, DebugEntity* fbe,
                       std::shared_ptr<Attribute<T>> lhs,
                       std::shared_ptr<Attribute<T>> rhs, Func op)
{
    auto premise = BuildPremise(lhs, rhs, op);
    if constexpr (std::is_base_of_v<DebugEntity, Premise>)
    {
        premise->SetName(name);
        premise->SetFBE(fbe);
    }
    return premise;
}

template <typename T, typename Func>
auto BuildPremiseNamed(const std::string_view name, DebugEntity* fbe,
                       std::shared_ptr<Attribute<T>> lhs, T value, Func op)
{
    auto premise = BuildPremise(lhs, value, op);
    if constexpr (std::is_base_of_v<DebugEntity, Premise>)
    {
        premise->SetName(name);
        premise->SetFBE(fbe);
    }
    return premise;
}

}  // namespace NOP