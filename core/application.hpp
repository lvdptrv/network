#pragma once

#include <memory>

namespace vldptrv::network
{
struct Application
{
    Application *instance(void);
    int GetListenSocket(void) const noexcept;
    ~Application(void) noexcept;

private:
    Application(void);

private:
    int InitListener(std::string_view host);

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace vldptrv::network