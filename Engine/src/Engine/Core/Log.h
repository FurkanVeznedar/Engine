#ifndef _LOG_H_
#define _LOG_H_

/*
The MIT License (MIT)

Copyright (c) 2016 Gabi Melman.                                       

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

-- NOTE: Third party dependency used by this software --
This software depends on the fmt lib (MIT License),
and users must comply to its license: https://raw.githubusercontent.com/fmtlib/fmt/master/LICENSE
*/

#include "Enpch.h"

#include "Engine/Core/Base.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Engine {
    // template class std::shared_ptr<spdlog::logger>;

    class Log
    {
    private:
        static std::shared_ptr<spdlog::logger> s_EngineLogger;
        static std::shared_ptr<spdlog::logger> s_AppLogger;
    public:

        static void Init();

        static std::string GetAssetsDir();
        static std::string GetShadersDir();
        static std::string GetImagesDir();
        static std::string GetFilesDir();

        inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_AppLogger; }
    };
}

// Engine Log Macros
#define EN_ENGINE_TRACE(...)   ::Engine::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define EN_ENGINE_INFO(...)    ::Engine::Log::GetEngineLogger()->info(__VA_ARGS__)
#define EN_ENGINE_WARN(...)    ::Engine::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define EN_ENGINE_ERROR(...)   ::Engine::Log::GetEngineLogger()->error(__VA_ARGS__)
#define EN_ENGINE_FATAL(...)   ::Engine::Log::GetEngineLogger()->fatal(__VA_ARGS__)

// Client Log Macros

#define EN_APP_TRACE(...)      ::Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define EN_APP_INFO(...)       ::Engine::Log::GetClientLogger()->info(__VA_ARGS__)
#define EN_APP_WARN(...)       ::Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define EN_APP_ERROR(...)      ::Engine::Log::GetClientLogger()->error(__VA_ARGS__)
#define EN_APP_FATAL(...)      ::Engine::Log::GetClientLogger()->fatal(__VA_ARGS__)


#endif // _LOG_H_