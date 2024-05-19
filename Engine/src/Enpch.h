#ifndef _ENPCH_H_
#define _ENPCH_H_

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>

#include <cmath>

#include "Engine/Core/Log.h"
#include "Engine/Debug/Instrumentor.h"

#ifdef EN_PLATFORM_WINDOWS
    #include <Windows.h>
#endif
#endif // _ENPCH_H_
