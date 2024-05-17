#ifndef _ENTRYPOINT_H_
#define _ENTRYPOINT_H_

#ifdef EN_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
    Engine::Log::Init();

    auto app = Engine::CreateApplication();
    app->Run();
    delete app;
}

#endif

#endif // _ENTRYPOINT_H_