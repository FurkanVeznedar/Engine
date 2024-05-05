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

    std::string Log::GetAssetsDir()
    {
        return "C:/Users/furka/Desktop/Furkan VEZNEDAR/03-Programming/11-FEAEngine/Engine/Assets/";
    }

    std::string Log::GetShadersDir()
    {
        return "C:/Users/furka/Desktop/Furkan VEZNEDAR/03-Programming/11-FEAEngine/Engine/Assets/Shaders/";
    }

    std::string Log::GetImagesDir()
    {
        return "C:/Users/furka/Desktop/Furkan VEZNEDAR/03-Programming/11-FEAEngine/Engine/Assets/Images/";
    }

    std::string Log::GetFilesDir()
    {
        return "C:/Users/furka/Desktop/Furkan VEZNEDAR/03-Programming/11-FEAEngine/Engine/Assets/Files/";
    }
}