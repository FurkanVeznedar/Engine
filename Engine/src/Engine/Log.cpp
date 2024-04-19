#include "Log.h"

namespace Engine {

    std::shared_ptr<spdlog::logger> Log::s_EngineLogger;
    std::shared_ptr<spdlog::logger> Log::s_AppLogger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        Log::s_EngineLogger = spdlog::stdout_color_mt("ENGINE");
        Log::s_EngineLogger->set_level(spdlog::level::trace);

        Log::s_AppLogger = spdlog::stdout_color_mt("APP");
        Log::s_AppLogger->set_level(spdlog::level::trace);
    }
}