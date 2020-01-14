#include "application.hpp"

namespace vldptrv::network
{
Application::Application(void)
{
    InitListener("localhost");
}

Application *Application::instance(void)
{
    Application app;
    return &app;
}

int Application::GetListenSocket(void) const noexcept
{
    return 0;
}

Application::~Application(void) noexcept = default;
} // namespace vldptrv::network