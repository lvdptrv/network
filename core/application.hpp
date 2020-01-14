#pragma once

#include <memory>

namespace vldptrv::network
{
struct Application
{
    Application(void);
    int GetListenSocket(void) const noexcept;
    Application(void) noexcept;
    
private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace vldptrv::network