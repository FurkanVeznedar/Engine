#ifndef _ENTRYPOINT_H_
#define _ENTRYPOINT_H_

#ifdef EN_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
    Engine::Log::Init();
    EN_ENGINE_WARN("Initialized Log!");
    int a = 5;
    EN_APP_ERROR("Hello! Var={0}", a);

    auto app = Engine::CreateApplication();
    app->Run();
    delete app;
}

#endif

#endif // _ENTRYPOINT_H_