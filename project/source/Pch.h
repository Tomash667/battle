#pragma once

#ifdef _WIN64
#	define X64
#endif

#include <algorithm>
#include <string>
#include <vector>
#include <cassert>
#include <DirectXMath.h>
#include "FastFunc.h"

using std::string;
using std::vector;
using std::min;
using std::max;

template<typename T>
using delegate = ssvu::FastFunc<T>;
