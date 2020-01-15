#pragma once

#include <memory>

namespace vldptrv::network
{
struct Socket
{
    Socket(int domain, int type, int protocol);
    int GetHandle(void) const noexcept;
    ~Socket(void) noexcept;

protected:
    Socket(int handle = -1) noexcept;
private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace vldptv::network