#pragma once

// Allow compiling using different container types

#ifndef CONTAINER_TYPE
#include <deque>
#include <list>
#include <vector>
template <typename T>
using NOPContainer = std::vector<T>;
#else
template <typename T>
using NOPContainer = CONTAINER_TYPE<T>;
#endif

namespace NOP
{
using NOPFlag = int;
static constexpr NOPFlag Default = 0b0000;
static constexpr NOPFlag NoNotify = 0b0001;
static constexpr NOPFlag ReNotify = 0b0010;
static constexpr NOPFlag Parallel = 0b0100;
static constexpr NOPFlag Exclusive = 0b1000;
}  // namespace NOP
