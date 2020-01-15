#pragma once

#include <memory>

namespace vldptrv::network
{
struct Socket
{
    Socket(int domain, int type, int protocol);
    ~Socket(void) noexcept;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace vldptv::network