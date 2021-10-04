#pragma once

// Allow compiling using different container types

#ifndef CONTAINER_TYPE
#include <vector>
#include <list>
#include <deque>
template<typename T>
using NOPContainer = std::vector<T>;
#else
template<typename T>
using NOPContainer = CONTAINER_TYPE<T>;
#endif

