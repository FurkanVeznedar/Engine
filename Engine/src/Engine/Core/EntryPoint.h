#ifndef _ENTRYPOINT_H_
#define _ENTRYPOINT_H_

#ifdef EN_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
    EN_PROFILE_BEGIN_SESSION("Startup", "EngineProfile-Startup.json");
    Engine::Log::Init();
    auto app = Engine::CreateApplication();
    EN_PROFILE_END_SESSION();

    EN_PROFILE_BEGIN_SESSION("Runtime", "EngineProfile-Runtime.json");
    app->Run();
    EN_PROFILE_END_SESSION();

    EN_PROFILE_BEGIN_SESSION("Shutdown", "EngineProfile-Shutdown.json");
    delete app;
    EN_PROFILE_END_SESSION();
}

#endif

#endif // _ENTRYPOINT_H_