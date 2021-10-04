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
    Premise(std::function<bool()> op);
    bool Approved() override;

    // Overload operator for boolean logic
    explicit operator bool() const { return approved_; }

   private:
    std::function<bool()> operation_;
};

Premise::Premise(std::function<bool()> op) : operation_{std::move(op)} {}

inline bool Premise::Approved() { return operation_(); }

template <typename T, typename Func>
auto BuildPremise(std::shared_ptr<Attribute<T>> lhs,
                  std::shared_ptr<Attribute<T>> rhs, Func op)
{
    auto premise = std::make_shared<Premise>(
        [=]() { return op(lhs->GetValue(), rhs->GetValue()); });
    lhs->Attach(premise);
    rhs->Attach(premise);
    premise->Update();
    return premise;
}


template <typename T, typename Func>
auto BuildPremise(std::shared_ptr<Attribute<T>> lhs, T rhs, Func op)
{
    auto premise =
        std::make_shared<Premise>([=]() { return op(lhs->GetValue(), rhs); });
    lhs->Attach(premise);
    premise->Update();
    return premise;
}

template <typename T, typename Func>
auto BuildPremiseNamed(const std::string_view name, DebugEntity* fbe,
                       std::shared_ptr<Attribute<T>> lhs,
                       std::shared_ptr<Attribute<T>> rhs, Func op)
{
    auto premise = BuildPremise(lhs, rhs, op);
    SET_DEBUG_PROPERTIES(premise, name, fbe);
    return premise;
}

template <typename T, typename Func>
auto BuildPremiseNamed(const std::string_view name, DebugEntity* fbe,
                       std::shared_ptr<Attribute<T>> lhs, T rhs, Func op)
{
    auto premise = BuildPremise(lhs, rhs, op);
    SET_DEBUG_PROPERTIES(premise, name, fbe);
    return premise;
}

}  // namespace NOP
